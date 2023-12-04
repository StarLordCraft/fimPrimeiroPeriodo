#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "./PaymentModel.h"
#include "sarahQL/where.h"
#include "server/server.h"

typedef struct{
    const char *user_id;
    const char *auth_token;
    char *username;
    char *email;
    char *password;
    char *role;
}User;

extern const char *user_table;

extern FieldDescriptor userFields[];

extern ContentDescriptor userSchema;

SearchResult *paymentsToReceive(char *user_id);

SearchResult *paymentsToPay(char *user_id);

#endif