#ifndef CREATE_TABLE_H
#define CREATE_TABLE_H

extern char *baseDbPath;

void setBaseDbPath(char *dbPath);

/**
 * @brief função responsável por criar um arquivo de database na pasta /server/database
 * @param filename -> nome do arquivo
*/
void createBinaryFile(const char *filename);
#endif