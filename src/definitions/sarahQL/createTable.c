#include "sarahQL/createTable.h"
#include <stdio.h>
#include <stdlib.h>

void createBinaryFile(const char *filename) {
    const char *relativePath = "/mnt/HD1/Projetos/cpp/begginer/courseWork/includes/server/database";
    char fullPath[256];

    snprintf(fullPath, sizeof(fullPath), "%s/%s.db", relativePath, filename);

    FILE *file = fopen(fullPath, "wb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fclose(file);
}