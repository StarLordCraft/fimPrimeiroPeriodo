#include "server/controllers/paymentController.h"
#include "server/server.h"

#include "sarahQL/insert.h"
#include "sarahQL/where.h"
#include "sarahQL/createTable.h"

#include "models/PaymentModel.h"
#include "models/UserModel.h"

SearchResult *combineSearchResults(SearchResult *first, SearchResult *second)
{
    if (!first || !second)
    {
        return NULL;
    }

    size_t totalSize = first->matchCount + second->matchCount;
    void **combinedMatches = malloc(totalSize * sizeof(Payment));
    if (!combinedMatches)
    {
        perror("Memory allocation failed for combined matches");

        return NULL;
    }

    memcpy(combinedMatches, first->matches, first->matchCount * sizeof(Payment));
    memcpy(combinedMatches + first->matchCount, second->matches, second->matchCount * sizeof(Payment));

    SearchResult *combinedResult = malloc(sizeof(SearchResult));
    if (!combinedResult)
    {
        perror("Memory allocation failed for combined SearchResult");
        free(combinedMatches);
        return NULL;
    }

    combinedResult->matches = combinedMatches;
    combinedResult->matchCount = totalSize;

    return combinedResult;
}

SearchResult *getAllUserPayments(char *user_id)
{
     SearchResult *toReceive = paymentsToReceive(user_id);
    SearchResult *toPay = paymentsToPay(user_id);

    if (!toReceive || !toPay)
        return NULL;

    SearchResult *allPayments = combineSearchResults(toReceive, toPay);

    if(allPayments->matchCount == 0)
        return NULL;
    else
       return allPayments;
}

void *PaymentGET(void *request)
{
    User *user = (User *)request;

    return getAllUserPayments(user->user_id);
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

void initPaymentController() { createController("/payment", PaymentGET, PaymentPOST, PaymentPUT, PaymentDELETE); }