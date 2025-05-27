#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

#define MAX_INPUT 256
#define MAX_PARAMS 3

void print_help() {
    printf("Доступные команды:\n");
    printf("создать <имя_файла> <содержимое>\n");
    printf("удалить <имя_файла>\n");
    printf("изменить <имя_файла> <новое_содержимое>\n");
    printf("просмотреть <имя_файла>\n");
    printf("выход - завершение программы\n");
}

int main() {
    char input[MAX_INPUT];
    char* params[MAX_PARAMS];
    char* token;
    int param_count;
    
    FILE* fs_file = open_or_create_filesystem("mydisk.fs");
    if (!fs_file) {
        printf("Ошибка при создании файловой системы\n");
        return 1;
    }
    
    // Чтение текущего содержимого
    fseek(fs_file, 0, SEEK_END);
    long fsize = ftell(fs_file);
    fseek(fs_file, 0, SEEK_SET);
    
    char* fs_content = malloc(fsize + 1);
    if (fsize > 0) fread(fs_content, 1, fsize, fs_file);
    fs_content[fsize] = 0;
    
    printf("Файловая система готова к работе. Введите 'помощь' для списка команд\n");
    
    while (1) {
        printf("> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0; // Удаляем символ новой строки
        
        // Разбиваем ввод на параметры
        param_count = 0;
        token = strtok(input, " ");
        while (token != NULL && param_count < MAX_PARAMS) {
            params[param_count++] = token;
            token = strtok(NULL, " ");
        }
        
        if (param_count == 0) continue;
        
        // Обработка команд
        if (strcmp(params[0], "выход") == 0) {
            break;
        }
        else if (strcmp(params[0], "помощь") == 0) {
            print_help();
        }
        else if (strcmp(params[0], "создать") == 0 && param_count == 3) {
            if (create_new_file_in_filesystem(&fs_content, params[1], params[2]) == 0) {
                printf("Файл '%s' успешно создан\n", params[1]);
            } else {
                printf("Ошибка при создании файла\n");
            }
        }
        else if (strcmp(params[0], "удалить") == 0 && param_count == 2) {
            if (delete_file_in_filesystem(&fs_content, params[1]) == 0) {
                printf("Файл '%s' успешно удален\n", params[1]);
            } else {
                printf("Ошибка при удалении файла\n");
            }
        }
        else if (strcmp(params[0], "изменить") == 0 && param_count == 3) {
            if (modify_file_in_filesystem(&fs_content, params[1], params[2]) == 0) {
                printf("Файл '%s' успешно изменен\n", params[1]);
            } else {
                printf("Ошибка при изменении файла\n");
            }
        }
        else if (strcmp(params[0], "просмотреть") == 0 && param_count == 2) {
            char* content = view_file_in_filesystem(fs_content, params[1]);
            if (content) {
                printf("%s\n", content);
                free(content);
            } else {
                printf("Файл не найден\n");
            }
        }
        else {
            printf("Неизвестная команда или неверные параметры\n");
        }
        
        // Сохраняем изменения в файл
        fseek(fs_file, 0, SEEK_SET);
        fwrite(fs_content, 1, strlen(fs_content), fs_file);
        fflush(fs_file);
    }
    
    free(fs_content);
    fclose(fs_file);
    return 0;
}
