#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"
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
  int x; scale_value(p, &x);printf("%d", x);
}

//=======le main========

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    //tableau d'arbre binaire
    bst **roots = malloc((size_t)argc * sizeof(*roots));
    if(roots == nullptr){
      return EXIT_FAILURE;
    }


    // creation des arbres
    for (int j = 1; j < argc; ++j) {

        roots[j] = bst_empty((int (*)(const void *, const void *)) strcmp);
        if (roots[j] == nullptr) {
            fprintf(stderr, "Erreur : Impossible d’allouer l’arbre binaire numéro %d.\n", j);
            for (int k = 1; k <= j; ++k) {
                bst_dispose(&roots[k]);
            }
            free(roots);
            return EXIT_FAILURE;
        }
    }

    //==ajout dans les arbres==
    for (int q = 1; q < argc; ++q) {
      const char *resultat = strstr(argv[1],".txt");
      if(resultat == nullptr){
        //==quand on ajoute les lettes de chaque mot dans un arbres

        add_letter(argv[q], roots[q]);
      }
      else{
        //===quand c'est des fichier txt
        const char *checkpoint = strstr(argv[q],".txt");
        if(checkpoint == nullptr){
            fprintf(stderr,"Error : %s <file.txt>\n", argv[q]);
            return EXIT_FAILURE;
        }
        FILE *f = fopen(argv[q], "r");
        if (f == nullptr) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s.\n", argv[q]);
            return EXIT_FAILURE;
        }

        if (retreive_word(f, roots[q], 100) != 0) {
            fprintf(stderr, "Erreur lors de l’extraction des mots depuis %s.\n", argv[q]);
            fclose(f);
            return EXIT_FAILURE;
        }

        fclose(f);
      }
      printf("Arbre binaire %d :\n", q);
      bst_repr_graphic(roots[q], put);

    }
    printf("l'intersection : %d\n", bst_common_word(roots[1], roots[2]));
    //printf("l'union : %d", bst_union_tree(roots[1], roots[2]));

    return EXIT_SUCCESS;
}





