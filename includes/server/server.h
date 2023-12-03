#ifndef SERVER_H
#define SERVER_H
#include "server/api/api.h"

#include "server/api/controllers/homeController.h"

void loadControllers()
{
    initHomeController();
}

#endif