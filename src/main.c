#include "screens.h"

int main() {
    configureConsole();

    RenderScreen *screens = getScreens(); 

    while(isOpen()){
        screens[appState]();

        handleEvents();
        
        refresh();

        freeScreenButtons();
    }

    freeScreens(screens);

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}