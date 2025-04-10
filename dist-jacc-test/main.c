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


    // creation arbre
    bst *root = bst_empty((int (*)(const void *, const void *)) strcmp);
    if (root == NULL) {
        fprintf(stderr, "Erreur : Impossible d’allouer l’arbre binaire.\n");
        return EXIT_FAILURE;
    }

    //ajout un mot dans l'abre
    if(argc == 2){
      const char *resultat = strstr(argv[1],".txt");
      if(resultat != nullptr){
        FILE *f = fopen(argv[1], "r");
        if(retreive_word(f, root, 100) == 1){
          return EXIT_FAILURE;
        }
        fclose(f);
      }
      else{
        add_letter(argv[1], root);
        printf("Arbre binaire :\n");
        bst_repr_graphic(root, put);
        bst_dispose(&root);
        return EXIT_SUCCESS;
      }

    }

     //Ajout mots arbre
    //for (int i = 1; i < argc; i++) {
        //if (add_word(argv[i], root) == nullptr ){
            //fprintf(stderr, "Erreur lors de l'ajout du mot '%s'\n", argv[i]);
        //}
    //}

    // Affichage basique
    printf("Arbre binaire :\n");
    bst_repr_graphic(root, put);
    printf("\n");

    bst_dispose(&root);

    return EXIT_SUCCESS;
}





