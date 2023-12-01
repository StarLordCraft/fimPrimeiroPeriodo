#include "client/loadScreens.h"

int main(int argc, char **argv) {
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif

    AppStateManager *appStateManager = getScreens();

    loadScreens();

    while(isOpen()){
        appStateManager->screens[appStateManager->last]();

        handleEvents();
    }

    freeScreens(appStateManager->screens);
    freeScreenButtons(); freeScreenInputs();

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}