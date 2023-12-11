#include "server/controllers/homeController.h"

#include "sarahQL/where.h"

#include "models/UserModel.h"

typedef struct {
    char *email;
    char *senha;
}LoginData;


void *homeGET(void *request){
    return NULL;
}

void *homePOST(void *request){
    return NULL;
}

void *homePUT(void *request){
    LoginData *req = (LoginData *) request;
    
    User *user = where(user_table, sizeof(User), userSchema, "email", req->email)->matches[0];

    
    if(!user)
        return NULL;
    else {
        if(strcmp(user->password, req->senha) == 0)
            return user;
        else
            return NULL;
    }
}

void *homeDELETE(void *request){
    return NULL;
}


void initHomeController(){ createController("/home", homeGET, homePOST, homePUT, homeDELETE); }