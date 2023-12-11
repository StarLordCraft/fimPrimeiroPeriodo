#include "server/controllers/tokenAuthController.h"
#include "server/server.h"

#include "models/UserModel.h"

#include "sarahQL/insert.h"
#include "sarahQL/where.h"

#include "client/views/auth.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char *generateToken(int length)
{
    static int initialized = 0;
    if (!initialized)
    {
        srand((unsigned) time(NULL));
        initialized = 1;
    }

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *token = (char *)malloc((length + 1) * sizeof(char));

    if (token)
    {
        for (int i = 0; i < length; i++)
        {
            int index = rand() % (sizeof(charset) - 1);
            token[i] = charset[index];
        }
        token[length] = '\0';
    }

    return token;
}
void *tokenAuthGET(void *request)
{
    useServerDb();
    SearchResult *result = where(user_table, sizeof(User), userSchema, "auth_token", ((char *)request));

    if (result->matchCount == 0)
        return NULL;
    else
    {
        User *user = (User *)result->matches[0];
        return user;
    }
}

void *tokenAuthPOST(void *request)
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

void *tokenAuthPUT(void *request) { return NULL; }

void *tokenAuthDELETE(void *request) { return NULL; };

void initTokenAuthController() { createController("/auth/withtoken", tokenAuthGET, tokenAuthPOST, tokenAuthPUT, tokenAuthDELETE); }