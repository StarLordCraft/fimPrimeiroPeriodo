#include "standart.h"

#include "rafaGraphics/box.h"

/**
 * @brief Cria uma Box
 *
 * @param width largura da Box
 * @param height altura da Box
 * @param startPointX Posicionamento no eixo X da box
 * @param startPointY Posicionamento no eixo Y da Box
 * @return Box retorna um elemento renderizável na tela
 */
Box *createBox(unsigned short width, unsigned short height, unsigned short startPointX, unsigned short startPointY)
{
    Box *box = (Box *)malloc(sizeof(Box));

    box->width = width;
    box->height = height;
    box->startPointX = startPointX;
    box->startPointY = startPointY;

    return box;
}

/**
 * @brief Cria uma borda num determinado elemento
 *
 * @param box que receberá borda
 * @param borderSize tamanho da borda
 * @param border desenho da borda
 * @return void
 */
void createBorder(Box *box, unsigned short borderSize, const char *border)
{
    if (box->width < 2 * borderSize || box->height < 2 * borderSize)
        error("Tamanho da borda muito grande para a caixa!\n");

    for (unsigned short y = 0; y < box->height; ++y)
        for (unsigned short x = 0; x < box->width; ++x)
            if (x < borderSize || x >= (box->width - borderSize) || y < borderSize || y >= (box->height - borderSize))
                renderText(x + box->startPointX, y + box->startPointY, border);
}

/**
 * @brief Centraliza um elemento em relação a um contêiner pai, levando em consideração as coordenadas
 * horizontal e vertical.
 *
 * @param boxRelative O contêiner pai.
 * @param textLength O tamanho do elemento filho a ser centralizado.
 * @param horizontal Define se o elemento deve ser centralizado horizontalmente.
 * @param vertical Define se o elemento deve ser centralizado verticalmente.
 *
 * @return int* Um array contendo as coordenadas x e y que centralizam o elemento.
 */
unsigned short *getCenterPos(Box *boxRelative, unsigned short childrenLenght, bool horizontal, bool vertical)
{
    unsigned short *positions = (unsigned short *)malloc(sizeof(unsigned short) * 2);

    positions[0] = horizontal ? (boxRelative->startPointX + (boxRelative->width - childrenLenght) / 2) : 0;
    positions[1] = vertical ? (boxRelative->startPointY + (boxRelative->height - 1) / 2) : 0;

    return positions;
}