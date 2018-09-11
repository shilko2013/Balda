#pragma once

#include <malloc.h>
#include "dictionary.c"

#ifndef TCHAR
#define TCHAR char
#endif

#define DEFAULT_FIELD_SIZE 5

/*field *game_field = init_field(DEFAULT_FIELD_SIZE);
    fill_field(game_field);
    print_field(game_field);*/

typedef struct {
    int *size;
    TCHAR **field;
} field;

field *init_field(const int size) {
    field *game_field = (field *) malloc(sizeof(field));
    game_field->size = (int *) malloc(sizeof(int));
    *game_field->size = size;
    game_field->field = (TCHAR **) calloc((size_t)size, sizeof(TCHAR *));
    for (int i = 0; i < size; ++i)
        game_field->field[i] = (TCHAR *) malloc(size * sizeof(TCHAR));
    return game_field;
}

void fill_field(const field * const game_field) {
    for (int i = 0; i < *game_field->size; ++i) {
        game_field->field[*game_field->size / 2][i] = 'f';
    }
}

void print_field(const field * const game_field) {
    for (int i = 0; i < *game_field->size; ++i) {
        for (int j = 0; j < *game_field->size; ++j)
            printf("%c ",game_field->field[i][j]);
        printf("\n");
    }
}

void set_letter(const field * const game_field, const int x, const int y, const TCHAR letter) {
    game_field->field[x][y] = letter;
}

TCHAR get_letter(const field * const game_field, const int x, const int y) {
    return game_field->field[x][y];
}