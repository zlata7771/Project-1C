#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Создание нового файла
int create_file(const char* filename);

// Удаление файла
int delete_file(const char* filename);

// Запись данных в файл
int write_to_file(const char* filename, const char* data);

// Чтение данных из файла
char* read_from_file(const char* filename);

// Проверка существования файла
int file_exists(const char* filename);

#endif // FILESYSTEM_H
