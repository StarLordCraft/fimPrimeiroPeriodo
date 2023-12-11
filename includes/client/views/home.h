#ifndef VIEW_MENU_H
#define VIEW_MENU_H

#include "models/UserModel.h"

extern User *selectedUser;

void changeScreenLogin();

void changeScreenRegister();

void loggedHome();

void unloggedHome();

void renderHome();

#endif