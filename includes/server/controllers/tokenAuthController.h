#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

void *tokenAuthGET(void *request);

void *tokenAuthPOST(void *request);

void *tokenAuthPUT(void *request);

void *tokenAuthDELETE(void *request);

void initTokenAuthController();
#endif