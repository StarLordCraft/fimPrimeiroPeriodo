#include "client/loadScreens.h"
#include "sarahQL/createTable.h"
#include <string.h>

int main(int argc, char **argv) {
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif
    
    setBaseDbPath("../includes/server/database");

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