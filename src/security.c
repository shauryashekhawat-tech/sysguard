#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "security.h"
#include "colors.h"

static int score = 100;

static void section(const char *title)
{
    printf(CYAN BOLD "\n%s\n" RESET, title);
    printf("----------------------------------------------\n");
}

static void checkUser()
{
    section("Current User");

    if(geteuid()==0)
    {
        printf(RED "[!] Running as root\n" RESET);
        score -= 10;
    }
    else
    {
        printf(GREEN "[✓] Running as normal user\n" RESET);
    }
}

static void checkSSH()
{
    section("SSH Service");

    FILE *fp = popen("systemctl is-active ssh 2>/dev/null","r");

    if(fp)
    {
        char status[64]={0};

        fgets(status,sizeof(status),fp);

        if(strncmp(status,"active",6)==0)
            printf(GREEN "[✓] SSH Service Running\n" RESET);
        else
            printf(YELLOW "[!] SSH Service Not Running\n" RESET);

        pclose(fp);
    }
}

static void checkFirewall()
{
    section("Firewall");

    if(system("command -v ufw >/dev/null 2>&1")==0)
    {
        if(system("ufw status | grep -q active")==0)
            printf(GREEN "[✓] UFW Enabled\n" RESET);
        else
        {
            printf(RED "[✗] UFW Disabled\n" RESET);
            score -= 15;
        }

        return;
    }

    if(system("command -v firewall-cmd >/dev/null 2>&1")==0)
    {
        if(system("firewall-cmd --state >/dev/null 2>&1")==0)
            printf(GREEN "[✓] Firewalld Running\n" RESET);
        else
        {
            printf(RED "[✗] Firewalld Stopped\n" RESET);
            score -= 15;
        }

        return;
    }

    if(system("command -v nft >/dev/null 2>&1")==0)
    {
        printf(GREEN "[✓] nftables Installed\n" RESET);
        return;
    }

    printf(YELLOW "[!] Firewall Not Detected\n" RESET);
    score -= 10;
}

static void checkSUID()
{
    section("SUID Files");

    FILE *fp=popen("find /usr/bin -perm -4000 2>/dev/null | wc -l","r");

    if(fp)
    {
        int count=0;

        fscanf(fp,"%d",&count);

        printf("SUID Files : %d\n",count);

        if(count>50)
            score-=5;

        pclose(fp);
    }
}

static void checkWorldWritable()
{
    section("World Writable Files");

    FILE *fp=popen("find /etc -xdev -type f -perm -0002 2>/dev/null | wc -l","r");

    if(fp)
    {
        int count=0;

        fscanf(fp,"%d",&count);

        printf("Files : %d\n",count);

        if(count>0)
            score-=10;

        pclose(fp);
    }
}

static void printScore()
{
    printf(CYAN BOLD);

    printf("\n==============================================\n");

    printf("Security Score : ");

    if(score>=90)
        printf(GREEN "%d/100\n",score);

    else if(score>=70)
        printf(YELLOW "%d/100\n",score);

    else
        printf(RED "%d/100\n",score);

    printf(RESET);

    printf("==============================================\n");
}

void showSecurity()
{
    score=100;

    printf(CYAN BOLD);
    printf("\n========================================================\n");
    printf("                Security Audit\n");
    printf("========================================================\n");
    printf(RESET);

    checkUser();

    checkSSH();

    checkFirewall();

    checkSUID();

    checkWorldWritable();

    printScore();
}