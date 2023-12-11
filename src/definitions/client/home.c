#include "client/views/home.h"

#include "sarahQL/createTable.h"

#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"

#include "client/views/auth.h"
#include "client/client.h"

#include "server/controllers/homeController.h"

#include "models/UserModel.h"


User *selectedUser = NULL;

void changeScreenLogin()
{
    changeScreen(renderLogin);
}

void changeScreenRegister()
{
    changeScreen(renderRegister);
}

void logout()
{
    useClientDatabase();

    char fullPath[256];

    snprintf(fullPath, sizeof(fullPath), "%s/cookies.bin", baseDbPath);

    FILE *file = fopen(fullPath, "wb");

    if (file != NULL)
    {

        size_t tokenLen = strlen("");
        fwrite("", 1, tokenLen, file);

        fclose(file);
    }

    changeScreen(renderHome);
}


void send(void *user){
    selectedUser = (User *) user;
}

void unloggedHome()
{
    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);

    Box *title = createBox(10, 5, windowCenter[0] + 3, 3);
    createBorder(title, 1, "-");
    unsigned short *titleTextPos = getCenterPos(title, 4, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MENU");

    Button *Entrar = createButton(15, 5, windowCenter[0], windowCenter[1], " Entrar", changeScreenLogin);
    Button *Cadastrar = createButton(15, 5, windowCenter[0], (windowCenter[1] + Entrar->height + 2), "Cadastrar", changeScreenRegister);

    renderButton(Entrar);
    renderButton(Cadastrar);
}

void createButtonGrid(SearchResult *users, Box *div, unsigned short btnWidth, unsigned short btnHeight, unsigned short spaceBetween) {
    if (!users || !div) return;

    unsigned short x = 1 + div->startPointX; // Inicia na posição X da div + margem
    unsigned short y = 1 + div->startPointY; // Inicia na posição Y da div + margem
    unsigned short maxX = div->startPointX + div->width - btnWidth; // Limite máximo em X
    unsigned short maxY = div->startPointY + div->height - btnHeight; // Limite máximo em Y

    for (size_t i = 0; i < users->matchCount; ++i) {
        
        if (x > maxX) {
            x = 1 + div->startPointX;
            y += btnHeight + spaceBetween;
        }

        if (y > maxY) {
            break;
        }

        Button *userBtn = createButton(btnWidth, btnHeight, x, y, ((User *)users->matches[i])->username, send);
        buttonWithUserData(userBtn, users->matches[i]);
        renderButton(userBtn);

        x += btnWidth + spaceBetween;
    }
}

void loggedHome(User *user)
{
    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);

    Box *div = createBox(window->width - 10, window->height - 10, 5, 9);
    createBorder(div, 1, "#");

    Button *extrato = createButton(15, 5, 10, 3, "Extrato", NULL);
    Button *sair = createButton(15, 5, window->width - 21, 3, "Sair", logout);

    SearchResult *users = (SearchResult *) findControllerByRoute("/home")->GET(NULL);

    createButtonGrid(users, div, 10, 5, 2);

    renderButton(extrato); renderButton(sair);
}

void renderHome()
{
    void *accessToken = getAuthTokenCookie();
    Controller *tokenAuthController = findControllerByRoute("/auth/withtoken");

    User *user = (User *)tokenAuthController->GET(accessToken);

    if (!user)
        unloggedHome();
    else
        loggedHome(user);
}
