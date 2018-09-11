#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>

#ifndef TCHAR
#define TCHAR char
#endif

#define CATALOG_NAME "dictionary"
#define FILE_NAME_LENGTH 21
#define MAX_WORD_LENGTH 25
#define RUS_COUNT_LETTERS 33
#define EN_COUNT_LETTERS 26
#define RUS 1
#define EN 0

/* Для быстрого поиска словарь разделен на 33 двумерных
 * массива(количество букв) - dictionary_by_letters.
 * В свою очередь каждый dictionary_by_letters хранит массивы
 * с разной длинной слов. То есть получается древовидная структура.
 * Внутри dictionary_by_length слова отсортированы по алфавиту и
 * ищутся бинарным поиском. Имена файла пердставляются в виде
 * "dictionary_Lt_Le.txt", где Lt - номер буквы, начиная
 * с нуля [0;32], не считая буквы Ё, которая имеет номер 33, а Le - длина слова [2;25].
 * Каждое слово пишется с новой строки.
 */

typedef struct {
    TCHAR **words;
    int *size;
    //TCHAR * path;
} dictionary_by_length;

typedef struct {
    dictionary_by_length **dicts_length;
    int *size;
} dictionary_by_letters;

typedef struct {
    dictionary_by_letters **dicts_letters;
    int *size;
} dictionary;

typedef dictionary_by_length dict_length;

typedef dictionary_by_letters dict_letters;

int letter_to_int(const TCHAR *const letter, int rus) {
    int letter_number = letter[0];
    if (rus) { //манипуляции для русского языка
        letter_number += 64; //so much magic constants :)
        if (letter_number == -24) //буква Ё
            letter_number = 33;
    } else {
        letter_number -= 65; // англ яз
    }
    return letter_number;
}

/*
 * @param letter - Прописная буква алфавита
 * @param length - Длина слов
 * @param rus - флаг русского языка
 */
dict_length *init_dict_length(const int letter_number, const int length, const int rus) {
    int language_length = length; //отвечает за unicode
    if (rus)                    //манипуляции для русского языка
        language_length *= 2; //16 бит на символ вместо 8
    dict_length *dict = (dict_length *) malloc(sizeof(dict_length));
    TCHAR *path = (TCHAR *) malloc(sizeof(TCHAR) * FILE_NAME_LENGTH + strlen(CATALOG_NAME) + 2); //2 for slashes
    snprintf(path, sizeof(TCHAR) * FILE_NAME_LENGTH + strlen(CATALOG_NAME) + 2, CATALOG_NAME "\\dictionary_%02d_%02d.txt", letter_number, length);
    FILE *file = fopen(path, "r");
    if (file == NULL)
        return NULL;
    char *string = (char *) malloc(sizeof(char) * language_length);
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
        fgets(string, language_length + 3, file); //+3 на случай /r/n
        dict->words[CONST_COUNT - count] = (TCHAR *) malloc(sizeof(TCHAR) * language_length);
        strncpy(dict->words[CONST_COUNT - count], string, (size_t) language_length);
        --count;
    }
    fclose(file);
    free(path);
    free(string);
    dict->size = (int *) malloc(sizeof(int));
    *dict->size = CONST_COUNT;
    return dict;
}

dict_letters *init_dict_letter(const int letter_number, int rus) {
    dict_letters *dict = (dict_letters *) malloc(sizeof(dict_letters));
    dict->size = (int *) malloc(sizeof(int));
    *dict->size = MAX_WORD_LENGTH;
    dict->dicts_length = (dict_length **) malloc(sizeof(dict_length *) * MAX_WORD_LENGTH);
    for (int i = 0; i < MAX_WORD_LENGTH; ++i)
        dict->dicts_length[i] = init_dict_length(letter_number, i, rus);
    return dict;
}

void print_dict(dictionary *d) { //for debugging
    for (int i = 0; i < *d->size; ++i) {
        if (d->dicts_letters[i] != NULL) {
            for (int j = 0; j < *d->dicts_letters[i]->size; ++j) {
                if (d->dicts_letters[i]->dicts_length[j] != NULL)
                    for (int k = 0; k < *d->dicts_letters[i]->dicts_length[j]->size; ++k)
                        printf("%s\n",d->dicts_letters[i]->dicts_length[j]->words[k]);
            }
            printf("\n");
        }
    }
}

dictionary *init_dict(int rus) {
    dictionary *dict = (dictionary *) malloc(sizeof(dictionary));
    dict->size = (int *) malloc(sizeof(int));
    if (rus)
        *dict->size = RUS_COUNT_LETTERS;
    else
        *dict->size = EN_COUNT_LETTERS;
    dict->dicts_letters = (dict_letters **) malloc(sizeof(dict_letters *) * *dict->size);
        for (int i = 0; i < *dict->size; ++i)
            dict->dicts_letters[i] = init_dict_letter(i, rus);
    return dict;
}

int dict_search(const TCHAR * const word) {
    return -1;
}

int binary_search() {
    return -1;
}