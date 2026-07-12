#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>

#include "system.h"

void showSystemInfo(void)
{
    char hostname[256];
    struct utsname sys;

    printf("\n============================================================\n");
    printf("                 SysGuard v1.0\n");
    printf("          Linux Health & Security Auditor\n");
    printf("============================================================\n\n");

    /* Hostname */

    if (gethostname(hostname, sizeof(hostname)) == 0)
        printf("Hostname        : %s\n", hostname);

    /* Current User */

    struct passwd *pw = getpwuid(getuid());

    if (pw != NULL)
        printf("Current User    : %s\n", pw->pw_name);

    /* Shell */

    char *shell = getenv("SHELL");

    if (shell != NULL)
        printf("Shell           : %s\n", shell);

    /* Kernel Information */

    if (uname(&sys) == 0)
    {
        printf("Kernel          : %s\n", sys.release);
        printf("Architecture    : %s\n", sys.machine);
    }

    /* Operating System */

    FILE *fp = fopen("/etc/os-release", "r");

    if (fp != NULL)
    {
        char line[256];

        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "PRETTY_NAME=", 12) == 0)
            {
                char *value = strchr(line, '=');

                if (value)
                {
                    value++;

                    value[strcspn(value, "\n")] = 0;

                    if (value[0] == '"')
                    {
                        value++;
                        value[strlen(value) - 1] = '\0';
                    }

                    printf("Operating System: %s\n", value);
                    break;
                }
            }
        }

        fclose(fp);
    }

    /* CPU Information */

    fp = fopen("/proc/cpuinfo", "r");

    if (fp != NULL)
    {
        char line[256];
        int cores = 0;

        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "model name", 10) == 0)
            {
                char *value = strchr(line, ':');

                if (value)
                {
                    printf("CPU Model       :%s", value + 1);
                    break;
                }
            }
        }

        rewind(fp);

        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "processor", 9) == 0)
                cores++;
        }

        printf("CPU Threads     : %d\n", cores);

        fclose(fp);
    }

    /* RAM */

    fp = fopen("/proc/meminfo", "r");

    if (fp != NULL)
    {
        char line[256];

        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "MemTotal:", 9) == 0)
            {
                long mem;

                sscanf(line, "MemTotal: %ld kB", &mem);

                printf("Installed RAM   : %.2f GB\n",
                       mem / 1024.0 / 1024.0);

                break;
            }
        }

        fclose(fp);
    }

    /* Uptime */

    fp = fopen("/proc/uptime", "r");

    if (fp != NULL)
    {
        double seconds;

        fscanf(fp, "%lf", &seconds);

        int days = seconds / 86400;
        int hours = ((int)seconds % 86400) / 3600;
        int minutes = ((int)seconds % 3600) / 60;

        printf("Uptime          : ");

        if (days)
            printf("%d day(s) ", days);

        printf("%d hour(s) %d minute(s)\n", hours, minutes);

        fclose(fp);
    }

    printf("\n============================================================\n");
}