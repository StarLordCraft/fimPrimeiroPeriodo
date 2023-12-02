#ifndef API_H
#define API_H
#include "sarahQL/createTable.h"
#include <stdlib.h>
#include <string.h>

// Definição do tipo de ponteiro para função Method
typedef void *(*Method)(void *);

// Estrutura representando um Endpoint
typedef struct {
    const char *route;   ///< Rota do endpoint
    Method GET;          ///< Ponteiro para função do método GET
    Method POST;         ///< Ponteiro para função do método POST
    Method PUT;          ///< Ponteiro para função do método PUT
    Method DELETE;       ///< Ponteiro para função do método DELETE
} Endpoint;

// Estrutura representando uma API
typedef struct {
    Endpoint **endpoints; ///< Array de Endpoints
    unsigned short size; ///< Tamanho do array de Endpoints
} Api;

Api *api;

/**
 * @brief Inicializa a estrutura da API.
 *
 * Aloca memória para a API e a estrutura de endpoints, definindo o tamanho inicial como 0.
 */
void initApi()
{
    api = (Api *) malloc(sizeof(Api));
    api->endpoints = (Endpoint **) malloc(sizeof(Endpoint));
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
 * @brief Adiciona um novo endpoint à API.
 *
 * Realoca o array de endpoints da API para acomodar o novo endpoint e incrementa o tamanho.
 * 
 * @param endpoint O endpoint a ser adicionado.
 */
void addEndpoint(Endpoint *endpoint)
{
    Endpoint **newEndpoints = realloc(api->endpoints, sizeof(Endpoint *) * (api->size + 1));
    if (newEndpoints == NULL) {
        // Tratamento de erro para falha de realocação
        return;
    }
    api->endpoints = newEndpoints;
    api->endpoints[api->size] = endpoint;
    ++api->size;
}


/**
 * @brief Cria e inicializa um novo endpoint com os métodos HTTP especificados.
 * 
 * Esta função aloca memória para um novo endpoint, configura a rota e associa 
 * os métodos HTTP fornecidos (GET, POST, PUT, DELETE) ao endpoint. A rota é duplicada
 * para evitar problemas de ponteiros. Esta função não adiciona o endpoint a qualquer
 * estrutura de gerenciamento de endpoints, isso deve ser feito separadamente.
 *
 * @param route Ponteiro para a string que representa a rota do endpoint.
 * @param GET Função que representa o método GET para este endpoint.
 * @param POST Função que representa o método POST para este endpoint.
 * @param PUT Função que representa o método PUT para este endpoint.
 * @param DELETE Função que representa o método DELETE para este endpoint.
 * @return void
 */
void createEndPoint(const char *route, Method GET, Method POST, Method PUT, Method DELETE)
{
    Endpoint * newEndpoint = (Endpoint *) malloc(sizeof(Endpoint));
    newEndpoint->route = route;

    newEndpoint->GET = GET;
    newEndpoint->POST = POST;
    newEndpoint->PUT = PUT;
    newEndpoint->DELETE = DELETE;
}

/**
 * @brief Encontra um endpoint pelo caminho da rota.
 *
 * Percorre o array de endpoints procurando por uma rota correspondente.
 * 
 * @param route O caminho da rota a ser procurada.
 * @return Ponteiro para o Endpoint encontrado ou NULL se não encontrado.
 */
Endpoint *findEndpointByRoute(const char *route) {
    for (int i = 0; i < api->size; i++) {
        if (strcmp(api->endpoints[i]->route, route) == 0) {
            return api->endpoints[i];
        }
    }
    return NULL;
}

/**
 * @brief Libera a memória alocada para a API.
 *
 * Desaloca cada Endpoint alocado dinamicamente, o array de Endpoints e a estrutura Api.
 */
void freeApi() {
    if (api != NULL) {
        for (int i = 0; i < api->size; i++) {
            free(api->endpoints[i]);
        }

        free(api->endpoints);

        free(api);
        api = NULL;
    }
}

#endif
