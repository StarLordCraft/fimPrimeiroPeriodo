#include "client/loadScreens.h"

int main(int argc, char **argv) {
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif

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