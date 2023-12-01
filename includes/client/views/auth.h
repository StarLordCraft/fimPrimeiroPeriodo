#ifndef AUTH_H
#define AUTH_H

#include "rafaGraphics/button.h"
#include "rafaGraphics/box.h"
#include "rafaGraphics/screens.h"
#include "rafaGraphics/input.h"

void renderLogin()
{
    Box *window = initScreen(1);
    Input *Email = createInput(64, 10, 10, "Email:", "email", "email");
    Input *Senha = createInput(64, 10, 15, "Senha:", "password", "password");

    renderInput(Email); renderInput(Senha);
    gambiarra();
}

#endif