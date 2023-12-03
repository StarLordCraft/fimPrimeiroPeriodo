#ifndef PAYMENT_MODEL_H
#define PAYMENT_MODEL_H

#include "sarahQL/contentDescriptor.h"
#include "sarahQL/where.h"

typedef struct {
    const char *payment_id;
    const char *payer_id;
    const char *receptor_id;
    double value;
}Payment;

const char *payment_table = "payment";

FieldDescriptor paymentFields[] = {
    {"payment_id", STRING, offsetof(Payment, payment_id)},
    {"payer_id", STRING, offsetof(Payment, payer_id)},
    {"receptor_id", STRING, offsetof(Payment, receptor_id)},
    {"value", DOUBLE, offsetof(Payment, value)}
};

ContentDescriptor paymentSchema = {
    userFields,
    sizeof(Payment)
};

#endif