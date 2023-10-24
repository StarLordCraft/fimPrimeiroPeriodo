#ifndef STANDART_H
#define STANDART_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <ncurses.h>
    #include <unistd.h>
#endif

/**
 * @brief coloca na tela uma mensagem de erro e fecha o programa
 * 
 * @param message mensagem de erro
 * @return void
*/
void error(char *message);

/**
 * @brief limpa a tela
 * 
 * @return void
*/
void clearScreen();

/**
 * @brief para o programa por alguns milisegundos
 * 
 * @param milliseconds tempo de parar o programa
 * @return void
*/
void wait(unsigned int milliseconds);

#endif