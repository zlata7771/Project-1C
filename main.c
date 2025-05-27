#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"

int main() {
    // Инициализация файловой системы
    FILE* fs_file = open_or_create_filesystem("mydisk.fs");
    if (!fs_file) {
        printf("Ошибка при создании файловой системы\n");
        return 1;
    }

    // Чтение содержимого файловой системы
    fseek(fs_file, 0, SEEK_END);
    long fsize = ftell(fs_file);
    fseek(fs_file, 0, SEEK_SET);
    
    char* fs_content = malloc(fsize + 1);
    fread(fs_content, 1, fsize, fs_file);
    fs_content[fsize] = 0;
    
    // Демонстрация работы функций
    printf("Создаем новый файл...\n");
    create_new_file_in_filesystem(&fs_content, "test.txt", "Это содержимое тестового файла");
    
    printf("Просматриваем созданный файл...\n");
    char* content = view_file_in_filesystem(fs_content, "test.txt");
    if (content) {
        printf("Содержимое файла:\n%s\n", content);
        free(content);
    }
    
    // Перезаписываем файловую систему
    fseek(fs_file, 0, SEEK_SET);
    fwrite(fs_content, 1, strlen(fs_content), fs_file);
    
    // Очистка ресурсов
    free(fs_content);
    fclose(fs_file);
    
    printf("Демонстрация завершена!\n");
    return 0;
}
