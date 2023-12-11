#ifndef BOX_H
#define BOX_H

#include "window.h"

/// @brief
/*
 * Essa struct serve pra criar armazenar e manipular estruturas analogas a div no html
 */
typedef struct
{
    unsigned short width;
    unsigned short height;

    unsigned short startPointX;
    unsigned short startPointY;
} Box;

/**
 * @brief Cria uma Box
 *
 * @param width largura da Box
 * @param height altura da Box
 * @param startPointX Posicionamento no eixo X da box
 * @param startPointY Posicionamento no eixo Y da Box
 * @return Box retorna um elemento renderizável na tela
 */
Box *createBox(unsigned short width, unsigned short height, unsigned short startPointX, unsigned short startPointY);

/**
 * @brief Cria uma borda num determinado elemento
 *
 * @param box que receberá borda
 * @param borderSize tamanho da borda
 * @param border desenho da borda
 * @return void
 */
void createBorder(Box *box, unsigned short borderSize, const char *border);

/**
 * @brief Centraliza um elemento em relação a um contêiner pai, levando em consideração as coordenadas
 * horizontal e vertical.
 *
 * @param boxRelative O contêiner pai.
 * @param childrenLenght O tamanho do elemento filho a ser centralizado.
 * @param horizontal Define se o elemento deve ser centralizado horizontalmente.
 * @param vertical Define se o elemento deve ser centralizado verticalmente.
 *
 * @return int* Um array contendo as coordenadas x e y que centralizam o elemento.
 */
unsigned short *getCenterPos(Box *boxRelative, unsigned short childrenLenght, bool horizontal, bool vertical);

#endif