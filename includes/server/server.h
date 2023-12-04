#ifndef SERVER_H
#define SERVER_H

// Definição do tipo de ponteiro para função Method
typedef void *(*Method)(void *request);

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

extern Api *api;

/**
 * @brief função pra carregar os controllers
*/
void loadControllers();

/**
 * @brief Inicializa a estrutura da API.
 *
 * Aloca memória para a API e a estrutura de Controllers, definindo o tamanho inicial como 0.
 */
void initApi();

/**
 * @brief Configura o caminho base do banco de dados do servidor.
 *
 * Usa a função setBaseDbPath de sarahQL/createTable.h para definir o caminho.
 */
void useServerDb();

/**
 * @brief Adiciona um novo Controller à API.
 *
 * Realoca o array de Controllers da API para acomodar o novo Controller e incrementa o tamanho.
 * 
 * @param Controller O Controller a ser adicionado.
 */
void addController(Controller *controller);

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
void createController(const char *route, Method GET, Method POST, Method PUT, Method DELETE);

/**
 * @brief Encontra um Controller pelo caminho da rota.
 *
 * Percorre o array de Controllers procurando por uma rota correspondente.
 * 
 * @param route O caminho da rota a ser procurada.
 * @return Ponteiro para o Controller encontrado ou NULL se não encontrado.
 */
Controller *findControllerByRoute(const char *route);

/**
 * @brief Libera a memória alocada para a API.
 *
 * Desaloca cada Controller alocado dinamicamente, o array de Controllers e a estrutura Api.
 */
void freeApi();

#endif