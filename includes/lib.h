#include <stdio.h>
#include <stdlib.h>

void error(char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

typedef enum {
    FALSE,
    TRUE,
} boolean;

typedef struct{
    void* first;
    void* second;
} Pair;

Pair* createPair(void* first, void* second) {
    Pair* newPair = (Pair*) malloc(sizeof(Pair));
    newPair->first = first;
    newPair->second = second;
    return newPair;
}

void freePair(Pair* pair) {
    free(pair->first);
    free(pair->second);
    free(pair);
}