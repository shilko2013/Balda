#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifndef TCHAR
#define TCHAR char
#endif

/* Для быстрого поиска словарь разделен на 33 двумерных
 * массива(количество букв) - dictionary_by_letters.
 * В свою очередь каждый dictionary_by_letters хранит массивы
 * с разной длинной слов. То есть получается древовидная структура.
 * Внутри dictionary_by_length слова отсортированы по алфавиту и
 * ищутся бинарным поиском. Имена файла пердставляются в виде
 * "dictionary_L_Le.txt", где L - буква, а Le - длина слова.
 * Каждое слово пишется с новой строки.
 */

typedef struct {
    TCHAR **words;
    int *size;
    //TCHAR * path;
} dictionary_by_length;

typedef struct {
    dictionary_by_length *dicts_length;
    int *size;
} dictionary_by_letters;

typedef struct {
    dictionary_by_letters *dicts_letters;
    int *size;
} dictionary;

typedef dictionary_by_length dict_length;

typedef dictionary_by_letters dict_letters;

dict_length *init_dict_length(const TCHAR letter, const int length) {
    dict_length *dict = (dict_length *) malloc(sizeof(dict_length));
    TCHAR *path = (TCHAR *) malloc(sizeof(TCHAR) * 20);
    snprintf(path, sizeof(TCHAR) * 20, "dictionary_%c_%02d.txt", letter, length);
    FILE *file = fopen(path, "r");
    if (file == NULL)
        return NULL;
    char *string = (char *) malloc(sizeof(char) * length);
    int count = 0;
    while (!feof(file)) {
        TCHAR symbol = (TCHAR) fgetc(file);
        if (symbol == '\n' || symbol == EOF)
            ++count;
    }
    fclose(file);
    file = fopen(path, "r");
    dict->words = (TCHAR **) malloc(sizeof(TCHAR *) * count);
    const int CONST_COUNT = count;
    while (count) {
        fgets(string, length + 3, file); //+3 на случай /r/n
        dict->words[CONST_COUNT - count] = (TCHAR *) malloc(sizeof(TCHAR) * length);
        strncpy(dict->words[CONST_COUNT - count], string, (size_t) length);
        --count;
    }
    fclose(file);
    free(path);
    free(string);
    dict->size = (int *) malloc(sizeof(int));
    *dict->size = CONST_COUNT;
    return dict;
}


dict_letters *init_dict_letter(TCHAR letter) {
    /*do {

    } while (init_dict_length(TCHAR letter, int length) != NULL);*/
    return NULL;
}

dictionary *init_dict() {
    return NULL;
}

int dict_search() {
    return -1;
}

void binary_search() {
}