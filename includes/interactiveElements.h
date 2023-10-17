#ifndef INTERACTIVE_ELEMENTS_H
#define INTERACTIVE_ELEMENTS_H

#include "elements.h"

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

typedef struct
{
    unsigned short width;
    unsigned short height;
    unsigned short startPointX;
    unsigned short startPointY;
    char *text;
    const char *label;
    boolean focused;
} Input;

/// @section Global Variables
Button *screenButtons = NULL;
unsigned short numScreenButtons = 0;

Input *screenInputs = NULL;
unsigned short numScreenInputs = 0;
Input *inputFocused = NULL;
/// @endparblock end Global Variables

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
 * @brief Renderiza um botão na tela e o torna clicável, adicionando-o a um array de botões.
 *
 * @param button O botão a ser renderizado na tela.
 * @return void
 */
void renderButton(Button *button)
{
    createBorder(createBox(button->width, button->height, button->startPointX, button->startPointY), 1);
    unsigned short *centerPos = getCenterPos(createBox(button->width, button->height, button->startPointX, button->startPointY), strlen(button->text), TRUE, TRUE);
    renderText(centerPos[0], centerPos[1], button->text);

    addButtonToScreen(button);

    free(centerPos);
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
    Button *newButton = (Button *)malloc(sizeof(Button));

    newButton->width = width;
    newButton->height = height;
    newButton->startPointX = startPointX;
    newButton->startPointY = startPointY;
    newButton->text = label;
    newButton->onClick = callBack;

    renderButton(newButton);

    return newButton;
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
        if (button->onClick != NULL)
            button->onClick();
}

/**
 * @brief Reseta o array de botões para receber os botões de uma outra tela.
 *
 * @return void
 */
void freeScreenButtons()
{
    for(int i = 0; i < numScreenButtons; ++i)
        free(&screenButtons[i]);
    free(screenButtons);
    numScreenButtons = 0;
}

/**
 * @brief Cria um Input
 *
 * @param width largura do Input
 * @param height altura do Input
 * @param startPointX Posicionamento no eixo X do Input
 * @param startPointY Posicionamento no eixo Y do Input
 * @param label Texto de call to action do Input
 * @param callBack o que acontece quando esse botão é clicado
 * @return Button retorna um elemento de interação renderizável na tela
 */
Input *createInput(unsigned short width, unsigned short height, unsigned short startPointX, unsigned short startPointY,
                        const char *label)
{
    Input *newInput = (Input *)malloc(sizeof(Input));
    newInput->width = width;
    newInput->height = height;
    newInput->startPointX = startPointX;
    newInput->startPointY = startPointY;
    newInput->label = label;
    newInput->focused = FALSE;
    return newInput;
}

/**
 * @brief Testa se um input foi clicado e define todos os outros como não clicados
 *
 * @param input input a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void setFocusInput(Input *input, unsigned short mouseX, unsigned short mouseY)
{
    unsigned short noFocusedInputs = 0;
    if (mouseX >= input->startPointX && mouseX < (input->startPointX + input->width) &&
        mouseY >= input->startPointY && mouseY < (input->startPointY + input->height)){
            input->focused = TRUE;
            inputFocused = input;
        }

    else {
        ++noFocusedInputs;
        input->focused = FALSE;
    }

    if(noFocusedInputs >= numScreenInputs) inputFocused = NULL;
}

/**
 * @brief Desaloca memória de um input.
 *
 * @return void
 */
void freeInput(Input *input)
{ free(input->text); free(input); }

/**
 * @brief Reseta o array de inputs para receber os inputs de uma outra tela.
 *
 * @return void
 */
void freeScreenInputs()
{
    for(int i = 0; i < numScreenInputs; ++i)
        freeInput(&screenInputs[i]);
    free(screenInputs); free(inputFocused);
    numScreenInputs = 0;
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

                inputFocused = FALSE;

                for(int i = 0; i < numScreenInputs; ++i)
                    setFocusInput(&screenInputs[i], pos.X, pos.Y);
            }
        }
    }

    if (kbhit() && getch() == 27 && !inputFocused)
        setIsOpen(FALSE);

#elif defined(__linux__)
    int ch = getch();
    if (ch == KEY_MOUSE)
    {
        MEVENT event;
        if (getmouse(&event) == OK)
            if (event.bstate & BUTTON1_PRESSED){
                for (int i = 0; i < numScreenButtons; ++i)
                    handleButtonEvent(&screenButtons[i], event.x, event.y);
                
                inputFocused = FALSE;
                
                for (int i = 0; i < numScreenInputs; ++i)
                    setFocusInput(&screenInputs[i], event.x, event.y);
            }
    }

    if (ch == 'q' && !inputFocused)
        setIsOpen(FALSE);

    refresh();
#endif
}
#endif