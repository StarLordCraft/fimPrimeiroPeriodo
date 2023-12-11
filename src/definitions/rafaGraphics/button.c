#include "standart.h"

#include "rafaGraphics/button.h"

/// @section GLOBAL VARIABLES
Button *screenButtons = NULL;
unsigned short numScreenButtons = 0;
/// @endparblock

/**
 * @brief Adiciona um botão ao array de botões para processar eventos de clique.
 *
 * @param button O botão a ser adicionado ao array.
 * @return void
 */
void addButtonToScreen(Button *button)
{
    ++numScreenButtons;
    screenButtons = (Button *)realloc(screenButtons, numScreenButtons * sizeof(Button));

    if (screenButtons == NULL)
        error("Falha na alocação de memória.\n");

    screenButtons[numScreenButtons - 1] = *button;
}

/**
 * @brief Renderiza um botão na tela.
 *
 * @param button O botão a ser renderizado na tela.
 * @return void
 */
void renderButton(Button *button)
{
    Box *box = createBox(button->width, button->height, button->startPointX, button->startPointY);
    createBorder(box, 1, "-");

    unsigned short *centerPos = getCenterPos(box, strlen(button->text), TRUE, TRUE);

    renderText(centerPos[0], centerPos[1], button->text);

    free(centerPos);
    free(box);
}

/**
 * @brief Cria um Button
 *
 * @param width largura do button
 * @param height altura do button
 * @param startPointX Posicionamento no eixo X do button
 * @param startPointY Posicionamento no eixo Y do button
 * @param label Texto de call to action do button
 * @param callBack o que acontece quando esse botão é clicado
 * @return Button retorna um elemento de interação renderizável na tela
 */
Button *createButton(unsigned short width, unsigned short height, unsigned short startPointX,
                     unsigned short startPointY, const char *label, void (*callBack)(void))
{
    if (screenButtons)
        for (int i = 0; i < numScreenButtons; ++i)
            if (screenButtons[i].startPointX == startPointX && screenButtons[i].startPointY == startPointY)
            {
                renderButton(&screenButtons[i]);
                return &screenButtons[i];
            }

    Button *newButton = (Button *)malloc(sizeof(Button));

    newButton->userData = NULL;
    newButton->width = width;
    newButton->height = height;
    newButton->startPointX = startPointX;
    newButton->startPointY = startPointY;
    newButton->text = label;

    newButton->onClick = callBack;

    renderButton(newButton);
    addButtonToScreen(newButton);

    return newButton;
}

void buttonWithUserData(Button *button, void *userData)
{
    button->userData = userData;
}

/**
 * @brief Testa se um botão foi clicado
 *
 * @param button botão a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void handleButtonEvent(Button *button, unsigned short mouseX, unsigned short mouseY)
{
    if (mouseX >= button->startPointX && mouseX < (button->startPointX + button->width) &&
        mouseY >= button->startPointY && mouseY < (button->startPointY + button->height))
        if (button->onClick)
            button->onClick(button->userData);
}

/**
 * @brief Reseta o array de botões para receber os botões de uma outra tela.
 *
 * @return void
 */
void freeScreenButtons()
{
    if(screenButtons){
        free(screenButtons);
        screenButtons = NULL;
        numScreenButtons = 0;
    }
}