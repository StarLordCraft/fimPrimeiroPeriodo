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
    unsigned short cursor;

    char *text;
    unsigned short textSize;
    const char *label;
    const char *value;
    const char *type;

    bool focused;
} Input;

/// @section Global Variables
Button *screenButtons = NULL;
unsigned short numScreenButtons = 0;

Input *screenInputs = NULL;
unsigned short numScreenInputs = 0;
Input *inputFocused = NULL;

bool cursorVisible = TRUE;
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
            button->onClick();
}

/**
 * @brief Reseta o array de botões para receber os botões de uma outra tela.
 *
 * @return void
 */
void freeScreenButtons()
{
    free(screenButtons);
    screenButtons = NULL;
    numScreenButtons = 0;
}

/**
 * @brief Adiciona um input ao array de inputs para processar eventos de clique.
 *
 * @param input O input a ser adicionado ao array.
 * @return void
 */
void addInputToScreen(Input *input)
{
    ++numScreenInputs;
    screenInputs = (Input *)realloc(screenInputs, numScreenInputs * sizeof(Input));

    if (screenInputs == NULL)
        error("Falha na alocação de memória.\n");

    screenInputs[numScreenInputs - 1] = *input;
}

/**
 * @brief Renderiza um input na tela e o torna clicável, adicionando-o a um array de inputs.
 *
 * @param input O input a ser renderizado na tela.
 * @return void
 */
void renderInput(Input *input)
{
    renderText(input->startPointX, input->startPointY - 1, input->label);

    Box *box = createBox(input->width, input->height, input->startPointX, input->startPointY);
    createBorder(box, 1, "-");

    if (input->text)
    {
        renderText(input->startPointX + 1, getCenterPos(box, 0, FALSE, TRUE)[1], input->text);
        if (input->focused)
        {
            if (cursorVisible)
                input->text[input->cursor] = '|';
            else
                input->text[input->cursor] = ' ';

            cursorVisible = !cursorVisible;
        }
    }

    free(box);
}

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
                   const char *label, const char *value, const char *type)
{
    if (screenInputs)
        for (int i = 0; i < numScreenInputs; ++i)
            if (screenInputs[i].startPointX == startPointX && screenInputs[i].startPointY == startPointY)
            {
                renderInput(&screenInputs[i]);
                return &screenInputs[i];
            }

    Input *newInput = (Input *)malloc(sizeof(Input));

    newInput->width = width;
    newInput->height = 3;
    newInput->startPointX = startPointX;
    newInput->startPointY = startPointY;
    newInput->label = label;
    newInput->text = NULL;
    newInput->focused = FALSE;
    newInput->textSize = 0;
    newInput->value = value;

    if (strcmp(type, "password") == 0 || strcmp(type, "email") == 0 || strcmp(type, "text") == 0 || strcmp(type, "number") == 0)
        newInput->type = type;
    else
    {
        char errorMessage[40] = "Tipo de input";
        strcat(errorMessage, type);
        strcat(errorMessage, "indefinido");
        error("Tipo de input indefinido");
    }

    renderInput(newInput);
    addInputToScreen(newInput);

    return newInput;
}

/**
 * @brief move o cursor para uma determinada posição no text
 *
 * @param to pra onde o cursor vai
 * @return void
 */
void moveCursor(Input *input, unsigned short to)
{
    if (to >= 0 && to <= input->textSize)
    {
        input->text[input->cursor] = input->text[to];
        input->cursor = to;
    }
}

/**
 * @brief preserva o texto e remove o cursor dele.
 *
 * @return void
 */
void removeCursor(Input *input)
{
    if (input != NULL && input->text != NULL && input->cursor >= 0)
    {
        if (input->textSize > 0 && input->textSize > input->cursor)
        {
            while(input->cursor != input->textSize)
                moveCursor(input, input->cursor + 1);

            renderText((input->startPointX + input->textSize + 1), (input->startPointY + 1), " ");
        }

        input->text[input->cursor] = '\0';
    }
}

/**
 * @brief Define o foco de um input como TRUE e o resto pra FALSE e remove o cursor do antigo input com foco se houver
 *
 * @param input input a ter foco
 * @return void
 */
void setFocusInput(Input *input)
{
    for (int i = 0; i < numScreenInputs; ++i)
        screenInputs[i].focused = FALSE;


    input->focused = TRUE;
    inputFocused = input;
    cursorVisible = TRUE;

    input->cursor = input->textSize;
}

/**
 * @brief Testa se um input foi clicado
 *
 * @param input input a ser testado
 * @param mouseX posição X do mouse
 * @param mouseY posição Y do mouse
 * @return void
 */
void handleInputClickEvent(Input *input, unsigned short mouseX, unsigned short mouseY)
{
    removeCursor(input);
    if (mouseX >= input->startPointX && mouseX < (input->startPointX + input->width) &&
        mouseY >= input->startPointY && mouseY < (input->startPointY + input->height))
        setFocusInput(input);
    else
        input->focused = FALSE;
}

/**
 * @brief função que deve realizar tratamento de entrada de dados nos campos de input seja deleção ou adição
 *
 * @param key o código da tecla apertada pelo usuário
 * @return void
 */
void handleInputText(unsigned short key)
{
    if (key == KEY_BACKSPACE && inputFocused->textSize > 0 && inputFocused->cursor > 0)
    {
        --inputFocused->textSize;
        char *newText = (char *)realloc(inputFocused->text, (inputFocused->textSize + 2) * sizeof(char));
        if (newText != NULL)
        {
            inputFocused->text = newText;

            renderText((inputFocused->textSize + inputFocused->startPointX + 2), (inputFocused->startPointY + 1), " ");

            moveCursor(inputFocused, inputFocused->cursor - 1);
            for (int i = inputFocused->cursor + 1; i < inputFocused->textSize + 1; ++i)
                inputFocused->text[i] = inputFocused->text[i + 1];

            inputFocused->text[inputFocused->textSize + 1] = '\0';
        }
        else
            error("Falha ao realocar memoria no input");
    }

    else if (key >= 32 && key <= 126 && (inputFocused->textSize + 1) < (inputFocused->width - 1))
    {
        ++inputFocused->textSize;
        char *newText = (char *)realloc(inputFocused->text, (inputFocused->textSize + 2) * sizeof(char));
        if (newText)
        {
            inputFocused->text = newText;

            moveCursor(inputFocused, inputFocused->cursor + 1);
            for (int i = inputFocused->textSize; i > inputFocused->cursor; --i)
                inputFocused->text[i] = inputFocused->text[i - 1];

            inputFocused->text[inputFocused->cursor - 1] = key;
            inputFocused->text[inputFocused->textSize + 1] = '\0';
        }
        else
            error("Falha ao realocar memoria no input");
    }
    else if (key == KEY_LEFT)
    {
        if ((inputFocused->cursor - 1) >= 0)
            moveCursor(inputFocused, inputFocused->cursor - 1);
    }
    else if (key == KEY_RIGHT)
    {
        if ((inputFocused->cursor + 1) <= inputFocused->textSize + 1)
            moveCursor(inputFocused, inputFocused->cursor + 1);
    }
}

/**
 * @brief Reseta o array de inputs para receber os inputs de uma outra tela.
 *
 * @return void
 */
void freeScreenInputs()
{
    free(screenInputs);
    free(inputFocused);
    screenInputs = NULL;
    numScreenInputs = 0;
}

/**
 * @brief recebe eventos e computa eles seja clique input de teclado...
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

                inputFocused = FALSE;

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
#endif