#include "sarahQL/where.h"
#include "sarahQL/contentDescriptor.h"
#include "sarahQL/createTable.h"

void **findMatches(void *array, size_t numElements, size_t elementSize, 
             ContentDescriptor desc, const char *fieldName, void *value, size_t *matchedCount) 
{
    if (!array || !desc.fields || !fieldName || !value) {
        *matchedCount = 0;
        return NULL;
    }

    void **matchedElements = malloc(numElements * sizeof(void *));
    size_t count = 0;

    for (size_t i = 0; i < numElements; i++) {
        char *element = (char *)array + (i * elementSize);

        for (size_t j = 0; j < desc.numFields; j++) {
            if (strcmp(desc.fields[j].name, fieldName) == 0) {
                char *fieldPtr = element + desc.fields[j].offset;

                if ((desc.fields[j].type == INT && *(int *)fieldPtr == *(int *)value) ||
                    (desc.fields[j].type == DOUBLE && *(double *)fieldPtr == *(double *)value) ||
                    (desc.fields[j].type == STRING && strcmp(fieldPtr, (char *)value) == 0)) {
                    matchedElements[count++] = (void *)element;
                    break;
                }
            }
        }
    }

    *matchedCount = count;
    return matchedElements;
}

SearchResult *where(const char *fileName, size_t elementSize, 
                    ContentDescriptor desc, const char *fieldName, void *value) 
{
    char filePath[1024]; // Assuming the file path won't exceed this length.
    snprintf(filePath, sizeof(filePath), "%s%s.bin", baseDbPath, fileName);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    size_t numElements = fileSize / elementSize;

    void *array = malloc(fileSize);
    if (!array) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    if (fread(array, elementSize, numElements, file) != numElements) {
        perror("Error reading file");
        free(array);
        fclose(file);
        return NULL;
    }
    fclose(file);

    size_t matchedCount;
    void **matches = findMatches(array, numElements, elementSize, desc, fieldName, value, &matchedCount);

    SearchResult *result = malloc(sizeof(SearchResult));
    if (!result) {
        perror("Memory allocation failed");
        free(matches);
        free(array);
        return NULL;
    }

    result->matches = matches;
    result->matchCount = matchedCount;

    free(array);
    return result;
}