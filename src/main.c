#include "client/client.h"
#include "server/server.h"

void configureApp()
{
    setIsOpen(TRUE);

    #ifdef __linux__
        configureConsole();
    #endif

    initApi();
    loadControllers();

    initAppStateManager();
    loadScreens();
}

void finishApp()
{
    freeScreens(); freeScreenButtons(); freeScreenInputs(); freeApi();

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