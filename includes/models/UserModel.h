#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "./PaymentModel.h"
#include "sarahQL/where.h"
#include "server/api/api.h"

typedef struct{
    const char *user_id;
    char *username;
    char *email;
    char *password;
    char *role;
}User;

const char *user_table = "user";

FieldDescriptor userFields[] = {
    {"user_id", STRING, offsetof(User, user_id)},
    {"username", STRING, offsetof(User, username)},
    {"email", STRING, offsetof(User, email)},
    {"password", STRING, offsetof(User, password)}, 
    {"role", STRING, offsetof(User, role)}
};

ContentDescriptor userSchema = {
    userFields,
    sizeof(User)
};

SearchResult *paymentsToReceive(const char *user_id)
{ 
    useServerDb();
    return where(payment_table, sizeof(Payment), paymentSchema, "receptor_id", user_id); 
}

SearchResult *paymentsToPay(const char *user_id)
{ 
    useServerDb();
    return where(payment_table, sizeof(Payment), paymentSchema, "payer_id", user_id); 
}

#endif