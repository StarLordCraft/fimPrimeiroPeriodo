#include "standart.h"

#include "rafaGraphics/window.h"
#include "rafaGraphics/button.h"
#include "rafaGraphics/input.h"

/// @brief @section GLOBAL VARIABLES
bool open = TRUE;
/// @endparblock

/**
 * @brief checa se a window ta aberta
 *
 * @return bool true se estiver rodando false senão
 */
bool isOpen()
{
    return open;
}

/**
 * @brief define o estado da window
 *
 * @param state o novo estado da window
 * @return void
 */
void setIsOpen(bool state)
{
    open = state;
}

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
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    timeout(0);
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
 * @brief recebe eventos e computa eles seja clique input de tecladorafaGraphics.
 *
 * @return bool - se deve ou não parar o programa
 */
void handleEvents()
{
#ifdef _WIN32
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hInput, fdwMode);

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
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

                inputFocused = NULL;
                for (int i = 0; i < numScreenInputs; ++i)
                    handleInputClickEvent(&screenInputs[i], pos.X, pos.Y);
            }
        }
    }
    unsigned short key = getch();

    if (kbhit() && key == 27 && !inputFocused)
        setIsOpen(FALSE);
    else if (inputFocused)
        handleInputText(key);

#elif defined(__linux__)
    int ch = getch();
    if (ch == KEY_MOUSE)
    {
        MEVENT event;
        if (getmouse(&event) == OK)
            if (event.bstate & BUTTON1_PRESSED)
            {

                for (int i = 0; i < numScreenButtons; ++i)
                    handleButtonEvent(&screenButtons[i], event.x, event.y);

                inputFocused = NULL;

                for (int i = 0; i < numScreenInputs; ++i)
                    handleInputClickEvent(&screenInputs[i], event.x, event.y);
            }
    }

    if (ch == 'q' && !inputFocused)
        setIsOpen(FALSE);
    else if (inputFocused)
        handleInputText(ch);

    refresh();
#endif
}