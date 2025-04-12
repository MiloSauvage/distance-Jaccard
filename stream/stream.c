#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stream.h"
#include "../bst/bst.h"

//soucis avec les dernier caractère si le fichier est vraiment plein à 100%
//alors les dernier caractère ne seront pas prit
//voir la partie commenter
int retreive_word(FILE *f, bst *t, size_t size){
    size_t k = 0;
    char *word = malloc(size * sizeof(char));
    if(word == NULL){
        return -1;
    }
    int c;
    while((c =fgetc(f)) != EOF){
        if(isspace(c)){
            printf("[%s]\n", word);
            word[k] = '\0';
            add_word(word, t);
            free(word);
            word = malloc(size * sizeof(char));
            k = 0;
            //sauter les putains d'espaces de merde
            while((c = fgetc(f)) != EOF && isspace(c)) {}
        }
        if(k == size - 1){
            word = realloc(word, size * 2 * sizeof(char));
            if(word == nullptr){
                return -1;
            }
        }
        //printf("%c",c);
        word[k] = (char)c;
        ++k;
    }
    //if(k > 0){
        //word[k] = '\0';
        //add_word(word, t);
    //}
    free(word);
    return 0;
}
