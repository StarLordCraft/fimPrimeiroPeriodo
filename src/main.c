#include "screens.h"

int main() {
    configureConsole();
    while(TRUE){
        boolean open = handleEvents();

        menu();
        
        refresh();
        if(!open)break;
    }
    
    #ifdef __linux__
        endwin();
    #endif

    return 0;
}