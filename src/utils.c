#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "utils.h"

void clearScreen(void)
{
#ifdef __linux__
    system("clear");
#else
    system("cls");
#endif
}

void waitForEnter(void)
{
    int c;

    printf("\nPress ENTER to continue...");

    while((c=getchar())!='\n' && c!=EOF);

    getchar();
}

void printLine(void)
{
    printf(CYAN);
    printf("========================================================\n");
    printf(RESET);
}

void printHeader(const char *title)
{
    printLine();

    printf(CYAN BOLD);

    printf("%30s\n",title);

    printf(RESET);

    printLine();
}