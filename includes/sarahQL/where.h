#ifndef WHERE_H
#define WHERE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "sarahQL/contentDescriptor.h"

typedef struct {
    void **matches;
    size_t matchCount;
} SearchResult;

/**
 * @brief Verifica se um determinado elemento corresponde a um valor específico em um campo especificado.
 *
 * Esta função é utilizada para determinar se um único elemento em um array de estruturas atende a um critério específico.
 * Ela examina um campo especificado dentro da estrutura e o compara a um valor fornecido. A função suporta múltiplos 
 * tipos de dados para os campos, conforme definido no ContentDescriptor. É comumente usada em operações de busca onde 
 * os elementos são avaliados individualmente.
 *
 * @param element Ponteiro para o elemento que será verificado para a correspondência. Este deve ser um ponteiro para uma estrutura.
 * @param desc Descritor da estrutura, detalhando os campos e seus tipos. Isso é usado para entender o layout 
 *             e os tipos de dados dos campos dentro da estrutura.
 * @param fieldName Nome do campo dentro da estrutura que será comparado com o valor fornecido. A função 
 *                  verificará apenas este campo específico dentro da estrutura.
 * @param value Ponteiro para o valor que será comparado com o campo especificado no elemento. O tipo deste 
 *              valor deve corresponder ao tipo do campo, conforme descrito no ContentDescriptor.
 *
 * @return Verdadeiro se o campo especificado no elemento corresponder ao valor fornecido, Falso caso contrário. Também retorna Falso em 
 *         caso de erro ou se o campo não for encontrado no descritor.
 */
bool isMatch(void *element, ContentDescriptor desc, const char *fieldName, void *value);


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