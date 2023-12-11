#include "server/controllers/homeController.h"

#include "sarahQL/where.h"
#include "sarahQL/insert.h"

#include "models/UserModel.h"

#include "client/views/auth.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char *generateToken(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *token = (char *)malloc((length + 1) * sizeof(char));
    
    if (token) {
        for (int i = 0; i < length; i++) {
            int index = rand() % (sizeof(charset) - 1);
            token[i] = charset[index];
        }
        token[length] = '\0';
    }
    
    return token;
}


void *homeGET(void *request)
{
    return NULL;
}

void *homePOST(void *request)
{
    AuthData *req = (AuthData *)request;

    useServerDb();

    SearchResult *result = where(user_table, sizeof(User), userSchema, "email", req->email);

    User *existingUser = NULL;

    if (result && result->matchCount > 0) 
        existingUser = result->matches[0];
    

    if (existingUser)
        return NULL;

    else
    {
        User *newUser = (User *)malloc(sizeof(User));
        
        strcpy(newUser->username, req->username);
        strcpy(newUser->email, req->email);
        strcpy(newUser->password, req->senha);
        strcpy(newUser->user_id, generateToken(64));
        strcpy(newUser->auth_token, generateToken(64));

        insert(newUser, user_table, sizeof(User));

        return newUser;
    }
}

void *homePUT(void *request)
{
    AuthData *req = (AuthData *)request;

    User *user = where(user_table, sizeof(User), userSchema, "email", req->email)->matches[0];

    if (!user)
        return NULL;
    else
    {
        if (strcmp(user->password, req->senha) == 0)
            return user;
        else
            return NULL;
    }
}

void *homeDELETE(void *request)
{
    return NULL;
}

void initHomeController() { createController("/home", homeGET, homePOST, homePUT, homeDELETE); }