#include "client/loadScreens.h"
#include "client/views/menu.h"
#include "client/views/auth.h"

void loadScreens()
{
    addScreen(renderMenu);
    addScreen(renderLogin);
}