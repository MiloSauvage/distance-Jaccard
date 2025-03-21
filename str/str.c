#include <stdio.h>
#include <str.h>

#define ALPHABET_SIZE 26

// let_in_word : parcours le mot associé à word, renvoie 1 si la recherche est
//    un succès, 0 sinon.
int let_in_word(char letter, const char *word){
  char *p = (char *)word;
  while(*p != letter && *p != '\0'){
    ++p;
  }
  return *p == letter ? 1 : 0;
}

int common_letters(const char *a, const char *b){
  int cpt = 0;
  char *p = (char *)a;
  while(*p != '\0'){
    cpt += let_in_word(*p, b);
    ++p;
  }
  return cpt;
}

int total_letters(const char *a, const char *b){
  int cpt[ALPHABET_SIZE] = {0};
  char *p = (char *)a;
  char *q = (char *)b;
  while(*p != '\0'){
    cpt[*p - 'A'] = 1;
    ++p;
  }
  while(*q != '\0'){
    cpt[*q - 'A'] = 1;
    ++q;
  }
  int c = 0;
  for(size_t i = 0; i < ALPHABET_SIZE; ++i){
    c += cpt[i];
  }
  return c;
}
