#ifndef AUTH_H
#define AUTH_H

typedef struct
{
    char *username;
    char *email;
    char *senha;
} AuthData;

void signin();

void login();

void renderLogin();

void renderRegister();

#endif