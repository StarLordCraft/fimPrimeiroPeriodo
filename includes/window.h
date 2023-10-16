#include <string.h>
#include "lib.h"

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#endif

/// @brief
/*
 * Essa struct serve pra criar armazenar e manipular estruturas analogas a div no html
 */
typedef struct
{
    unsigned int width;
    unsigned int height;

    unsigned int startPointX;
    unsigned int startPointY;
} Box;

/**
 * @brief
 * Essa struct serve pra criar armazenar e manipular estruturas analogas a button no html
 */
typedef struct
{
    unsigned int width;
    unsigned int height;

    unsigned int startPointX;
    unsigned int startPointY;

    const char *text;
    void (*onClick)(void);
} Button;

/// @section Global Variables
boolean open = TRUE;
Button *screenButtons = NULL;
int numScreenButtons = 0;
/// @endparblock end Global Variables

/**
 * @brief checa se a window ta aberta
 * 
 * @return boolean true se estiver rodando false senão
*/
boolean isOpen()
{ return open; }

/**
 * @brief define o estado da window
 * 
 * @param state o novo estado da window
 * @return void
*/
void setIsOpen(boolean state)
{ open = state; }

/**
 * @brief Reseta o array de botões para receber os botões de uma outra tela.
 * 
 * @return void
*/
void freeScreenButtons()
{
    free(screenButtons);
    numScreenButtons = 0;
}

/**
 * @brief Calcula o tamanho da janela em termos da quantidade máxima de caracteres visíveis.
 *
 * @return int O tamanho da janela do programa, representado como a quantidade de caracteres visíveis.
 */
int *getWindowSize()
{
    int *windowSize = (int *)malloc(2 * sizeof(int));

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
 * @brief Testa se um botão foi clicado
 *
 * @param button botão a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void handleButtonEvent(Button *button, int mouseX, int mouseY)
{
    if (mouseX >= button->startPointX && mouseX < (button->startPointX + button->width) &&
        mouseY >= button->startPointY && mouseY < (button->startPointY + button->height))
        if (button->onClick != NULL)
            button->onClick();
}

/**
 * @brief recebe eventos e computa eles seja clique input de teclado...
 *
 * @return boolean - se deve ou não parar o programa
 */
void handleEvents()
{
#ifdef _WIN32
    ReadConsoleInput(hInput, irInBuf, 128, &cNumRead);
    for (DWORD i = 0; i < cNumRead; i++)
    {
        if (irInBuf[i].EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
            if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                COORD pos = mer.dwMousePosition;
                for (int i = 0; i < numScreenButtons; ++i)
                    handleButtonEvent(&screenButtons[i], pos.X, pos.Y);
            }
        }
    }

    if (kbhit() && getch() == 27)
        setIsOpen(FALSE);

#elif defined(__linux__)
    int ch = getch();
    if (ch == KEY_MOUSE)
    {
        MEVENT event;
        if (getmouse(&event) == OK)
            if (event.bstate & BUTTON1_PRESSED)
                for (int i = 0; i < numScreenButtons; ++i)
                    handleButtonEvent(&screenButtons[i], event.x, event.y);
    }

    if (ch == 'q')
        setIsOpen(FALSE);

    refresh();
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
Box *createBox(unsigned int width, unsigned int height, unsigned int startPointX, unsigned int startPointY)
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
void renderText(unsigned int posX, unsigned int posY, const char *text)
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
 * @return void
 */
void createBorder(Box *box, unsigned int borderSize)
{
    if (box->width < 2 * borderSize || box->height < 2 * borderSize)
        error("Tamanho da borda muito grande para a caixa!\n");

    for (unsigned int y = 0; y < box->height; ++y)
        for (unsigned int x = 0; x < box->width; ++x)
            if (x < borderSize || x >= (box->width - borderSize) || y < borderSize || y >= (box->height - borderSize))
                renderText(x + box->startPointX, y + box->startPointY, "#");
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
int *getCenterPos(Box *boxRelative, unsigned short textLength, boolean horizontal, boolean vertical)
{
    int *positions = (int *)malloc(sizeof(int) * 2);

    positions[0] = horizontal ? (boxRelative->startPointX + (boxRelative->width - textLength) / 2) : 0;
    positions[1] = vertical ? (boxRelative->startPointY + (boxRelative->height - 1) / 2) : 0;

    return positions;
}

/**
 * @brief Adiciona um botão ao array de botões para processar eventos de clique.
 *
 * @param button O botão a ser adicionado ao array.
 * @return void
 */
void addButtonToScreen(Button *button)
{
    screenButtons = (Button *)realloc(screenButtons, (numScreenButtons + 1) * sizeof(Button));

    if (screenButtons == NULL)
        error("Falha na alocação de memória.\n");

    screenButtons[numScreenButtons] = *button;
    numScreenButtons++;
}

/**
 * @brief Renderiza um botão na tela e o torna clicável, adicionando-o a um array de botões.
 *
 * @param button O botão a ser renderizado na tela.
 * @return void
 */
void renderButton(Button *button)
{
    createBorder(createBox(button->width, button->height, button->startPointX, button->startPointY), 1);
    int *centerPos = getCenterPos(createBox(button->width, button->height, button->startPointX, button->startPointY), strlen(button->text), 1, 1);
    renderText(centerPos[0], centerPos[1], button->text);

    addButtonToScreen(button);

    free(centerPos);
}