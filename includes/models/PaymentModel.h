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

extern const char *payment_table;

extern FieldDescriptor paymentFields[];

extern ContentDescriptor paymentSchema;

#endif