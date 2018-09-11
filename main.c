#include <stdio.h>
#include "field.c"

int main() {
    dict_length *dict = init_dict_length("Ó",5,1);
    for (int i = 0; i < *dict->size; ++i) {
        printf("%s\n",dict->words[i]);
    }
    return 0;
}