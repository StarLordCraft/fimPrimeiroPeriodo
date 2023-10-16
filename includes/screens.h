#include "window.h"

typedef void (*Screen)();

Box *initScreen(int borderSize)
{
    int *windowSizes = getWindowSize();
    Box *window = createBox(windowSizes[0], windowSizes[1], 0, 0);
    createBorder(window, borderSize);
    
    free(windowSizes);
    return window;
}

void menu()
{
    Box *window = initScreen(1);
    Box *title = createBox(10, 5, getCenterPos(window, 10, TRUE, FALSE)[0], 3);
    createBorder(title, 1);
    int *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    free(window); free(title);
    free(titleTextPos);
}

void *getScreens()
{
    Screen *screens = (Screen*) malloc(sizeof(Screen));
    screens[0] = menu;
    return screens;
}

void freeScreens(Screen *screens)
{ free(screens); }