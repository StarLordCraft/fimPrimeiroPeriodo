#include "rafaGraphics/screens.h"
#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"
#include "rafaGraphics/input.h"

AppStateManager *appStateManager = NULL;

Box *initScreen(unsigned short borderSize)
{
    unsigned short *windowSizes = getWindowSize();
    Box *window = createBox(windowSizes[0], windowSizes[1], 0, 0);
    createBorder(window, borderSize, "_");
    
    free(windowSizes);
    return window;
}

void addScreen(RenderScreen screen) {
    appStateManager->screens = realloc(appStateManager->screens, (appStateManager->numScreens + 1) * sizeof(RenderScreen));
    appStateManager->screens[appStateManager->numScreens] = screen;
    appStateManager->numScreens++;
}

void resetScreen()
{
    freeScreenButtons();
    freeScreenInputs();
    clearScreen();
}

AppStateManager *getScreens() {
    if (!appStateManager) {
        appStateManager = (AppStateManager *)malloc(sizeof(AppStateManager));
        appStateManager->screens = NULL;
        appStateManager->numScreens = 0;
        appStateManager->last = 0;
    }
    return appStateManager;
}

void changeScreen(RenderScreen renderScreen)
{
    ++appStateManager->last;

    freeScreenButtons();
    freeScreenInputs();
    clearScreen();
    
    renderScreen();
}

void freeScreens(RenderScreen *screens)
{ free(screens); }