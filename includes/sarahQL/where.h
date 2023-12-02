#ifndef WHERE_H
#define WHERE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "sarahQL/contentDescriptor.h"

typedef struct {
    void **matches;
    size_t matchCount;
} SearchResult;

/**
 * @brief Realiza uma busca em um array de estruturas, procurando elementos que correspondam a um valor específico em um campo especificado.
 *
 * @param array Ponteiro para o array de estruturas onde a busca será realizada.
 * @param numElements Número de elementos no array.
 * @param elementSize Tamanho de cada elemento no array (tamanho da estrutura).
 * @param desc Descritor da estrutura, detalhando os campos e seus tipos.
 * @param fieldName Nome do campo dentro da estrutura no qual a busca será realizada.
 * @param value Ponteiro para o valor que será comparado com o campo especificado.
 *
 * @return Ponteiro para o primeiro elemento encontrado que corresponde ao critério de busca. Retorna NULL se nenhum elemento correspondente for encontrado ou em caso de erro.
 */
void **findMatches(void *array, size_t numElements, size_t elementSize, 
           ContentDescriptor desc, const char *fieldName, void *value, size_t *matchedCount);


/**
 * @brief Lê dados de um arquivo e busca por elementos que correspondam a um valor específico em um campo especificado, utilizando uma estrutura definida.
 *
 * @param fileName Nome do arquivo do qual os dados serão lidos. O arquivo deve conter uma sequência de estruturas conforme definido por `elementSize`.
 * @param elementSize Tamanho de cada elemento no arquivo (tamanho da estrutura).
 * @param desc Descritor da estrutura, detalhando os campos e seus tipos. Usado para interpretar os dados lidos do arquivo.
 * @param fieldName Nome do campo dentro da estrutura no qual a busca será realizada. Este campo é usado para comparar com o `value`.
 * @param value Ponteiro para o valor que será comparado com o campo especificado. O tipo do valor deve corresponder ao tipo do campo.
 *
 * @return Ponteiro para um array de ponteiros para os elementos correspondentes encontrados. Retorna NULL se nenhum elemento correspondente for encontrado ou em caso de erro. O array retornado deve ser liberado pelo chamador.
 *
 * @note Esta função assume que o conteúdo do arquivo corresponde exatamente à sequência de estruturas descritas por `elementSize` e `desc`. 
 *       O chamador é responsável por garantir a compatibilidade dos dados do arquivo com a estrutura definida.
 */
SearchResult *where(const char *fileName, size_t elementSize, 
            ContentDescriptor desc, const char *fieldName, void *value);

#endif