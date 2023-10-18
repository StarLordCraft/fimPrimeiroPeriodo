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
    createBorder(window, borderSize, "_");
    
    free(windowSizes);
    return window;
}

void resetScreen()
{
    freeScreenButtons();
    freeScreenInputs();
    clearScreen();
}

/**
 * @brief troca pra tela de login
 * 
 * @return void
*/
void changeScreenLogin()
{
    resetScreen(); 
    appState = LOGIN; 
}

/**
 * @brief troca pra tela de login
 * 
 * @return void
*/
void changeScreenRegister()
{
    resetScreen(); 
    appState = CADASTRO; 
}

/**
 * @brief desenha na tela o menu inicial
 * 
 * @return void
*/
void renderMenu()
{    
    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);
    
    Box *title = createBox(10, 5, windowCenter[0] + 3, 3);
    createBorder(title, 1, "-");
    unsigned short *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    Button *Entrar = createButton(15, 5, windowCenter[0], windowCenter[1], " Entrar", changeScreenLogin);
    Button *Cadastrar = createButton(15, 5, windowCenter[0], (windowCenter[1] + Entrar->height + 2), "Cadastrar", changeScreenRegister);

    free(window); free(title); free(titleTextPos); free(windowCenter);
}


/**
 * @brief desenha na tela o ponto de login
 * 
 * @return void
*/
void renderLogin()
{
    Box *window = initScreen(1);
    Input *Email = createInput(10, 10, 10, "Email:");

    free(window);
}

/**
 * @brief desenha na tela o ponto de register
 * 
 * @return void
*/
void renderRegister()
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
    screens[MENU] = renderMenu;
    screens[LOGIN] = renderLogin;
    screens[CADASTRO] = renderRegister;
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