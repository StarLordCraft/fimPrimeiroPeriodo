#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "./PaymentModel.h"
#include "sarahQL/where.h"
#include "server/server.h"

typedef struct{
    char user_id[64];
    char auth_token[64];
    char username[30];
    char email[64];
    char password[64];
    char role[30];
}User;

extern const char *user_table;

extern FieldDescriptor userFields[];

extern ContentDescriptor userSchema;

SearchResult *paymentsToReceive(char *user_id);

SearchResult *paymentsToPay(char *user_id);

#endif