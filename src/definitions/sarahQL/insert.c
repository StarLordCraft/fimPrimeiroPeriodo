#include "sarahQL/insert.h"
#include "sarahQL/createTable.h"

#include <stdio.h>
#include <stdlib.h>

void insert(void *obj, const char *tableName, size_t objSize) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s/%s.bin", baseDbPath, tableName);

    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    if (fwrite(obj, objSize, 1, file) != 1)
        perror("Error writing to file");

    fclose(file);
}