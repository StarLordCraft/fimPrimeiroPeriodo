#include "window.h"

typedef void (*RenderScreen)();

typedef enum {
    MENU,
    LOGIN,
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
 * @brief troca pra tela main
 * 
 * @return void
*/
void entrar()
{
    clearScreen(); 
    appState = MAIN; 
}

/**
 * @brief desenha na tela o menu inicial
 * 
 * @return void
*/
void menu()
{
    
    Box *window = initScreen(1);
    unsigned short windowCenterX = getCenterPos(window, 10, TRUE, FALSE)[0];
    Box *title = createBox(10, 5, windowCenterX, 3);
    createBorder(title, 1);
    unsigned short *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    Button *Entrar = createButton(10, 5, windowCenterX, 15, "Entrar", entrar);

    free(window); free(title);
    free(titleTextPos); free(Entrar);
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
 * @brief define as telas a serem utilizadas no programa e retorna elas em um array
 * 
 * @return void * retorna um array de funções que desenham as telas 
*/
void *getScreens()
{
    RenderScreen *screens = (RenderScreen*) malloc(sizeof(RenderScreen) * 3);
    screens[MENU] = menu;
    screens[LOGIN] = login;
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