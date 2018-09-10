#include <malloc.h>
#include <stdio.h>
#include "dictionary.c"

#define TCHAR char

typedef struct {
    int *size;
    TCHAR **field;
} field;

field *get_field(int n) {
    field *game_field = (field *) malloc(sizeof(field));
    game_field->size = (int *) malloc(sizeof(int));
    *game_field->size = n;
    game_field->field = (TCHAR **) malloc(n * sizeof(TCHAR *));
    for (int i = 0; i < n; ++i)
        game_field->field[i] = (TCHAR *) malloc(n * sizeof(TCHAR));
    return game_field;
}

void fill_field(field *game_field) {
    for (int i = 0; i < *game_field->size; ++i) {
        game_field->field[*game_field->size / 2][i] = 'f';
    }
}

void print_field(field *game_field) {
    for (int i = 0; i < *game_field->size; ++i) {
        for (int j = 0; j < *game_field->size; ++j)
            printf("%c ",game_field->field[i][j]);
        printf("\n");
    }
}

void set_letter(field *game_field, int x, int y, TCHAR letter) {
    game_field->field[x][y] = letter;
}

TCHAR get_letter(field *game_field, int x, int y) {
    return game_field->field[x][y];
}