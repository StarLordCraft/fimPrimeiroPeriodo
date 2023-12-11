#include "client/views/home.h"

#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"

#include "client/views/auth.h"
#include "client/client.h"

#include "server/controllers/homeController.h"
#include "models/UserModel.h"

void changeScreenLogin()
{
    changeScreen(renderLogin);
}


void changeScreenRegister()
{
    changeScreen(renderRegister);
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
    
    renderButton(Entrar); renderButton(Cadastrar);
}

void renderHome()
{
    void *accessToken = getAuthTokenCookie();
    Controller *tokenAuthController = findControllerByRoute("/auth/withtoken");

    User *user = tokenAuthController->GET(accessToken);

    if(!user)
        unloggedHome();
}
