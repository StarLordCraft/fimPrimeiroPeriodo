#include "screens.h"

int main() {
    configureConsole();

    Screen *screens = getScreens();
    unsigned short appState = 0;

    while(TRUE){
        screens[appState]();

        boolean open = handleEvents();
        
        refresh();

        free(screenButtons);
        
        if(!open)break;
    }

    freeScreens(screens);

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}