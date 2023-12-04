#include <stdlib.h>
#include <string.h>

#include "server/server.h"
#include "server/controllers/homeController.h"
#include "server/controllers/tokenAuthController.h"

#include "sarahQL/createTable.h"

Api *api = NULL;

void loadControllers()
{
    initHomeController();
    initTokenAuthController();
}

void initApi()
{
    api = (Api *) malloc(sizeof(Api));
    api->controllers = (Controller **) malloc(sizeof(Controller));
    api->size = 0;
}

void useServerDb()
{
    setBaseDbPath("./includes/server/database");
}


void addController(Controller *controller)
{
    Controller **newControllers = realloc(api->controllers, sizeof(Controller *) * (api->size + 1));
    if (newControllers == NULL)return;
    api->controllers = newControllers;
    api->controllers[api->size] = controller;
    ++api->size;
}

void createController(const char *route, Method GET, Method POST, Method PUT, Method DELETE)
{
    Controller *newController = (Controller *) malloc(sizeof(Controller));
    newController->route = route;

    newController->GET = GET;
    newController->POST = POST;
    newController->PUT = PUT;
    newController->DELETE = DELETE;

    addController(newController);
}

Controller *findControllerByRoute(const char *route)
{
    for (int i = 0; i < api->size; i++) 
        if (strcmp(api->controllers[i]->route, route) == 0) 
            return api->controllers[i];
    

    return NULL;
}

void freeApi() {
    if (api != NULL) {
        for (int i = 0; i < api->size; i++) {
            free(api->controllers[i]);
        }

        free(api->controllers);

        free(api);
        api = NULL;
    }
}