#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>

#include "report.h"
#include "colors.h"

void generateReport(void)
{
    FILE *fp;

    fp = fopen("reports/report.txt","w");

    if(fp==NULL)
    {
        printf(RED "\nUnable to create report.\n" RESET);
        return;
    }

    time_t now=time(NULL);

    fprintf(fp,
"============================================================\n");

    fprintf(fp,
"                    SysGuard Report\n");

    fprintf(fp,
"============================================================\n\n");

    fprintf(fp,"Generated : %s",ctime(&now));

    char hostname[256];

    gethostname(hostname,sizeof(hostname));

    fprintf(fp,"\nHostname : %s\n",hostname);

    struct utsname sys;

    uname(&sys);

    fprintf(fp,"Kernel   : %s\n",sys.release);

    fprintf(fp,"Machine  : %s\n",sys.machine);

    FILE *cpu=fopen("/proc/cpuinfo","r");

    if(cpu)
    {
        char line[256];

        while(fgets(line,sizeof(line),cpu))
        {
            if(strncmp(line,"model name",10)==0)
            {
                fprintf(fp,"%s",line);
                break;
            }
        }

        fclose(cpu);
    }

    FILE *mem=fopen("/proc/meminfo","r");

    if(mem)
    {
        char line[256];

        fprintf(fp,"\n");

        while(fgets(line,sizeof(line),mem))
        {
            if(strncmp(line,"MemTotal",8)==0)
                fprintf(fp,"%s",line);

            if(strncmp(line,"MemAvailable",12)==0)
                fprintf(fp,"%s",line);

            if(strncmp(line,"SwapTotal",9)==0)
                fprintf(fp,"%s",line);

            if(strncmp(line,"SwapFree",8)==0)
                fprintf(fp,"%s",line);
        }

        fclose(mem);
    }

    fprintf(fp,
"\n============================================================\n");

    fclose(fp);

    printf(GREEN "\nReport generated successfully.\n" RESET);

    printf("Saved to reports/report.txt\n");
}