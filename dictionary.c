#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>

#ifndef TCHAR
#define TCHAR char
#endif

#define FILE_NAME_LENGHT 21

/* Для быстрого поиска словарь разделен на 33 двумерных
 * массива(количество букв) - dictionary_by_letters.
 * В свою очередь каждый dictionary_by_letters хранит массивы
 * с разной длинной слов. То есть получается древовидная структура.
 * Внутри dictionary_by_length слова отсортированы по алфавиту и
 * ищутся бинарным поиском. Имена файла пердставляются в виде
 * "dictionary_Lt_Le.txt", где Lt - номер буквы, начиная
 * с нуля, не считая буквы Ё, которая имеет номер 33, а Le - длина слова.
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

/*
 * @param letter - Прописная буква алфавита
 * @param length - Длина слов
 * @param rus - флаг русского языка
 */
dict_length *init_dict_length(const TCHAR * const letter, const int length, const int rus) {
    int letter_number = letter[0];
    int language_length = length; //отвечает за unicode
    if (rus) { //манипуляции для русского языка
        letter_number += 64;
        if (letter_number == -24) //буква Ё
            letter_number = 33;
        language_length *= 2; //16 бит на символ вместо 8
    }
    else {
        letter_number -= 65; // англ яз
    }
    dict_length *dict = (dict_length *) malloc(sizeof(dict_length));
    TCHAR *path = (TCHAR *) malloc(sizeof(TCHAR) * FILE_NAME_LENGHT);
    snprintf(path, sizeof(TCHAR) * FILE_NAME_LENGHT, "dictionary_%02d_%02d.txt", letter_number, length);
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

dict_letters *init_dict_letter(const TCHAR letter) {
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