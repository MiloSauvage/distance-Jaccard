//  bst.c : partie implantation d'un module polymorphe pour la spécification
//   ABINR du TDA ABinR(T).

#include "bst.h"

//=== Type cbst ================================================================

//--- Définition cbst ----------------------------------------------------------

typedef struct cbst cbst;

struct cbst {
  cbst *next[2];
  const void *ref;
  size_t count;
};

//-- petite macro --
#define REPR_TAB 4
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


//===========test
void *add_word(char *ref, bst *root) {
  char *word = malloc(sizeof(*word));
  if (word == nullptr) {
    return nullptr;
  }
  word = ref;
  if (bst_add_endofpath(root, word) == nullptr) {
    free(word);
    return nullptr;
  }
  return word;
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


void bst_repr_graphic(bst *t, void (*put)(const void *ref)) {
  if (t == NULL || IS_EMPTY(t->root)) {
    printf("Arbre vide\n");
    return;
  }
  cbst__repr_graphic(t->root, put, 0);
}

























