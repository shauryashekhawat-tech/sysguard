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

    printf("\n 1. System Information\n\n");
    printf(" 2. Health Monitoring\n\n");
    printf(" 3. Network Diagnostics\n\n");
    printf(" 4. Security Audit\n\n");
    printf(" 5. Generate Report\n\n");
    printf(" 0. Exit\n");

}