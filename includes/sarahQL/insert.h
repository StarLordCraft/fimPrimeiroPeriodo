#ifndef INSERT_H
#define INSERT_H
#include <stddef.h>

/**
 * @brief função pra inserir objetos em um dado arquivo
 * @param obj objeto a ser inserido
 * @param tableName em que tabela guardar o objeto
 * @param objSize como é um void * preciso saber o tamanho do objeto
*/
void insert(void *obj, const char *tableName, size_t objSize);
#endif