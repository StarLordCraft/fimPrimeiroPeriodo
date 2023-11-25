#ifndef BUTTON_H
#define BUTTON_H

#include "box.h"

/**
 * @brief
 * Essa struct serve pra criar armazenar e manipular estruturas analogas a button no html
 */
typedef struct
{
    unsigned short width;
    unsigned short height;
    unsigned short startPointX;
    unsigned short startPointY;

    const char *text;

    void (*onClick)();
} Button;

/// @section Global Variables
extern Button *screenButtons;
extern unsigned short numScreenButtons;
/// @endparblock

/**
 * @brief Adiciona um botão ao array de botões para processar eventos de clique.
 *
 * @param button O botão a ser adicionado ao array.
 * @return void
 */
void addButtonToScreen(Button *button);

/**
 * @brief Renderiza um botão na tela.
 *
 * @param button O botão a ser renderizado na tela.
 * @return void
 */
void renderButton(Button *button);

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
                     unsigned short startPointY, const char *label, void (*callBack)(void));

/**
 * @brief Testa se um botão foi clicado
 *
 * @param button botão a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void handleButtonEvent(Button *button, unsigned short mouseX, unsigned short mouseY);
/**
 * @brief Reseta o array de botões para receber os botões de uma outra tela.
 *
 * @return void
 */
void freeScreenButtons();

#endif