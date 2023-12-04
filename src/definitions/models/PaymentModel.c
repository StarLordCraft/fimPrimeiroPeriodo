#include "models/PaymentModel.h"

const char *payment_table = "payments";

FieldDescriptor paymentFields[] = {
    {"payment_id", STRING, offsetof(Payment, payment_id)},
    {"payer_id", STRING, offsetof(Payment, payer_id)},
    {"receptor_id", STRING, offsetof(Payment, receptor_id)},
    {"value", DOUBLE, offsetof(Payment, value)}
};

ContentDescriptor paymentSchema = {
    paymentFields,
    sizeof(Payment)
};