#ifndef PAYMENT_CONTROLLER_H
#define PAYMENT_CONTROLLER_H

void *PaymentGET(void *request);

void *PaymentPOST(void *request);

void *PaymentPUT(void *request);

void *PaymentDELETE(void *request);

void initPaymentController();
#endif