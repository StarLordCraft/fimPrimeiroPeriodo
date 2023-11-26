#include "rafaGraphics/screens.h"
#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"
#include "rafaGraphics/input.h"

AppStateManager *appStateManager = NULL;
RenderScreen *screens = NULL;

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
    screens = (RenderScreen *) malloc(sizeof(AppStateManager));
    appStateManager = (AppStateManager *) malloc(sizeof(AppStateManager));
    appStateManager->last = 0;
    return screens;
}

void changeScreen(RenderScreen renderScreen)
{
    ++appStateManager->last;
    appStateManager = realloc(appStateManager->screens, appStateManager->last + 1);

    freeScreenButtons();
    freeScreenInputs();
    clearScreen();
    
    renderScreen();
}

void freeScreens(RenderScreen *screens)
{ free(screens); }