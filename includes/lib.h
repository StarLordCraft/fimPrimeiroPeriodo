#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

void error(char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif 

    printf("\033[2J\033[1;1H");
}

typedef enum {
    FALSE,
    TRUE,
} boolean;
#endif