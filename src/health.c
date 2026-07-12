#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include "health.h"
#include "colors.h"

static void printMemory(void)
{
    FILE *fp = fopen("/proc/meminfo", "r");

    if (!fp)
    {
        printf(RED "Unable to read /proc/meminfo\n" RESET);
        return;
    }

    char line[256];

    long memTotal = 0;
    long memAvailable = 0;
    long swapTotal = 0;
    long swapFree = 0;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "MemTotal: %ld kB", &memTotal);
        sscanf(line, "MemAvailable: %ld kB", &memAvailable);
        sscanf(line, "SwapTotal: %ld kB", &swapTotal);
        sscanf(line, "SwapFree: %ld kB", &swapFree);
    }

    fclose(fp);

    double used =
        (memTotal - memAvailable) / 1024.0 / 1024.0;

    double total =
        memTotal / 1024.0 / 1024.0;

    printf(BOLD "Memory\n" RESET);

    printf("RAM Used        : %.2f / %.2f GB (%.1f%%)\n",
           used,
           total,
           used / total * 100.0);

    if (swapTotal)
    {
        double swapUsed =
            (swapTotal - swapFree) / 1024.0 / 1024.0;

        printf("Swap Used       : %.2f / %.2f GB\n",
               swapUsed,
               swapTotal / 1024.0 / 1024.0);
    }
    else
    {
        printf("Swap            : Disabled\n");
    }

    printf("\n");
}

static void printDisk(void)
{
    struct statvfs disk;

    if (statvfs("/", &disk) != 0)
    {
        printf(RED "Unable to read filesystem\n" RESET);
        return;
    }

    unsigned long long total =
        disk.f_blocks * disk.f_frsize;

    unsigned long long free =
        disk.f_bavail * disk.f_frsize;

    unsigned long long used =
        total - free;

    printf(BOLD "Disk\n" RESET);

    printf("Disk Used       : %.2f / %.2f GB (%.1f%%)\n\n",
           used / 1024.0 / 1024 / 1024,
           total / 1024.0 / 1024 / 1024,
           used * 100.0 / total);
}

static void printLoad(void)
{
    double load[3];

    if (getloadavg(load, 3) != -1)
    {
        printf(BOLD "Load Average\n" RESET);

        printf("1 min           : %.2f\n", load[0]);
        printf("5 min           : %.2f\n", load[1]);
        printf("15 min          : %.2f\n\n", load[2]);
    }
}

static void printTemperature(void)
{
    FILE *fp =
        fopen("/sys/class/thermal/thermal_zone0/temp", "r");

    if (!fp)
        return;

    int temp;

    fscanf(fp, "%d", &temp);

    fclose(fp);

    printf(BOLD "CPU Temperature\n" RESET);

    printf("Temperature     : %.1f °C\n\n",
           temp / 1000.0);
}

static void printBattery(void)
{
    FILE *fp;

    char status[64];

    int capacity;

    fp = fopen(
        "/sys/class/power_supply/BAT0/status",
        "r");

    if (!fp)
        return;

    fgets(status, sizeof(status), fp);

    fclose(fp);

    fp = fopen(
        "/sys/class/power_supply/BAT0/capacity",
        "r");

    if (!fp)
        return;

    fscanf(fp, "%d", &capacity);

    fclose(fp);

    status[strcspn(status, "\n")] = 0;

    printf(BOLD "Battery\n" RESET);

    printf("Status          : %s\n", status);

    printf("Charge          : %d%%\n\n", capacity);
}

static void printCPUUsage(void)
{
    FILE *fp;

    unsigned long long user1, nice1, system1, idle1;
    unsigned long long iowait1, irq1, softirq1, steal1;

    unsigned long long user2, nice2, system2, idle2;
    unsigned long long iowait2, irq2, softirq2, steal2;

    fp = fopen("/proc/stat", "r");

    if(fp == NULL)
    {
        printf(RED "Unable to read CPU statistics\n" RESET);
        return;
    }

    fscanf(fp,
           "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user1,
           &nice1,
           &system1,
           &idle1,
           &iowait1,
           &irq1,
           &softirq1,
           &steal1);

    fclose(fp);

    sleep(1);

    fp = fopen("/proc/stat", "r");

    if(fp == NULL)
        return;

    fscanf(fp,
           "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user2,
           &nice2,
           &system2,
           &idle2,
           &iowait2,
           &irq2,
           &softirq2,
           &steal2);

    fclose(fp);

    unsigned long long idle =
        (idle2 + iowait2) - (idle1 + iowait1);

    unsigned long long total1 =
        user1 + nice1 + system1 + idle1 +
        iowait1 + irq1 + softirq1 + steal1;

    unsigned long long total2 =
        user2 + nice2 + system2 + idle2 +
        iowait2 + irq2 + softirq2 + steal2;

    unsigned long long total = total2 - total1;

    double usage =
        (double)(total - idle) * 100.0 / total;

    printf(BOLD "CPU\n" RESET);

    printf("CPU Usage       : %.2f%%\n\n", usage);
}

void showHealth(void)
{
    printf(CYAN BOLD);

    printf("\n=====================================================\n");
    printf("                System Health\n");
    printf("=====================================================\n\n");

    printf(RESET);

    printMemory();

    printDisk();

    printCPUUsage();

    printLoad();

    printTemperature();

    printBattery();

    printf(CYAN);

    printf("=====================================================\n");

    printf(RESET);
}