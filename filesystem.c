#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem.h"

//Открыть (или создать и открыть) файл файловой системы
FILE* open_or_create_file(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        file = fopen(filename, "w+");
    }
    return file;
}

//Просмотреть содержимое файла внутри файловой системы
char* view_file_content(const char* filename, FILE* fs_file) {
    if (fs_file == NULL) return NULL;

    fseek(fs_file, 0, SEEK_END);
    long file_size = ftell(fs_file);
    rewind(fs_file);

    char* content = malloc(file_size + 1);
    if (content == NULL) return NULL;

    fread(content, 1, file_size, fs_file);
    content[file_size] = '\0';

    char* file_start = strstr(content, filename);
    if (file_start == NULL) {
        free(content);
        return NULL;
    }

    file_start += strlen(filename);
    while (*file_start == '\n' || *file_start == ' ') file_start++;

    char* file_end = strchr(file_start, '/');
    if (file_end == NULL) file_end = content + file_size;

    long content_length = file_end - file_start;
    char* result = malloc(content_length + 1);
    if (result == NULL) {
        free(content);
        return NULL;
    }

    strncpy(result, file_start, content_length);
    result[content_length] = '\0';
    free(content);

    return result;
}

//Удалить файл внутри файловой системы
int delete_file(const char* filename, FILE* fs_file) {
    if (fs_file == NULL) return -1;

    fseek(fs_file, 0, SEEK_END);
    long file_size = ftell(fs_file);
    rewind(fs_file);

    char* content = malloc(file_size + 1);
    if (content == NULL) return -1;

    fread(content, 1, file_size, fs_file);
    content[file_size] = '\0';

    char* file_start = strstr(content, filename);
    if (file_start == NULL) {
        free(content);
        return -1;
    }

    char* file_end = strchr(file_start, '/');
    if (file_end == NULL) file_end = content + file_size;

    long new_size = file_start - content;
    long remaining_size = file_size - (file_end - content);

    char* new_content = malloc(new_size + remaining_size + 1);
    if (new_content == NULL) {
        free(content);
        return -1;
    }

    strncpy(new_content, content, new_size);
    strncpy(new_content + new_size, file_end, remaining_size);
    new_content[new_size + remaining_size] = '\0';

    freopen(NULL, "w", fs_file);
    fwrite(new_content, 1, new_size + remaining_size, fs_file);
    fflush(fs_file);

    free(content);
    free(new_content);
    return 0;
}

// Создание нового файла в файловой системе
int create_new_file(const char* filename, const char* content, FILE* fs_file) {
    if (fs_file == NULL) return -1;

    // Переходим в конец файла
    fseek(fs_file, 0, SEEK_END);
    
    // Записываем имя файла и содержимое
    fprintf(fs_file, "\n%s\n%s\n/", filename, content);
    fflush(fs_file);
    
    return 0;
}






// Изменение существующего файла
int modify_file(const char* filename, const char* new_content, FILE* fs_file) {
    if (fs_file == NULL) return -1;

    // Получаем текущее содержимое файловой системы
    fseek(fs_file, 0, SEEK_END);
    long file_size = ftell(fs_file);
    rewind(fs_file);

    char* content = malloc(file_size + 1);
    if (content == NULL) return -1;

    fread(content, 1, file_size, fs_file);
    content[file_size] = '\0';

    // Находим файл для изменения
    char* file_start = strstr(content, filename);
    if (file_start == NULL) {
        free(content);
        return -1;
    }

    // Находим конец файла
    char* file_end = strchr(file_start, '/');
    if (file_end == NULL) file_end = content + file_size;

    // Формируем новое содержимое
    long prefix_size = file_start - content;
    long suffix_size = file_size - (file_end - content);

    char* new_content = malloc(prefix_size + strlen(new_content) + suffix_size + 4);
    if (new_content == NULL) {
        free(content);
        return -1;
    }

    // Копируем часть до файла
    strncpy(new_content, content, prefix_size);
    
    // Добавляем новое содержимое
    sprintf(new_content + prefix_size, "%s\n%s\n/", filename, new_content);
    
    // Копируем часть после файла
    strncpy(new_content + prefix_size + strlen(filename) + strlen(new_content) + 3, 
           file_end, suffix_size);

    // Перезаписываем файловую систему
    freopen(NULL, "w", fs_file);
    fwrite(new_content, 1, strlen(new_content), fs_file);
    fflush(fs_file);

    free(content);
    free(new_content);
    return 0;
}

