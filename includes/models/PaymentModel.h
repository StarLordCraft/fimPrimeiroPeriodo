#ifndef PAYMENT_MODEL_H
#define PAYMENT_MODEL_H

#include "sarahQL/contentDescriptor.h"
#include "sarahQL/where.h"

typedef struct {
    char payer_id[65];
    char receptor_id[65];
    double value;
}Payment;

extern const char *payment_table;

extern FieldDescriptor paymentFields[];

extern ContentDescriptor paymentSchema;

#endif