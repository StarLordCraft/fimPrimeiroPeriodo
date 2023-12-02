#include "client/loadScreens.h"
#include "sarahQL/createTable.h"

void configureApp()
{
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif

    initAppStateManager();
    loadScreens();
}

void finishApp()
{
    freeScreens();
    freeScreenButtons(); freeScreenInputs();

    #ifdef __linux__
        endwin();
    #endif

}

int main(int argc, char **argv) {
    configureApp();

    while(isOpen())
        runApp();
    
    finishApp();

    return 0;
}