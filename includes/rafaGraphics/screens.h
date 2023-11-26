#ifndef SCREENS_H
#define SCREENS_H

#include "rafaGraphics/box.h"
#include <stdlib.h>

typedef void (*RenderScreen)();

typedef struct {
    unsigned short last;
    RenderScreen *screens;
}AppStateManager;

AppStateManager *appStateManager;

RenderScreen *screens;

/***
 * @brief Uma box que representa a janela inteira
 *
 * @param borderSize tamanho da borda da janela
 * @return Box retorna uma Box que representa a janela do app
*/
Box *initScreen(unsigned short borderSize);

/**
 * @brief limpar coisas da tela anterior
*/
void resetScreen();

/**
 * @brief define as telas a serem utilizadas no programa e retorna elas em um array
 * 
 * @return void * retorna um array de funções que desenham as telas 
*/
void *getScreens();

/**
 * @brief decorator pra funções de trocar a tela
*/
void changeScreen(RenderScreen renderScreen);

/**
 * @brief libera memoria alocada de um objeto RenderScreen
 * 
 * @param screens array de RenderScreen a ter memória liberada
 * @return void
*/
void freeScreens(RenderScreen *screens);

#endif