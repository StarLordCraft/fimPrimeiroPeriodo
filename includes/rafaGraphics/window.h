#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>
#include "../standart.h"
#include "./keys.h"

/// @brief @section GLOBAL VARIABLES
extern bool open;
/// @endparblock

/**
 * @brief checa se a window ta aberta
 *
 * @return bool true se estiver rodando false senão
 */
bool isOpen();

/**
 * @brief define o estado da window
 *
 * @param state o novo estado da window
 * @return void
 */
void setIsOpen(bool state);

/**
 * @brief Calcula o tamanho da janela em termos da quantidade máxima de caracteres visíveis.
 *
 * @return int O tamanho da janela do programa, representado como a quantidade de caracteres visíveis.
 */
unsigned short *getWindowSize();

/**
 * @brief configura o console para poder receber eventos de clique e eventos de input serem não bloqueantes
 *
 * @return void
 */
void configureConsole();

/**
 * @brief Renderiza texto na tela do usuário na coordenada passada
 *
 * @param posX coordenada no eixo X
 * @param posY coordenada no eixo Y
 * @param text texto a ser renderizado
 *
 * @return void
 */
void renderText(unsigned short posX, unsigned short posY, const char *text);

/**
 * @brief recebe eventos e computa eles seja clique input de teclado...
 *
 * @return bool - se deve ou não parar o programa
 */
void handleEvents();

#endif