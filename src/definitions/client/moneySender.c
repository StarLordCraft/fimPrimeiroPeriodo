#include "client/views/moneySender.h"

#include "client/views/home.h"
#include "client/client.h"

#include "rafaGraphics/box.h"
#include "rafaGraphics/button.h"
#include "rafaGraphics/input.h"
#include "rafaGraphics/screens.h"

#include "server/server.h"

#include "models/PaymentModel.h"

void sendMoney()
{
    Payment *payment = (Payment *)malloc(sizeof(Payment));
    strcpy(payment->receptor_id, selectedUser->user_id);
    strcpy(payment->payer_id, user->user_id);

    char str[5];
    strcpy(str, findInputByValue("quantia").text);
    char *endptr;
    payment->value = strtod(str, &endptr);

    findControllerByRoute("/payment")->POST(payment);

    changeScreen(renderHome);
}

void renderMoneySender() {
    void *accessToken = getAuthTokenCookie();
    Controller *tokenAuthController = findControllerByRoute("/auth/withtoken");

    Box *window = initScreen(1);

    unsigned short *windowCenter = getCenterPos(window, 10, TRUE, TRUE);

    Box *title = createBox(20, 5, windowCenter[0] - 7, 3); 
    createBorder(title, 1, "-");
    unsigned short *titleTextPos = getCenterPos(title, 14, TRUE, TRUE);
    renderText(titleTextPos[0], titleTextPos[1], "MANDAR DINHEIRO");

    Box *para = createBox(20, 5, windowCenter[0] - 7, 10);
    createBorder(para, 1, "-");
    unsigned short *paraTextPos = getCenterPos(para, 0, TRUE, TRUE);
    renderText(paraTextPos[0], paraTextPos[1], selectedUser->username);
    renderText(para->startPointX, para->startPointY - 1, "Para: ");

    Input *Quantia = createInput(10, windowCenter[0] - 5, 17, "Quantia: ", "quantia", "text");

    Button *enviar = createButton(15, 5, windowCenter[0] - 5, 21, " Enviar", sendMoney);

    renderInput(Quantia); renderButton(enviar);
    
    gambiarra(); gambiarra();
}