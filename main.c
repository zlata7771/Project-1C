#include <stdio.h>
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
    FILE* fs = open_or_create_file("my_filesystem.fs");
    if (!fs) {
        printf("Ошибка при открытии файловой системы\n");
        return 1;
    }

    char input[MAX_INPUT];
    char* params[MAX_PARAMS];
    char* token;
    int param_count;

    printf("Файловая система. Введите 'помощь' для списка команд\n");

    while (1) {
        printf("> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0';

        param_count = 0;
        token = strtok(input, " ");
        while (token != NULL && param_count < MAX_PARAMS) {
            params[param_count++] = token;
            token = strtok(NULL, " ");
        }

        if (param_count == 0) continue;

        if (strcmp(params[0], "выход") == 0) {
            break;
        } else if (strcmp(params[0], "помощь") == 0) {
            print_help();
        } else if (strcmp(params[0], "создать") == 0 && param_count == 3) {
            if (create_new_file(params[1], params[2], fs) == 0) {
                printf("Файл '%s' создан\n", params[1]);
            } else {
                printf("Ошибка при создании файла\n");
            }
        } else if (strcmp(params[0], "удалить") == 0 && param_count == 2) {
            if (delete_file(params[1], fs) == 0) {
                printf("Файл '%s' удален\n", params[1]);
            } else {
                printf("Ошибка при удалении файла\n");
            }
        } else if (strcmp(params[0], "изменить") == 0 && param_count == 3) {
            if (modify_file(params[1], params[2], fs) == 0) {
                printf("Файл '%s' изменен\n", params[1]);
            } else {
                printf("Ошибка при изменении файла\n");
            }
        } else if (strcmp(params[0], "просмотреть") == 0 && param_count == 2) {
            char* content = view_file_content(params[1], fs);
            if (content) {
                printf("< %s\n", content);
                free(content);
            } else {
                printf("Файл не найден\n");
            }
        } else {
            printf("Неверная команда или параметры. Введите 'помощь' для справки\n");
        }
    }

    fclose(fs);
    return 0;
}
