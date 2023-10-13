#include "screens.h"

int main() {
    configureConsole();

    Screen *screens = getScreens();

    while(TRUE){
        boolean open = handleEvents();

        screens[0]();
        
        refresh();
        if(!open)break;
    }


    #ifdef __linux__
        endwin();
    #endif

    return 0;
}