#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "server/server.h"

char *generateToken(int length);

void *homeGET(void *request);

void *homePOST(void *request);

void *homePUT(void *request);

void *homeDELETE(void *request);

void initHomeController();

#endif