#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

/**
 * @brief coloca na tela uma mensagem de erro e fecha o programa
 * 
 * @param message mensagem de erro
 * @return void
*/
void error(char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    #ifdef __linux__
        endwin();
    #endif
    exit(1);
}


/**
 * @brief limpa a tela
 * 
 * @return void
*/
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
        printf("\033[2J\033[1;1H");
    #endif

}

/**
 * @brief para o programa por alguns milisegundos
 * 
 * @param milliseconds tempo de parar o programa
 * @return void
*/
void wait(unsigned int milliseconds)
{
    #ifdef _WIN32
         Sleep(milliseconds);
    #elif defined(__linux__)
        usleep(milliseconds * 1000);
    #endif
}

typedef enum {
    FALSE,
    TRUE,
} boolean;
#endif