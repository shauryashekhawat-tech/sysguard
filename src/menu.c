#include <stdio.h>

#include "menu.h"
#include "colors.h"

void showMenu(void)
{
    printf(CYAN BOLD);
    printf("\n=========================================================\n");
    printf("                     SysGuard v1.0\n");
    printf("             Linux Health & Security Auditor\n");
    printf("=========================================================\n");
    printf(RESET);

    printf(" 1. System Information\n");
    printf(" 2. Health Monitoring\n");
    printf(" 3. Network Diagnostics\n");
    printf(" 4. Security Audit\n");
    printf(" 5. Generate Report\n");
    printf(" 0. Exit\n");

}