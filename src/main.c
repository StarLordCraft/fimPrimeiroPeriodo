#include "screens.h"

int main(int argc, char **argv) {
    setIsOpen(TRUE);
    #ifdef __linux__
        configureConsole();
    #endif

    RenderScreen *screens = getScreens(); 

    while(isOpen()){
        screens[appState]();
        
        #ifdef __linux__
            refresh();
        #endif

        handleEvents();
    }

    freeScreens(screens);
    freeScreenButtons(); freeScreenInputs();

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}