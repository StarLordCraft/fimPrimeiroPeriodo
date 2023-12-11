#include "client/views/auth.h"

#include "rafaGraphics/button.h"
#include "rafaGraphics/box.h"
#include "rafaGraphics/screens.h"
#include "rafaGraphics/input.h"

#include "sarahQL/createTable.h"

#include "server/server.h"

#include "models/UserModel.h"

#include "client/views/home.h"
#include "client/client.h"

#include <stdbool.h>


void login()
{
    char *email = screenInputs[0].value; char *senha = screenInputs[1].value;

    LoginData *loginData = (LoginData *) malloc(sizeof(LoginData));

    loginData->email = strdup(email);
    loginData->senha = strdup(senha);
    
    User *user = findControllerByRoute("/home")->PUT(loginData);
    if(!user){

    }else {
        useClientDatabase();

        char fullPath[256];

        snprintf(fullPath, sizeof(fullPath), "%s/cookies.bin", baseDbPath);

        FILE *file = fopen(fullPath, "wb");

        if (file != NULL) {
        
            size_t tokenLen = strlen(user->auth_token);
            fwrite(user->auth_token, 1, tokenLen, file);

            
            fclose(file);
        }
        
        changeScreen(renderHome);
    }
    
}

void renderLogin()
{
    Box *window = initScreen(1);
    Input *Email = createInput(64, 10, 5, "Email:", "email", "email");
    Input *Senha = createInput(64, 10, 10, "Senha:", "password", "password");
    Button *entrar = createButton(14, 5, getCenterPos(window, 7, true, false)[0], 15, "Entrar", login);

    renderInput(Email); renderInput(Senha);
    renderButton(entrar);
    
    gambiarra();
}
