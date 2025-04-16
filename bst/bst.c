//  bst.c : partie implantation d'un module polymorphe pour la spécification
//   ABINR du TDA ABinR(T).

#include "bst.h"
#include <string.h>

//=== Type cbst ================================================================

//--- Définition cbst ----------------------------------------------------------

typedef struct cbst cbst;

struct cbst {
  cbst *next[2];
  const void *ref;
  size_t count;
};

//-- petite macro --
#define REPR_TAB 8
#define REPR_SPACE " "
#define REPR_NODE "o"
#define REPR_EMPTY "|"


//--- Raccourcis cbst ----------------------------------------------------------

#define EMPTY()     nullptr
#define IS_EMPTY(p) ((p) == nullptr)
#define LEFT(p)     ((p)->next[0])
#define RIGHT(p)    ((p)->next[1])
#define REF(p)      ((p)->ref)
#define NEXT(p, d)  ((p)->next[(d) > 0])





//===========letter + word =========
void *add_word(char *ref, bst *root) {
    if (!ref) return NULL;

    char *word_copy = strdup(ref);  // Alloue + copie en une opération
    if (!word_copy) return nullptr;

    if (!bst_add_endofpath(root, word_copy)) {
        free(word_copy);
        return nullptr;
    }
    return word_copy;
}

void *add_letter(char *word, bst *root) {
  for (int i = 0; word[i] != '\0'; i++) {
    char *letter = malloc(sizeof(char));
    if (letter == nullptr) {
      bst_dispose(&root);
      return nullptr;
    }
    *letter = word[i];
    if (bst_add_endofpath(root, letter) == nullptr) {
      free(letter);
      return nullptr;
    }
  }
  return word;
}

//======== fin du test

//--- Fonctions cbst -----------------------------------------------------------


//  cbst__dispose : libère les ressources allouées à l'arbre binaire pointé par
//    p.
static void cbst__dispose(cbst *p) {
    if (!IS_EMPTY(p)) {
      cbst__dispose(LEFT(p));
      cbst__dispose(RIGHT(p));
      free(p);
    }
  }


static void *cbst__add_endofpath(cbst **pp, const void *ref,
    int (*compar)(const void *, const void *)){
      if (*pp == nullptr) {
        cbst *p = malloc(sizeof(*p));
      if (p == nullptr) {
        return nullptr;
      }
      *pp = p;
      (*pp)->ref = ref;
      (*pp) -> count = 1;
      return (void *) ref;
    }
    int c = compar(ref, (*pp)->ref);
    if (c == 0) {
      (*pp)->count += 1;
      return (void *)(*pp)->ref;
    }
  return cbst__add_endofpath(&NEXT(*pp, c), ref, compar);
}

void *cbst__search(cbst **pp, const void *ref,
  int (*compar)(const void *, const void *)){
    if(*pp == nullptr){
      return nullptr;
    }
    int c = compar(ref, (*pp)->ref);
     if (c == 0) {
       printf("[mot trouver : %s]\n", (char*)(*pp)->ref);
        return (void *)(*pp)->ref;
      }
    return cbst__search(&NEXT(*pp, c), ref, compar);
}

int cbst__commun_word(cbst *t1, bst *t2) {
    if (t1 == nullptr) {
        return 0;
    }

    int count = (bst_search(t2, t1->ref) != nullptr) ? 1 : 0;

    return count + cbst__commun_word(LEFT(t1), t2)
                + cbst__commun_word(RIGHT(t1), t2);
}

int cbst__union_tree(cbst *t, bst *stock){
  if(t == nullptr || t->ref == nullptr){
      return 0;
  }
  int count = 0;
  if(bst_search(stock, t->ref) == nullptr){
    if(bst_add_endofpath(stock, t->ref) == nullptr){
      return EXIT_FAILURE;
    }
    count = 1;
    return count +cbst__union_tree(LEFT(t), stock)
        + cbst__union_tree(RIGHT(t), stock);
  }
   return count + cbst__union_tree(LEFT(t), stock)
        + cbst__union_tree(RIGHT(t), stock);
}

//int cbst__union_tree(cbst *t, char **message, size_t *size){
    //if(t == nullptr || t->ref  == nullptr){
      //return 0;
    //}
    //printf("message : %s, ref :%s\n", *message, (char*)t->ref);
    //const char *check = strstr(*message, t->ref);
    //if (check == nullptr) {
      //printf("%zu\n",strlen(*message) + strlen(t->ref));
      //if(strlen(*message) + strlen(t->ref) + 1 >= *size) {
        //*size *= 2;
        //*message = realloc(*message, sizeof(char) * (*size));
        //if(*message == nullptr){
          //fprintf(stderr,"Error : probleme de realloc");
          //return EXIT_FAILURE;
        //}
      //}
      //if(strcat(*message, t->ref) == nullptr){
        //fprintf(stderr, "Error : pas possible de faire l'union");
        //return EXIT_FAILURE;
      //}
      //printf("new message : %s\n", *message);
      //return 1 + cbst__union_tree(LEFT(t), message, size)
        //+ cbst__union_tree(RIGHT(t), message, size);
    //}

    //return 0 + cbst__union_tree(LEFT(t), message, size);
        //+ cbst__union_tree(RIGHT(t), message, size);
//}

#define REPR__TAB 4

//  ICI, PROCHAINEMENT, LA SPÉCIFICATION ET LA DÉFINITION DE :
static void cbst__repr_graphic(const cbst *p,
    void (*put)(const void *ref), size_t level) {
  if (IS_EMPTY(p)) {
    printf("%*s%s\n", (int) (REPR_TAB * level), "", REPR_EMPTY);
    return;
  }
  cbst__repr_graphic(RIGHT(p), put, level + 1);
  printf("%*s", (int) (REPR_TAB * level), "");
  printf("%zu:%s",p->count, (char *)p->ref);
  printf("\n");
  cbst__repr_graphic(LEFT(p), put, level + 1);
}

//=== Type bst =================================================================

//--- Définition bst -----------------------------------------------------------

struct bst {
    int (*compar)(const void *, const void *);
    cbst *root;
  };

  //--- Fonctions bst ------------------------------------------------------------

  bst *bst_empty(int (*compar)(const void *, const void *)) {
    bst *t = malloc(sizeof *t);
    if (t == nullptr) {
      return nullptr;
    }
    t->compar = compar;
    t->root = EMPTY();
    return t;
  }

  void bst_dispose(bst **tptr) {
    if (*tptr == nullptr) {
      return;
    }
    cbst__dispose((*tptr)->root);
    free(*tptr);
    *tptr = nullptr;
  }

void *bst_add_endofpath(bst *t, const void *ref){
  if (ref == nullptr) {
    return nullptr;
  }
  return cbst__add_endofpath(&t->root, ref, t->compar);
}

void *bst_search(bst *t, const void *ref){
    if(ref == nullptr){
      return nullptr;
    }
    return cbst__search(&t -> root, ref, t->compar);
}

int bst_common_word(bst *t1, bst* t2){
  if(IS_EMPTY(t1) || IS_EMPTY(t2)){
      return 0;
  }
  return cbst__commun_word(t1->root, t2);
}


//pas vide en entrée
float bst_jaccard_tree(bst *t1, bst *t2){
  if(t1 == nullptr || t2 == nullptr){
      return -1.0;
  }
  int numerateur = bst_common_word(t1, t2);
  int denominateur = bst_union_tree(t1, t2);

  if(denominateur == 0){
    return 0.0;
  }

  return (float)(1.0 - ((float)numerateur/(float)denominateur));

}

int bst_union_tree(bst *t1, bst* t2){
  if(t1 == nullptr || t2 == nullptr){
      return -1;
  }
  if(IS_EMPTY(t1) && IS_EMPTY(t2)){
        return 0;
  }
  bst *stock = bst_empty((int (*)(const void *, const void *)) strcmp);
  if(stock == nullptr){
      return -1;
  }
  int count = cbst__union_tree(t1->root, stock) +
              cbst__union_tree(t2->root, stock);
  bst_dispose(&stock);
  return count;

}

//probleme à regler il faut toujours que ce soit
//l'abre binaire le plus petit appeler en premier
//sinon le resultat est fosser
//int bst_union_tree(bst *t1, bst* t2){
  //printf("tesst\n");
  //if(IS_EMPTY(t1) && IS_EMPTY(t2)){
      //return 0;
  //}
  //size_t size = 100;
  //char *message = malloc(sizeof(char) * size);
  //if(message == nullptr){
     //return -1;
  //}
  //message[0] = '\0';
  //int count2 = cbst__union_tree(t2->root, &message, &size);
  //printf("message after first tree : %s\n", message);
  //int count1 = cbst__union_tree(t1->root, &message, &size);
  //printf("message after seconde tree : %s\n", message);
  //free(message);
  //return count1 + count2;
//}

void bst_repr_graphic(bst *t, void (*put)(const void *ref)) {
  if (t == NULL || IS_EMPTY(t->root)) {
    printf("Arbre vide\n");
    return;
  }
  cbst__repr_graphic(t->root, put, 0);
}

























