#include "sarahQL/where.h"
#include "sarahQL/contentDescriptor.h"
#include "sarahQL/createTable.h"

bool isMatch(void *element, ContentDescriptor desc, const char *fieldName, void *value) {
    if (!element || !desc.fields || !fieldName || !value) 
        return false;

    for (size_t j = 0; j < desc.numFields; j++) {
        if (strcmp(desc.fields[j].name, fieldName) == 0) {
            char *fieldPtr = (char *)element + desc.fields[j].offset;

            switch (desc.fields[j].type) {
                case INT:
                    return *(int *)fieldPtr == *(int *)value;
                case DOUBLE:
                    return *(double *)fieldPtr == *(double *)value;
                case STRING:
                    return strcmp(fieldPtr, (char *)value) == 0;
                default:
                    return false;
            }
        }
    }
    return false;
}

SearchResult *where(const char *fileName, size_t elementSize, ContentDescriptor desc, const char *fieldName, void *value) {
    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/%s.bin", baseDbPath, fileName);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    void **matches = NULL;
    size_t matchCount = 0;
    size_t capacity = 0;

    void *element = malloc(elementSize);
    if (!element) {
        perror("Memory allocation failed for element");
        fclose(file);
        return NULL;
    }

    while (fread(element, elementSize, 1, file) == 1) {
        if (isMatch(element, desc, fieldName, value)) {
            if (matchCount == capacity) {
                size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
                void **newMatches = realloc(matches, newCapacity * sizeof(void *));
                if (!newMatches) {
                    perror("Memory allocation failed for matches");
                    free(element);
                    for (size_t i = 0; i < matchCount; ++i) {
                        free(matches[i]);
                    }
                    free(matches);
                    fclose(file);
                    return NULL;
                }
                matches = newMatches;
                capacity = newCapacity;
            }

            matches[matchCount] = malloc(elementSize);
            if (!matches[matchCount]) {
                perror("Memory allocation failed for match copy");
                free(element);
                for (size_t i = 0; i < matchCount; ++i) {
                    free(matches[i]);
                }
                free(matches);
                fclose(file);
                return NULL;
            }
            memcpy(matches[matchCount], element, elementSize);
            matchCount++;
        }
    }

    free(element);
    fclose(file);

    SearchResult *result = malloc(sizeof(SearchResult));
    if (!result) {
        perror("Memory allocation failed for SearchResult");
        for (size_t i = 0; i < matchCount; ++i) {
            free(matches[i]);
        }
        free(matches);
        return NULL;
    }

    result->matches = matches;
    result->matchCount = matchCount;

    return result;
}