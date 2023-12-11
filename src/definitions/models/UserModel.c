#include "models/UserModel.h"

const char *user_table = "users";

FieldDescriptor userFields[] = {
    {"user_id", STRING, offsetof(User, user_id)},
    {"auth_token", STRING, offsetof(User, auth_token)},
    {"username", STRING, offsetof(User, username)},
    {"email", STRING, offsetof(User, email)},
    {"password", STRING, offsetof(User, password)}, 
    {"role", STRING, offsetof(User, role)}
};

ContentDescriptor userSchema = {
    userFields,
    6
};

SearchResult *paymentsToReceive(char *user_id)
{ 
    useServerDb();

    return where(payment_table, sizeof(Payment), paymentSchema, "receptor_id", user_id); 
}

SearchResult *paymentsToPay(char *user_id)
{ 
    useServerDb();

    return where(payment_table, sizeof(Payment), paymentSchema, "payer_id", user_id); 
}