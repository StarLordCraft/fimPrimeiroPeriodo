#include "screens.h"

int main() {
    configureConsole();

    Screen *screens = getScreens();
    unsigned short appState = 0;

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