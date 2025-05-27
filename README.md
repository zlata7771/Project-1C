# Project-1C
Каюкина Злата и Николаева Полина 0907-32

## open_or_create_file
C

FILE* open_or_create_file(const char* filename);
Описание:  
Открывает или создает и открывает файл файловой системы.  
Параметры:  
- filename - строка (const char*), содержащая имя файла.  

Возвращаемое значение:  
Указатель на файл (FILE*). В случае ошибки возвращает NULL.  

---

## view_file_content
C

char* view_file_content(const char* filename, FILE* fs_file);
Описание:  
Просматривает содержимое указанного файла внутри файловой системы.  
Параметры:  
- filename - строка (const char*), содержащая имя файла для просмотра.  
- fs_file - указатель на файл (FILE*), представляющий файловую систему.  

Возвращаемое значение:  
Строка (char*), содержащая содержимое файла. Необходимо освободить память после использования. В случае ошибки возвращает NULL.  

---

## delete_file
C

int delete_file(const char* filename, FILE* fs_file);
Описание:  
Удаляет файл внутри файловой системы.  
Параметры:  
- filename - строка (const char*), содержащая имя файла для удаления.  
- fs_file - указатель на файл (FILE*), представляющий файловую систему.  

Возвращаемое значение:  
Целое число (int):  
- 0 - успешное удаление.  
- -1 - ошибка (файл не найден или ошибка записи).  

---

## create_new_file_in_filesystem
Описание: Создает новый файл в файловой системе, добавляя его в конец.  
Параметры:  
- char** fs_content - указатель на содержимое файловой системы (будет изменено)  
- const char* filename - имя нового файла  
- const char* content - содержимое нового файла  
Возвращаемое значение:  
- int - 0 при успехе, -1 при ошибке  

---

## modify_file_in_filesystem
Описание: Изменяет содержимое существующего файла в файловой системе.  
Параметры:  
- char** fs_content - указатель на содержимое файловой системы (будет изменено)  
- const char* filename - имя изменяемого файла  
- const char* new_content - новое содержимое файла  
Возвращаемое значение:  
- int - 0 при успехе, -1 если файл не найден  
  
---

Наша файловая система предоставляется как библиотека, состоящая из двух файлов:
- filesystem.h - заголовочный файл с объявлениями функций
- filesystem.c - реализация функций

Как подключить к проекту:

1. Добавьте оба файла в ваш проект
2. Включите заголовочный файл в местах использования:
#include "filesystem.h"
3. При компиляции укажите оба исходных файла:
gcc main.c filesystem.c -o myprogram

Доступные функции:
// Открытие/создание файловой системы
FILE* open_or_create_filesystem(const char* filename);

// Просмотр содержимого файла
char* view_file_in_filesystem(const char* fs_content, const char* filename);

// Удаление файла
int delete_file_in_filesystem(char** fs_content, const char* filename);

// Создание нового файла
int create_new_file_in_filesystem(char** fs_content, const char* filename, const char* content);

// Изменение файла
int modify_file_in_filesystem(char** fs_content, const char* filename, const char* new_content);
