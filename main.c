#include <stdio.h>
#include "field.c"

int main() {
    field *game_field = get_field(5);
    fill_field(game_field);
    print_field(game_field);
    return 0;
}