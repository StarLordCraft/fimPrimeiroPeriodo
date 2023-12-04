#include "server/controllers/homeController.h"

void *homeGET(void *request){
    return NULL;
}

void *homePOST(void *request){
    return NULL;
}

void *homePUT(void *request){
    return NULL;
}

void *homeDELETE(void *request){
    return NULL;
}


void initHomeController(){ createController("/home", homeGET, homePOST, homePUT, homeDELETE); }