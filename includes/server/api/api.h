#ifndef API_H
#define API_H
#include "sarahQL/createTable.h"
#include <stdlib.h>
#include <string.h>

// Definição do tipo de ponteiro para função Method
typedef void *(*Method)(void *);

// Estrutura representando um Controller
typedef struct {
    const char *route;   ///< Rota do Controller
    Method GET;          ///< Ponteiro para função do método GET
    Method POST;         ///< Ponteiro para função do método POST
    Method PUT;          ///< Ponteiro para função do método PUT
    Method DELETE;       ///< Ponteiro para função do método DELETE
} Controller;

// Estrutura representando uma API
typedef struct {
    Controller **controllers; ///< Array de Controllers
    unsigned short size; ///< Tamanho do array de Controllers
} Api;

Api *api;

/**
 * @brief Inicializa a estrutura da API.
 *
 * Aloca memória para a API e a estrutura de Controllers, definindo o tamanho inicial como 0.
 */
void initApi()
{
    api = (Api *) malloc(sizeof(Api));
    api->controllers = (Controller **) malloc(sizeof(Controller));
    api->size = 0;
}

/**
 * @brief Configura o caminho base do banco de dados do servidor.
 *
 * Usa a função setBaseDbPath de sarahQL/createTable.h para definir o caminho.
 */
void useServerDb()
{
    setBaseDbPath("../includes/server/database");
}

/**
 * @brief Adiciona um novo Controller à API.
 *
 * Realoca o array de Controllers da API para acomodar o novo Controller e incrementa o tamanho.
 * 
 * @param Controller O Controller a ser adicionado.
 */
void addController(Controller *controller)
{
    Controller **newControllers = realloc(api->controllers, sizeof(Controller *) * (api->size + 1));
    if (newControllers == NULL) {
        // Tratamento de erro para falha de realocação
        return;
    }
    api->controllers = newControllers;
    api->controllers[api->size] = controller;
    ++api->size;
}


/**
 * @brief Cria e inicializa um novo Controller com os métodos HTTP especificados.
 * 
 * Esta função aloca memória para um novo Controller, configura a rota e associa 
 * os métodos HTTP fornecidos (GET, POST, PUT, DELETE) ao Controller. A rota é duplicada
 * para evitar problemas de ponteiros. Esta função não adiciona o Controller a qualquer
 * estrutura de gerenciamento de Controllers, isso deve ser feito separadamente.
 *
 * @param route Ponteiro para a string que representa a rota do Controller.
 * @param GET Função que representa o método GET para este Controller.
 * @param POST Função que representa o método POST para este Controller.
 * @param PUT Função que representa o método PUT para este Controller.
 * @param DELETE Função que representa o método DELETE para este Controller.
 * @return void
 */
void createController(const char *route, Method GET, Method POST, Method PUT, Method DELETE)
{
    Controller *newController = (Controller *) malloc(sizeof(Controller));
    newController->route = route;

    newController->GET = GET;
    newController->POST = POST;
    newController->PUT = PUT;
    newController->DELETE = DELETE;
}

/**
 * @brief Encontra um Controller pelo caminho da rota.
 *
 * Percorre o array de Controllers procurando por uma rota correspondente.
 * 
 * @param route O caminho da rota a ser procurada.
 * @return Ponteiro para o Controller encontrado ou NULL se não encontrado.
 */
Controller *findControllerByRoute(const char *route) {
    for (int i = 0; i < api->size; i++) {
        if (strcmp(api->controllers[i]->route, route) == 0) {
            return api->controllers[i];
        }
    }
    return NULL;
}

/**
 * @brief Libera a memória alocada para a API.
 *
 * Desaloca cada Controller alocado dinamicamente, o array de Controllers e a estrutura Api.
 */
void freeApi() {
    if (api != NULL) {
        for (int i = 0; i < api->size; i++) {
            free(api->controllers[i]);
        }

        free(api->controllers);

        free(api);
        api = NULL;
    }
}

#endif
