#include "sarahQL/createTable.h"
#include <stdio.h>
#include <stdlib.h>

char * baseDbPath = "";

void setBaseDbPath(char *dbPath)
{
    baseDbPath = dbPath;
}


void createTable(const char *filename) {
    char fullPath[256];

    snprintf(fullPath, sizeof(fullPath), "%s/%s.bin", baseDbPath, filename);

    FILE *file = fopen(fullPath, "wb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fclose(file);
}
