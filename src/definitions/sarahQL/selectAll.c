#include "sarahQL/selectAll.h"

#include <stdio.h>
#include <stdlib.h>

SearchResult *selectAll(size_t objectSize, const char *filename) {
    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/%s.bin", baseDbPath, filename);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    size_t count = fileSize / objectSize;
    void **objectsArray = malloc(count * sizeof(void *));
    if (!objectsArray) {
        perror("Error allocating memory for objectsArray");
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        objectsArray[i] = malloc(objectSize);
        if (!objectsArray[i]) {
            perror("Error allocating memory for an object");
            // Libera a memória alocada até agora antes de retornar
            for (size_t j = 0; j < i; j++) {
                free(objectsArray[j]);
            }
            free(objectsArray);
            fclose(file);
            return NULL;
        }
        if (fread(objectsArray[i], objectSize, 1, file) != 1) {
            perror("Error reading from file");
            // Libera a memória alocada até agora antes de retornar
            for (size_t j = 0; j <= i; j++) {
                free(objectsArray[j]);
            }
            free(objectsArray);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    SearchResult *result = malloc(sizeof(SearchResult));
    if (!result) {
        perror("Memory allocation failed for SearchResult");
        for (size_t i = 0; i < count; i++) {
            free(objectsArray[i]);
        }
        free(objectsArray);
        return NULL;
    }

    result->matches = objectsArray;
    result->matchCount = count;

    return result;
}