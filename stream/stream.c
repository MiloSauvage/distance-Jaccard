#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include <ctype.h>
#include "stream.h"

int retreive_word(FILE *f, bst *t, size_t size){
    int k = 0;
    char *word = malloc(size * sizeof(char));
    if(word == NULL){
        return -1;
    }
    int c;
    while((c =fgetc(f)) != EOF){
        if(isspace(c)){
            word + (k+ 1) * sizeof(char) = '\0';
            bst_add_endofpath(t, word);
            free(word);
            k = 0;
        }
        if(k == size - 1){
            word = realloc(word, size * 2 * sizeof(char));
            if(word == nullptr){
                return -1;
            }
        }
        word + k * sizeof(char) = c;
        ++k;
    }
    if(k > 0){
        word + (k + 1) * sizeof(char) = '\0';
        bst_add_endofpath(t, word);
    }
    free(word);
    return 0;
}