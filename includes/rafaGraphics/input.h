#ifndef INPUT_H
#define INPUT_H
#include "button.h"

typedef struct
{
    unsigned short width;
    unsigned short height;
    unsigned short startPointX;
    unsigned short startPointY;
    unsigned short cursor;

    char *text;
    unsigned short textSize;
    const char *label;
    const char *value;
    const char *type;

    bool focused;
} Input;

/// @brief GLOBAL VARIABLES
extern Input *screenInputs;
extern unsigned short numScreenInputs;
extern Input *inputFocused;

extern bool cursorVisible;
/// @endparblock end Global Variables

/**
 * @brief Adiciona um input ao array de inputs para processar eventos de clique.
 *
 * @param input O input a ser adicionado ao array.
 * @return void
 */
void addInputToScreen(Input *input);

/**
 * @brief Renderiza um input na tela e o torna clicável, adicionando-o a um array de inputs.
 *
 * @param input O input a ser renderizado na tela.
 * @return void
 */
void renderInput(Input *input);

/**
 * @brief Cria um Input
 *
 * @param width largura do Input
 * @param startPointX Posicionamento no eixo X do Input
 * @param startPointY Posicionamento no eixo Y do Input
 * @param label Texto de call to action do Input
 * @param value tipo um id a ser tratado la no backend
 * @param type tipo de input
 * @return Input retorna um elemento de interação renderizável na tela
 */
Input *createInput(unsigned short width, unsigned short startPointX, unsigned short startPointY,
                   const char *label, const char *value, const char *type);

/**
 * @brief move o cursor para uma determinada posição no text
 *
 * @param to pra onde o cursor vai
 * @return void
 */
void moveCursor(Input *input, unsigned short to);

/**
 * @brief preserva o texto e remove o cursor dele.
 *
 * @return void
 */
void removeCursor(Input *input);

/**
 * @brief Define o foco de um input como TRUE e o resto pra FALSE e remove o cursor do antigo input com foco se houver
 *
 * @param input input a ter foco
 * @return void
 */
void setFocusInput(Input *input);

/**
 * @brief Testa se um input foi clicado
 *
 * @param input input a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void handleInputClickEvent(Input *input, unsigned short mouseX, unsigned short mouseY);

/**
 * @brief função que deve realizar tratamento de entrada de dados nos campos de input seja deleção ou adição
 *
 * @param key o código da tecla apertada pelo usuário
 * @return void
 */
void handleInputText(unsigned short key);

/**
 * Retorna o input com aquele value
*/
Input findInputByValue(char *value);

/**
 * @brief Reseta o array de inputs para receber os inputs de uma outra tela.
 *
 * @return void
 */
void freeScreenInputs();

#endif