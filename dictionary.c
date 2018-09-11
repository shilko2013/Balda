#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>

#ifndef TCHAR
#define TCHAR char
#endif

#define FILE_NAME_LENGTH 21
#define MAX_WORD_LENGTH 25

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
dict_length *init_dict_length(const TCHAR *const letter, const int length, const int rus) {
    int letter_number = letter_to_int(letter, rus);
    int language_length = length; //отвечает за unicode
    if (rus)                    //манипуляции для русского языка
        language_length *= 2; //16 бит на символ вместо 8
    dict_length *dict = (dict_length *) malloc(sizeof(dict_length));
    TCHAR *path = (TCHAR *) malloc(sizeof(TCHAR) * FILE_NAME_LENGTH);
    snprintf(path, sizeof(TCHAR) * FILE_NAME_LENGTH, "dictionary_%02d_%02d.txt", letter_number, length);
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

dict_letters *init_dict_letter(const TCHAR *letter, int rus) {
    dict_letters *dict = (dict_letters *) malloc(sizeof(dict_letters));
    dict->size = (int *) malloc(sizeof(int));
    *dict->size = MAX_WORD_LENGTH;
    dict->dicts_length = (dict_length **) malloc(sizeof(dict_length *) * MAX_WORD_LENGTH);
    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        dict->dicts_length[i] = init_dict_length(letter, i, rus);
    }
    return dict;
}

void print(dict_letters *d) {
    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        if (d->dicts_length[i] != NULL)
            for (int j = 0; j < *(d->dicts_length[i]->size); ++j) {
                printf("%s\n", d->dicts_length[i]->words[j]);
            }
        printf("\n");
    }
}

dictionary *init_dict() {
    return NULL;
}

int dict_search() {
    return -1;
}

void binary_search() {
}