#include "window.h"

Box *initScreen(int borderSize)
{
    int *windowSizes = getWindowSize();
    Box *window = createBox(windowSizes[0], windowSizes[1], 0, 0);
    createBorder(window, borderSize);
    
    return window;
}

void menu()
{
    Box *window = initScreen(1);
    Box *title = createBox(10, 5, getCenterPos(window, "1111111111", TRUE, FALSE)[0], 3);
    createBorder(title, 1);
    int *titleTextPos = getCenterPos(title, "MENU", TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    free(window); free(title);
}