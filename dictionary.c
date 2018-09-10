#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define TCHAR char

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
    //TCHAR * path;
} dictionary_by_length;

typedef struct {
    dictionary_by_length *dicts_length;
} dictionary_by_letters;

typedef struct {
    dictionary_by_letters *dicts_letters;
} dictionary;

typedef dictionary_by_length dict_length;

typedef dictionary_by_letters dict_letters;

dict_length *init_dict_length(TCHAR letter, int length) {
    dict_length *dict = (dict_length *) malloc(sizeof(dict_length));
    TCHAR *path = NULL;
    snprintf(path, sizeof(TCHAR) * 19, "dictionary_%c_%02d", letter, length);
    FILE *file = fopen(path, "r");
    if (file == NULL)
        return NULL;
    char *string = (char *) malloc(sizeof(char) * length);
    int count = 0;
    while (!feof(file)) {
        if (fgetc(file) == '\n')
            ++count;
    }
    fclose(file);
    file = fopen(path, "r");
    dict->words = (TCHAR **) malloc(sizeof(TCHAR) * count);
    const int CONST_COUNT = count;
    while (!feof(file)) {
        fgets(string, length, file);
        dict->words[CONST_COUNT - count] = (TCHAR *) malloc(sizeof(TCHAR) * length);
        dict->words[CONST_COUNT - count] = string;
        --count;
        //запись в массив
    }
    fclose(file);
    free(path);
    free(string);
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
    return NULL;
}

void binary_search() {
}