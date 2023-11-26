#include "rafaGraphics/box.h"
#include "rafaGraphics/screens.h"

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

void *getScreens()
{
    appStateManager = (AppStateManager *) malloc(sizeof(AppStateManager));
    return screens;
}

void changeScreen(RenderScreen renderScreen)
{
    ++appStateManager->last;
    realloc(appStateManager->screens, appStateManager->last + 1);

    freeScreenButtons();
    freeScreenInputs();
    clearScreen();
    
    renderScreen();
}

void freeScreens(RenderScreen *screens)
{ free(screens); }