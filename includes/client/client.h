#ifndef LOAD_SCREENS_H
#define LOAD_SCREENS_H
#include "rafaGraphics/screens.h"
#include "rafaGraphics/button.h"
#include "rafaGraphics/input.h"

/**
 * @brief carrega as telas do app
*/
void loadScreens();

/**
 * @brief set to use client db
*/
void useClientDatabase();

/**
 * @brief verifica nos cookies se o usuário tem token de autenticação
*/
char *getAuthTokenCookie();

#endif