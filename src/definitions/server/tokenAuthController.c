#include "server/controllers/tokenAuthController.h"
#include "server/server.h"

#include "models/UserModel.h"

#include "sarahQL/insert.h"
#include "sarahQL/where.h"

void *tokenAuthGET(void *request)
{
    useServerDb();
    SearchResult *result = where(user_table, sizeof(User), userSchema, "auth_token", request);

    if(result->matchCount == 0)
        return NULL;

    return result->matches[0];
}

void *tokenAuthPOST(void *request){ return NULL; }

void *tokenAuthPUT(void *request){ return NULL; }

void *tokenAuthDELETE(void *request){ return NULL; };

void initTokenAuthController(){ createController("/auth/withtoken", tokenAuthGET, tokenAuthPOST, tokenAuthPUT, tokenAuthDELETE); }