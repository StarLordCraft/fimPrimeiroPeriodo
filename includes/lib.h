#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void error(char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
        printf("\033[2J\033[1;1H");
    #endif

}

typedef enum {
    FALSE,
    TRUE,
} boolean;
#endif