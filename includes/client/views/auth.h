#ifndef AUTH_H
#define AUTH_H

typedef struct {
    char *email;
    char *senha;
}LoginData;

void login();

void renderLogin();

#endif