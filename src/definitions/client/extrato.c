#include "client/views/extrato.h"
#include "client/views/home.h"

#include "sarahQL/createTable.h"
#include "sarahQL/where.h"

#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"

#include "client/client.h"

#include <string.h>

double amount = 0;

void createExtratoGrid(SearchResult *payments, User *currentUser, Box *div, unsigned short boxWidth, unsigned short boxHeight, unsigned short spaceBetween)
{
    if (!payments || !div)
        return;

    unsigned short x = 1 + div->startPointX;
    unsigned short y = 2 + div->startPointY;
    unsigned short maxX = div->startPointX + div->width - boxWidth;
    unsigned short maxY = div->startPointY + div->height - boxHeight;

    for (size_t i = 0; i < payments->matchCount; ++i)
    {

        if (x > maxX)
        {
            x = 1 + div->startPointX;
            y += boxHeight + spaceBetween;
        }

        if (y > maxY)
            break;

        Payment *payment = payments->matches[i];

        Box *paymentBox = createBox(boxWidth, boxHeight, x, y);
        createBorder(paymentBox, 1, "-");

        char *statusLabel;
        if (strcmp(currentUser->user_id, payment->payer_id) == 0)
        {
            statusLabel = "Pago";
            amount += payment->value;
        }
        else if (strcmp(currentUser->user_id, payment->receptor_id) == 0)
        {
            statusLabel = "Recebido";
            amount -= payment->value;
        }

        renderText(paymentBox->startPointX, paymentBox->startPointY - 1, statusLabel);

        char str[10];
        unsigned short *textPos = getCenterPos(paymentBox, 0, TRUE, TRUE);
        sprintf(str, "R$%.2f", payment->value);
        renderText(textPos[0], textPos[1], str);

        x += boxWidth + spaceBetween;
    }
}

void renderExtrato()
{
    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);

    Box *div = createBox(window->width - 10, window->height - 10, 5, 9);
    createBorder(div, 1, "#");

    SearchResult *payments = findControllerByRoute("/payment")->GET(user);

    if(payments)
        createExtratoGrid(payments, user, div, 10, 5, 2);

    Box *amountBox = createBox(15, 5, window->width - 21, 3);
    createBorder(amountBox, 1, "-");
    unsigned short *amountTextPos = getCenterPos(amountBox, 10, TRUE, TRUE);
    char str[10];
    sprintf(str, "R$%.2f", amount);
    renderText(amountTextPos[0], amountTextPos[1], str);

    gambiarra();
}