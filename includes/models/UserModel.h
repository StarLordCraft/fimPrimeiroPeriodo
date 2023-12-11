#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "./PaymentModel.h"
#include "sarahQL/where.h"
#include "server/server.h"

typedef struct{
    char user_id[65];
    char auth_token[65];
    char username[31];
    char email[65];
    char password[65];
    char role[31];
}User;

extern const char *user_table;

extern FieldDescriptor userFields[];

extern ContentDescriptor userSchema;

SearchResult *paymentsToReceive(char *user_id);

SearchResult *paymentsToPay(char *user_id);

#endif