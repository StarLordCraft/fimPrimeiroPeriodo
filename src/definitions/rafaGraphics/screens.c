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

void initAppStateManager() 
{
    if (!appStateManager) {
        appStateManager = (AppStateManager *) malloc(sizeof(AppStateManager));
        appStateManager->screens = (RenderScreen *) malloc(sizeof(RenderScreen));
        appStateManager->recentScreens = (RenderScreen *) malloc(sizeof(RenderScreen));
        appStateManager->reRender = true;
        appStateManager->numScreens = 0;
        appStateManager->current = 0;
        appStateManager->recentTop = 0;
    }
}

void pushRecentScreen(RenderScreen screen) {
    appStateManager->recentScreens = realloc(appStateManager->recentScreens, (appStateManager->recentTop + 1) * sizeof(RenderScreen));
    appStateManager->recentScreens[appStateManager->recentTop] = screen;
    ++appStateManager->recentTop;
}

void changeScreen(RenderScreen renderScreen) {
    for(int i = 0; i < appStateManager->numScreens; ++i)
        if(appStateManager->screens[i] == renderScreen){
            appStateManager->current = i;
            break;
        };

    pushRecentScreen(appStateManager->screens[appStateManager->current]);

    freeScreenButtons(); freeScreenInputs();
}

void backScreen() {
    if (appStateManager->recentTop <= 1) return; 

    --appStateManager->recentTop; 

    RenderScreen previousScreen = appStateManager->recentScreens[appStateManager->recentTop - 1];

    for(int i = 0; i < appStateManager->numScreens; ++i) {
        if(appStateManager->screens[i] == previousScreen) {
            appStateManager->current = i;
            break;
        }
    }

    appStateManager->recentScreens[appStateManager->recentTop] = NULL;

    appStateManager->reRender = true;
}

void freeScreens() 
{
    free(appStateManager->screens);
    free(appStateManager->recentScreens);
}

void runApp()
{
    if(threadCreateStatus)
        threadCreateStatus = pthread_create(&renderThreadId, NULL, renderThreadFunction, NULL);
    
    handleEvents();
}

void gambiarra()
{
    Input *voidInput = createInput(2, 0, 0, "", "", ""); 
    renderInput(voidInput);
}