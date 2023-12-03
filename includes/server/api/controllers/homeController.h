#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H
#include "server/api/api.h"

void *GET(void *request){
    return NULL;
}

void *POST(void *request){
    return NULL;
}

void *PUT(void *request){
    return NULL;
}

void *DELETE(void *request){
    return NULL;
};

void initHomeController(){ createController("/home", GET, POST, PUT, DELETE); }

#endif