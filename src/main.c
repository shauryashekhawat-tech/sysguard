#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "system.h"
#include "health.h"
#include "network.h"
#include "security.h"
#include "report.h"
#include "utils.h"

static void waitForEnter(void)
{
    int c;

    printf("\nPress ENTER to continue...");
    while ((c = getchar()) != '\n' && c != EOF);

    getchar();
}

static void clearScreen(void)
{
#ifdef __linux__
    system("clear");
#else
    system("cls");
#endif
}

int main(void)
{
    int choice;

    while (1)
    {
        clearScreen();

        showMenu();

        printf("\nChoice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input.\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                clearScreen();
                showSystemInfo();
                waitForEnter();
                break;

            case 2:
                clearScreen();
                showHealth();
                waitForEnter();
                break;

            case 3:
                clearScreen();
                showNetwork();
                waitForEnter();
                break;

            case 4:
                clearScreen();
                showSecurity();
                waitForEnter();
                break;

            case 5:
                clearScreen();
                generateReport();
                waitForEnter();
                break;
                
            case 0:
                clearScreen();
                printf("Thank you for using SysGuard.\n");
                return 0;

            default:
                printf("\nInvalid option.\n");
                waitForEnter();
        }
    }

    return 0;
}