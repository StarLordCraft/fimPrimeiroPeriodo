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
#include <string.h>

void signin()
{
    AuthData *registerData = (AuthData *) malloc(sizeof(AuthData));

    char usernameInput[31];
    char emailInput[65];
    char senhaInput[65];

    strcpy(usernameInput, findInputByValue("username").text);
    strcpy(emailInput, findInputByValue("email").text);
    strcpy(senhaInput, findInputByValue("password").text);

    registerData->username = strdup(usernameInput);
    registerData->email = strdup(emailInput);
    registerData->senha = strdup(senhaInput);
    
    User *user = (User *) (findControllerByRoute("/auth/withtoken"))->POST(registerData);

    if(!user)
    {

    }else{
        useClientDatabase();

        char fullPath[256];

        snprintf(fullPath, sizeof(fullPath), "%s/cookies.bin", baseDbPath);

        FILE *file = fopen(fullPath, "wb");

        if (file != NULL) {
        
            size_t tokenLen = strlen(user->auth_token);
            fwrite(user->auth_token, 1, tokenLen, file);

            
            fclose(file);
        }
    }
    changeScreen(renderHome);
    free(user); free(registerData);
}

void login()
{
    AuthData *loginData = (AuthData *) malloc(sizeof(AuthData));

    char emailInput[65];
    char senhaInput[65];

    strcpy(emailInput, findInputByValue("email").text);
    strcpy(senhaInput, findInputByValue("password").text);

    loginData->email = strdup(emailInput);
    loginData->senha = strdup(senhaInput);
 
    User *user = (User *) findControllerByRoute("/home")->POST(loginData);
    if(!user)
    {

    }else{
        useClientDatabase();

        char fullPath[256];

        snprintf(fullPath, sizeof(fullPath), "%s/cookies.bin", baseDbPath);

        FILE *file = fopen(fullPath, "wb");

        if (file != NULL) {
        
            size_t tokenLen = strlen(user->auth_token);
            fwrite(user->auth_token, 1, tokenLen, file);

            
            fclose(file);
        }
    }
    changeScreen(renderHome);
    free(user); free(loginData);
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


void renderRegister()
{
    Box *window = initScreen(1);


    gambiarra();

    Input *Email = createInput(64, 10, 10, "Email:", "email", "email");
    Input *username = createInput(20, 10, 5, "Username:", "username", "email");
    Input *Senha = createInput(64, 10, 15, "Senha:", "password", "password");

    Button *registrar = createButton(14, 5, getCenterPos(window, 7, true, false)[0], 20, "Registrar", signin);

    renderInput(username); renderInput(Email); renderInput(Senha);
    renderButton(registrar);

}