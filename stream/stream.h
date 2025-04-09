#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


//recupère un mot dans le fichier et l'ajoute à l'arbre binaire,
// renvoie 0 si tout s'est bien passé, -1 sinon
// size : taille du mot à récupérer
// t : arbre binaire dans lequel on ajoute le mot
// f : fichier dans lequel on récupère le mot
extern int retreive_word(FILE *f, bst *t, size_t size);