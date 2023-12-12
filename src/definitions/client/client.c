#include "client/client.h"
#include "client/views/home.h"
#include "client/views/auth.h"
#include "client/views/moneySender.h"
#include "client/views/extrato.h"

#include "sarahQL/createTable.h"

void loadScreens()
{
    addScreen(renderHome); addScreen(unloggedHome); addScreen(loggedHome);
    addScreen(renderLogin); addScreen(renderRegister);
    addScreen(renderMoneySender); addScreen(renderExtrato);

    pushRecentScreen(appStateManager->screens[appStateManager->current]);
}

void useClientDatabase()
{
    setBaseDbPath("./includes/client/database");
}

char *getAuthTokenCookie()
{
    useClientDatabase();
    FILE *file;
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/cookies.bin", baseDbPath);

    file = fopen(fullPath, "rb");
    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *authToken = (char *)malloc(fileSize + 1);
    if (authToken == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    fread(authToken, 1, fileSize, file);
    authToken[fileSize] = '\0';

    fclose(file);

    return authToken;
}