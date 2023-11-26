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
        appStateManager->recentScreens = NULL;
        appStateManager->numScreens = 0;
        appStateManager->current = 0;
        appStateManager->recentTop = -1;
    }
    return appStateManager;
}

void pushRecentScreen(RenderScreen screen) {
    appStateManager->recentScreens = realloc(appStateManager->recentScreens, (appStateManager->recentTop + 1) * sizeof(RenderScreen));
    appStateManager->recentScreens[appStateManager->recentTop] = screen;
    ++appStateManager->recentTop;
}

void changeScreen(RenderScreen renderScreen) {
    pushRecentScreen(appStateManager->screens[appStateManager->current]);

    for(int i = 0; i < appStateManager->numScreens; ++i)
        if(appStateManager->screens[i] == renderScreen){
            appStateManager->current = i;
            break;
        };

    resetScreen();
}

void backScreen() {
    if (appStateManager->recentTop < 0) return;

    RenderScreen previousScreen = appStateManager->recentScreens[--appStateManager->recentTop];

    for(int i = 0; i < appStateManager->numScreens; ++i)
        if(appStateManager->screens[i] == previousScreen){
            appStateManager->current = i;
            break;
        };

    resetScreen();
}

void freeScreens() 
{
    free(appStateManager->screens);
    free(appStateManager->recentScreens);
}