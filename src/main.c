#include "screens.h"

int main(int argc, char **argv) {
    configureConsole();

    RenderScreen *screens = getScreens(); 

    while(isOpen()){
        numScreenButtons = 0;
        screens[appState]();

        handleEvents();

        refresh();
    }

    freeScreens(screens);
    freeScreenButtons();

    #ifdef __linux__
        endwin();
    #endif

    return 0;
}