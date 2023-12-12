#include "server/controllers/homeController.h"

#include "sarahQL/where.h"
#include "sarahQL/insert.h"
#include "sarahQL/selectAll.h"

#include "models/UserModel.h"

#include "client/views/auth.h"

void *homeGET(void *request)
{
    useServerDb();
    return selectAll(sizeof(User), user_table);
}

void *homePOST(void *request)
{
    AuthData *req = (AuthData *)request;

    SearchResult *result = where(user_table, sizeof(User), userSchema, "email", req->email);

    User *existingUser = NULL;

    if (result && result->matchCount > 0)
        existingUser = result->matches[0];
    if (existingUser)
    {
        if (strcmp(existingUser->password, req->senha) == 0)
            return existingUser;
    }
    return NULL;
}

void *homePUT(void *request)
{
    return NULL;
}

void *homeDELETE(void *request)
{
    return NULL;
}

void initHomeController() { createController("/home", homeGET, homePOST, homePUT, homeDELETE); }