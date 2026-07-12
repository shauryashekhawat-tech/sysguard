#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>

#include "network.h"
#include "colors.h"

static void printHostname()
{
    char hostname[256];

    if(gethostname(hostname,sizeof(hostname))==0)
        printf("Hostname        : %s\n",hostname);
}

static void printInterfaces()
{
    struct ifaddrs *ifaddr,*ifa;

    if(getifaddrs(&ifaddr)==-1)
        return;

    for(ifa=ifaddr;ifa!=NULL;ifa=ifa->ifa_next)
    {
        if(ifa->ifa_addr==NULL)
            continue;

        if(ifa->ifa_addr->sa_family!=AF_INET)
            continue;

        if(ifa->ifa_flags & IFF_LOOPBACK)
            continue;

        char ip[INET_ADDRSTRLEN];

        struct sockaddr_in *addr=
            (struct sockaddr_in*)ifa->ifa_addr;

        inet_ntop(AF_INET,
                  &addr->sin_addr,
                  ip,
                  sizeof(ip));

        printf("Interface       : %s\n",ifa->ifa_name);
        printf("IP Address      : %s\n",ip);

        break;
    }

    freeifaddrs(ifaddr);
}

static void printGateway()
{
    FILE *fp=fopen("/proc/net/route","r");

    if(!fp)
        return;

    char line[256];

    fgets(line,sizeof(line),fp);

    while(fgets(line,sizeof(line),fp))
    {
        char iface[32];
        unsigned long dest,gate;

        sscanf(line,"%31s %lx %lx",
               iface,
               &dest,
               &gate);

        if(dest==0)
        {
            struct in_addr addr;

            addr.s_addr=gate;

            printf("Gateway         : %s\n",
                   inet_ntoa(addr));

            break;
        }
    }

    fclose(fp);
}

static void printDNS()
{
    FILE *fp=fopen("/etc/resolv.conf","r");

    if(!fp)
        return;

    char line[256];

    printf("DNS Servers\n");

    while(fgets(line,sizeof(line),fp))
    {
        if(strncmp(line,"nameserver",10)==0)
        {
            char dns[64];

            sscanf(line,"nameserver %63s",dns);

            printf("  %s\n",dns);
        }
    }

    fclose(fp);
}

static void checkInternet()
{
    int ret=system("ping -c 1 -W 1 1.1.1.1 > /dev/null 2>&1");

    if(ret==0)
        printf("\nInternet        : " GREEN "Connected\n" RESET);
    else
        printf("\nInternet        : " RED "Disconnected\n" RESET);
}

void showNetwork()
{
    printf(CYAN BOLD);

    printf("\n=====================================================\n");
    printf("            Network Diagnostics\n");
    printf("=====================================================\n\n");

    printf(RESET);

    printHostname();

    printInterfaces();

    printGateway();

    printf("\n");

    printDNS();

    checkInternet();

    printf(CYAN);

    printf("\n=====================================================\n");

    printf(RESET);
}