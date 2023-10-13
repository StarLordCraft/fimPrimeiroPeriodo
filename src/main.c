#include "screens.h"

int main() {
    configureConsole();

    Screen *screens = getScreens();
    unsigned short appState = 0;

    while(TRUE){
        boolean open = handleEvents();

        screens[appState]();
        
        refresh();
        if(!open)break;
    }

    freeScreens(screens);

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}