#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <string.h>
#include "lib.h"

/// @brief @section GLOBAL VARIABLES
bool open = TRUE;
/// @endparblock

/**
 * @brief checa se a window ta aberta
 *
 * @return bool true se estiver rodando false senão
 */
bool isOpen()
{ return open; }

/**
 * @brief define o estado da window
 *
 * @param state o novo estado da window
 * @return void
 */
void setIsOpen(bool state)
{ open = state; }

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
 * @brief Calcula o tamanho da janela em termos da quantidade máxima de caracteres visíveis.
 *
 * @return int O tamanho da janela do programa, representado como a quantidade de caracteres visíveis.
 */
unsigned short *getWindowSize()
{
    unsigned short *windowSize = (unsigned short *)malloc(2 * sizeof(unsigned short));

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    windowSize[0] = csbi.dwSize.X;
    windowSize[1] = csbi.dwSize.Y;

#elif defined(__linux__)
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    windowSize[0] = w.ws_col;
    windowSize[1] = w.ws_row;

#endif

    return windowSize;
}

/**
 * @brief configura o console para poder receber eventos de clique e eventos de input serem não bloqueantes
 *
 * @return void
 */
void configureConsole()
{
    open = TRUE;
#ifdef _WIN32
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hInput, fdwMode);

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
#elif defined(__linux__)
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    timeout(0);
#endif
}

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
 * @brief Renderiza texto na tela do usuário na coordenada passada
 *
 * @param posX coordenada no eixo X
 * @param posY coordenada no eixo Y
 * @param text texto a ser renderizado
 *
 * @return void
 */
void renderText(unsigned short posX, unsigned short posY, const char *text)
{
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {posX, posY};
    SetConsoleCursorPosition(console, position);
    printf("%s", text);
#elif __linux__
    printf("\033[%d;%dH%s", posY, posX, text);
#endif
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
unsigned short *getCenterPos(Box *boxRelative, unsigned short textLength, bool horizontal, bool vertical)
{
    unsigned short *positions = (unsigned short *)malloc(sizeof(unsigned short) * 2);

    positions[0] = horizontal ? (boxRelative->startPointX + (boxRelative->width - textLength) / 2) : 0;
    positions[1] = vertical ? (boxRelative->startPointY + (boxRelative->height - 1) / 2) : 0;

    return positions;
}
#endif