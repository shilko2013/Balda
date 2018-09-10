#pragma once

#include <malloc.h>
#include "dictionary.c"

#ifndef TCHAR
#define TCHAR char
#endif

/*field *game_field = get_field(5);
    fill_field(game_field);
    print_field(game_field);*/

typedef struct {
    int *size;
    TCHAR **field;
} field;

field *get_field(const int size) {
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

void set_letter(const field * const game_field, int x, int y, TCHAR letter) {
    game_field->field[x][y] = letter;
}

TCHAR get_letter(field *game_field, int x, int y) {
    return game_field->field[x][y];
}