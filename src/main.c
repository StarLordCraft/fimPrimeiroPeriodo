#include "screens.h"

int main(int argc, char **argv) {
    configureConsole();

    RenderScreen *screens = getScreens(); 

    while(isOpen()){
        screens[appState]();
        
        refresh();

        handleEvents();
    }

    freeScreens(screens);
    freeScreenButtons(); freeScreenInputs();

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}