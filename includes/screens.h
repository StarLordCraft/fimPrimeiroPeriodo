#include "window.h"

typedef void (*RenderScreen)();

Box *initScreen(unsigned short borderSize)
{
    unsigned short *windowSizes = getWindowSize();
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
    unsigned short *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    free(window); free(title);
    free(titleTextPos);
}

void *getScreens()
{
    RenderScreen *screens = (RenderScreen*) malloc(sizeof(RenderScreen));
    screens[0] = menu;
    return screens;
}

void freeScreens(RenderScreen *screens)
{ free(screens); }