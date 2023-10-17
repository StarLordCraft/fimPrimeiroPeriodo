#ifndef SCREENS_H
#define SCREENS_H

#include "interactiveElements.h"

typedef void (*RenderScreen)();

typedef enum {
    MENU,
    LOGIN,
    CADASTRO,
}AppState;

AppState appState = MENU;

/***
 * @brief Uma box que representa a janela inteira
 *
 * @param borderSize tamanho da borda da janela
 * @return Box retorna uma Box que representa a janela do app
*/
Box *initScreen(unsigned short borderSize)
{
    unsigned short *windowSizes = getWindowSize();
    Box *window = createBox(windowSizes[0], windowSizes[1], 0, 0);
    createBorder(window, borderSize);
    
    free(windowSizes);
    return window;
}

/**
 * @brief troca pra tela de login
 * 
 * @return void
*/
void entrar()
{
    clearScreen(); 
    appState = LOGIN; 
}

/**
 * @brief troca pra tela de login
 * 
 * @return void
*/
void cadastrar()
{
    clearScreen(); 
    appState = CADASTRO; 
}

/**
 * @brief desenha na tela o menu inicial
 * 
 * @return void
*/
void menu()
{
    numScreenButtons = 0;
    
    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);
    
    Box *title = createBox(10, 5, windowCenter[0] + 3, 3);
    createBorder(title, 1);
    unsigned short *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    Button *Entrar = createButton(15, 5, windowCenter[0], windowCenter[1], " Entrar", entrar);
    Button *Cadastrar = createButton(15, 5, windowCenter[0], (windowCenter[1] + Entrar->height + 2), "Cadastrar", cadastrar);

    free(window); free(title);
    free(titleTextPos); free(Entrar);
    free(windowCenter); free(Cadastrar);
}


/**
 * @brief desenha na tela o ponto de login
 * 
 * @return void
*/
void login()
{
    Box *window = initScreen(1);

    free(window);
}

/**
 * @brief desenha na tela o ponto de register
 * 
 * @return void
*/
void registro()
{

}

/**
 * @brief define as telas a serem utilizadas no programa e retorna elas em um array
 * 
 * @return void * retorna um array de funções que desenham as telas 
*/
void *getScreens()
{
    RenderScreen *screens = (RenderScreen*) malloc(sizeof(RenderScreen) * 4);
    screens[MENU] = menu;
    screens[LOGIN] = login;
    screens[CADASTRO] = registro;
    return screens;

}


/**
 * @brief libera memoria alocada de um objeto RenderScreen
 * 
 * @param screens array de RenderScreen a ter memória liberada
 * @return void
*/
void freeScreens(RenderScreen *screens)
{ free(screens); }

#endif