#ifndef SCREENS_H
#define SCREENS_H

#include "rafaGraphics/box.h"
#include "standart.h"

typedef void (*RenderScreen)();

typedef struct AppStateManager {
    RenderScreen *screens;
    RenderScreen *recentScreens;
    unsigned short numScreens;
    unsigned short current;
    int recentTop;
} AppStateManager;

extern AppStateManager *appStateManager;

/***
 * @brief Uma box que representa a janela inteira
 *
 * @param borderSize tamanho da borda da janela
 * @return Box retorna uma Box que representa a janela do app
*/
Box *initScreen(unsigned short borderSize);

void addScreen(RenderScreen screen);

/**
 * @brief limpar coisas da tela anterior
*/
void resetScreen();

/**
 * @brief define as telas a serem utilizadas no programa e retorna elas em um array
 * 
 * @return void * retorna um array de funções que desenham as telas 
*/
AppStateManager *getScreens();

/**
 * @brief decorator pra funções de trocar a tela
*/
void changeScreen(RenderScreen renderScreen);

/**
 * @brief adiciona uma tela pra pilha de telas de navegação
 * @param screen tela a ser adicionada
*/
void pushRecentScreen(RenderScreen screen);

/**
 * @brief navega pra trás nas telas
*/
void backScreen();

/**
 * @brief libera memoria alocada de um objeto RenderScreen
 * 
 * @param screens array de RenderScreen a ter memória liberada
 * @return void
*/
void freeScreens();

#endif