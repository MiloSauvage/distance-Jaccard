#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "scale.h"

//int main(){
  //const char *a = "ABCDE";
  //const char *b = "BCF";

  //int cl = common_letters(a, b);
  //int tl = total_letters(a, b);

  //printf("Communes : %d\n", cl);
  //printf("Total : %d\n", tl);
  //printf("Distance de Jaccard : %f\n", 1-((float)cl/(float)tl));

  //return EXIT_SUCCESS;
//}

#define OPT__SHORT  "-"
#define OPT__LONG   "--"
#define OPT_HELP_L  "help"

#define BST_L "Binary search tree"



// =======fonction outil=======
void put(const void *p) {
  int x;
  scale_value(p, &x);
  printf("%d", x);
}

//=======le main========

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];

    // creation arbre
    bst *tree = bst_empty((int (*)(const void *, const void *)) strcmp);
    if (tree == NULL) {
        fprintf(stderr, "Erreur : Impossible d’allouer l’arbre binaire.\n");
        return EXIT_FAILURE;
    }

    // Ajout arbre
    for (int i = 0; input[i] != '\0'; i++) {
        char *letter = malloc(sizeof(char));
        if (letter == NULL) {
            fprintf(stderr, "Erreur : Allocation mémoire échouée.\n");
            bst_dispose(&tree);
            return EXIT_FAILURE;
        }
         // Stocke la lettre
        *letter = input[i];

        if (bst_add_endofpath(tree, letter) == NULL) {
            fprintf(stderr, "Erreur : Impossible d’ajouter '%c' dans l’arbre.\n", input[i]);
            free(letter);
        }
    }

    // Affichage basique
    printf("Arbre binaire :\n");
    bst_repr_graphic(tree, put);
    printf("\n");

    bst_dispose(&tree);

    return EXIT_SUCCESS;
}






