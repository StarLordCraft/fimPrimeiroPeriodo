#include "server/controllers/paymentController.h"
#include "server/server.h"

#include "sarahQL/insert.h"
#include "sarahQL/where.h"
#include "sarahQL/createTable.h"

#include "models/PaymentModel.h"

void *PaymentGET(void *request)
{
    return NULL;
}

void *PaymentPOST(void *request)
{
    useServerDb();

    insert(request, payment_table, sizeof(Payment));

    return NULL;
}

void *PaymentPUT(void *request)
{
    return NULL;
}

void *PaymentDELETE(void *request)
{
    return NULL;
}

void initPaymentController(){ createController("/payment", PaymentGET, PaymentPOST, PaymentPUT, PaymentDELETE); }