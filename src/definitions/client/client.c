#include "client/client.h"
#include "client/views/menu.h"
#include "client/views/auth.h"

#include "sarahQL/createTable.h"

void loadScreens()
{
    addScreen(renderMenu);
    addScreen(renderLogin);

    pushRecentScreen(appStateManager->screens[appStateManager->current]);
}

void useClientDatabase()
{
    setBaseDbPath("./includes/client/database");
}