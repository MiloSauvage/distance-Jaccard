#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stream.h"
#include "../bst/bst.h"


 //void *(*add_word)(char *word, bst *root)
int retreive_word(FILE *f, bst *t, size_t size
 ){
    size_t k = 0;
    char *word = malloc(size * sizeof(char));
    if(word == NULL){
        return -1;
    }
    int c;
    while((c =fgetc(f)) != EOF){
        if(isspace(c)){
            word[k] = '\0';
            add_word(word, t);
            free(word);
            word = malloc(size * sizeof(char));
            k = 0;
        }
        if(k == size - 1){
            word = realloc(word, size * 2 * sizeof(char));
            if(word == nullptr){
                return -1;
            }
        }printf("%c",c);
        word[k] = (char)c;
        ++k;
    }
    if(k > 0){
        word[k] = '\0';
        add_word(word, t);
    }
    free(word);
    return 0;
}
