#include "client/loadScreens.h"
#include "sarahQL/createTable.h"
#include <string.h>

int main(int argc, char **argv) {
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif
    
    setBaseDbPath("../includes/server/database");

    initAppStateManager();
    loadScreens();

    while(isOpen())
        runApp();

    freeScreens();
    freeScreenButtons(); freeScreenInputs();

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}