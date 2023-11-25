#include "standart.h"

#include "rafaGraphics/input.h"


///@section GLOBAL VARIABLES
Input *screenInputs = NULL;
unsigned short numScreenInputs = 0;
Input *inputFocused = NULL;

bool cursorVisible = TRUE;
///@endparblock

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
    newInput->text = (char *)malloc(sizeof(char) * 2);
    newInput->text[0] = ' ';
    newInput->text[1] = '\0';
    newInput->textSize = 0;
    newInput->focused = FALSE;
    newInput->value = value;

    if (strcmp(type, "password") == 0 || strcmp(type, "email") == 0 || strcmp(type, "text") == 0 || strcmp(type, "number") == 0)
        newInput->type = type;
    else
    {
        char *errorMessage = (char *)malloc(sizeof(char) * 40);

        errorMessage = strcat(errorMessage, "Tipo de input: ");
        errorMessage = strcat(errorMessage, type);
        errorMessage = strcat(errorMessage, "indefinido");

        error(errorMessage);
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
            while (input->cursor != input->textSize)
                moveCursor(input, input->cursor + 1);
        }
        input->text[input->cursor] = '\0';
        renderText((input->startPointX + input->textSize + 1), (input->startPointY + 1), " ");
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
    if (KEY_ENTER == key || '\n' == key)
    {
        for (unsigned short i = 0; i < numScreenInputs; ++i)
            if (&screenInputs[i] == inputFocused)
            {
                if (i < numScreenInputs - 1)
                {
                    removeCursor(inputFocused);
                    handleInputClickEvent(&screenInputs[1 + i], screenInputs[1 + i].startPointX + 1, screenInputs[1 + i].startPointY + 1);
                }
                else
                {
                    if ((numScreenButtons > 0))
                        screenButtons[numScreenButtons - 1].onClick();
                }
                break;
            }
    }
    else if (KEY_BACKSPACE == key && inputFocused->textSize > 0 && inputFocused->cursor > 0)
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
    else if (KEY_LEFT == key)
    {
        if ((inputFocused->cursor - 1) >= 0)
            moveCursor(inputFocused, inputFocused->cursor - 1);
    }
    else if (KEY_RIGHT == key)
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