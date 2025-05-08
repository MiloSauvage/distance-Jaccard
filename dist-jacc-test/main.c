#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include "stream.h"
#include "bst.h"
#include "scale.h"

#define TRACK fprintf(stderr, "*** %s:%d\n", __func__, __LINE__)

#define OPT__SHORT  "-"
#define OPT__LONG   "--"

#define PROMPT_CHAR "-"

#define OPT_HELP_L  OPT__LONG "help"
#define OPT_HELP_S OPT__SHORT "?"

#define OPT_USAGE OPT__LONG "usage"
#define OPT_VERSION OPT__LONG "version"

#define OPT_BI_TR_S OPT__SHORT "a"
#define OPT_HASH_S OPT__SHORT "h"
#define OPT_TYPE_S OPT__SHORT "w"

#define OPT_AVL_BT "avl-binary-tree"
#define OPT_HASH_TABLE "hash-table"


#define OPT_GRAPH_S OPT__SHORT "g"
#define OPT_GRAPH_L OPT__LONG "graph"

#define OPT_WORD_PROCESSING OPT__LONG "words-processing"

#define BST_L "Binary search tree"

[[noreturn]] void crash(char *argv[], const char *format, ...) {
  va_list ap;
  va_start(ap);
  fprintf(stderr, "%s: ", argv[0]);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fprintf(stderr,
      "\nTry \"%s " OPT_HELP_L "\" for more information\n.",
      argv[0]);
  exit(EXIT_FAILURE);
}

[[noreturn]] void help(char *argv[]) {
  printf("Usage: %s [OPTION]... FILE1 FILE2 [FILE]...\n", argv[0]);
  printf("\n");
  printf("Computes Jaccard dissimilarities of sets of words in FILEs.\n");
  printf("\n");
  printf(
      "For any pair of FILEs, dissimilarity is displayed first to four \
decimal places, followed by the two FILEs in the pair. A word is, by default, \
a maximum length sequence of characters that do not belong to the white-space \
characters set.");
  printf("\n");
  printf(
      "Read the standard input for any FILE that is '-' on command line. \
The standard input is displayed as a pair of double quotation marks in \
productions.\n");
  printf("\n");
  // Program Information
  printf("Program Information\n");
  printf("  " OPT_HELP_S ", " OPT_HELP_L "\n");
  printf("\tPrint this help message and exit.\n");
  printf("\n");
  printf("  " OPT_USAGE "\n");
  printf("\tPrint a short usage message and exit.\n");
  printf("\n");
  printf("  " OPT_VERSION "\n");
  printf("\tPrint version information.\n");
  printf("\n");
  // Processing
  printf("Processing\n");
  printf("  "OPT_BI_TR_S "\tSame as " OPT_WORD_PROCESSING "=" OPT_AVL_BT ".\n");
  printf("\n");
  printf("  "OPT_HASH_S "\tSame as "OPT_WORD_PROCESSING
      "=" OPT_HASH_TABLE ".\n");
  printf("\n");
  printf("  " OPT_TYPE_S " TYPE, " OPT_WORD_PROCESSING "=TYPE\n");
  printf(
      "\tProcess the words according to the data structure specified by \
TYPE. The available values for TYPE are self explanatory: 'avl-binary-tree' \
and 'hash-table'. Default is 'hash-table'.\n");
  printf("\n");
  // Input Control
  // Output Control
  // File Selection
  printf(
      "White-space and punctuation characters conform to the standard. At \
most 64 FILEs are supported.\n");
  exit(EXIT_SUCCESS);
}

// =======fonction outil=======
void put(const void *p) {
  int x;
  scale_value(p, &x);
  printf("%d", x);
}

//=======le main========

int main(int argc, char *argv[]) {
  int r = EXIT_SUCCESS;
  if (argc == 0) {
    abort();
  }
  bool do_graph = false;
  FILE **files = nullptr;
  int n_file = 0;
  for (size_t k = 1; k < (size_t)argc; ++k) {
    if (strcmp(argv[k], OPT_HELP_L) == 0
        || strcmp(argv[k], OPT_HELP_S) == 0) {
      help(argv);
    } else if(strcmp(argv[k], OPT_GRAPH_S) == 0
              || strcmp(argv[k], OPT_GRAPH_L) == 0){
      do_graph = true;
    } else {
      errno = 0;
      FILE *file = stdin;
      if(strcmp(argv[k], PROMPT_CHAR) != 0){
          file = fopen(argv[k], "r");
      }
      if (file == nullptr || errno != 0) {
        crash(argv, "Can't open for reading file \"%s\"\n", argv[k]);
      }
      ++n_file;
      files = realloc(files, sizeof(*files) * (unsigned long int) n_file);
      if(files == nullptr){
        goto error_capacity;
      }
      files[n_file-1] = file;
    }
  }

  #define STR(s)  #s
  #define XSTR(s) STR(s)
  #define WORD_LENGTH_MAX 31


  long int n = 0;
  char w[WORD_LENGTH_MAX + 1];
  while (scanf("%" XSTR(WORD_LENGTH_MAX) "s", w) == 1) {
    ++n;
    if (strlen(w) == WORD_LENGTH_MAX) {
      fprintf(stderr,
          "*** Warning: Word '%s...' possibly sliced\n", w);
    }
    char *t = malloc(strlen(w) + 1);
    strcpy(t, w);
  }
  fprintf(stderr, "--- Info: Number of words read: %ld\n", n);

  return EXIT_SUCCESS;
  printf("%d\n%s\n", n_file, do_graph ? "" : "");

  if (argc < 2) {
    crash(argv, "Missing operand.");
    return EXIT_FAILURE;
  }

  bst **roots = malloc((size_t) argc * sizeof(*roots));
  if (roots == nullptr) {
    return EXIT_FAILURE;
  }
  //=======teste avec que deux fichiers texte
  //bst *a1 = bst_empty((int (*)(const void *, const void *)) strcmp);
  //bst *a2 = bst_empty((int (*)(const void *, const void *)) strcmp);
  //if (a1 == nullptr || a2 == nullptr) {
  //return EXIT_FAILURE;
  //}
  //FILE *f1 = fopen(argv[1], "r");
  //FILE *f2 = fopen(argv[2], "r");
  //if (retreive_word(f1, a1, 100) != 0) {
  //fprintf(stderr, "Erreur lors de l’extraction des mots depuis %s.\n",
  //argv[1]);
  //fclose(f1);
  //return EXIT_FAILURE;
  //}
  //if (retreive_word(f2, a2, 100) != 0) {
  //fprintf(stderr, "Erreur lors de l’extraction des mots depuis %s.\n",
  //argv[2]);
  //fclose(f2);
  //return EXIT_FAILURE;
  //}
  //fclose(f1);
  //fclose(f2);
  //printf("Arbre binaire %d :\n", 0);
  //bst_repr_graphic(a2, put);
  //printf("Arbre binaire %d :\n", 1);
  //bst_repr_graphic(a1, put);
  //printf("l'intersection : %d\n", bst_common_word(a1, a2));
  //printf("l'union : %d\n", bst_union_tree(a1, a2));
  //bst_dispose(&a1);
  //bst_dispose(&a2);
  //====fin du test
  //creation des arbres
  for (int j = 1; j < argc; ++j) {
    roots[j] = bst_empty((int (*)(const void *, const void *)) strcmp);
    if (roots[j] == nullptr) {
      fprintf(stderr,
          "Erreur : Impossible d’allouer l’arbre binaire numéro%d.\n", j);
      for (int k = 0; k <= j; ++k) {
        bst_dispose(&roots[k]);
      }
      free(roots);
      return EXIT_FAILURE;
    }
  }
  //==ajout dans les arbres==
  for (int q = 1; q < argc; ++q) {
    const char *resultat = strstr(argv[1], ".txt");
    if (resultat == nullptr) {
      //==quand on ajoute les lettes de chaque mot dans un arbres
      add_letter(argv[q], roots[q]);
    } else {
      //===quand c'est des fichier txt
      const char *checkpoint = strstr(argv[q], ".txt");
      if (checkpoint == nullptr) {
        fprintf(stderr, "Error : %s <file.txt>\n", argv[q]);
        return EXIT_FAILURE;
      }
      FILE *f = fopen(argv[q], "r");
      if (f == nullptr) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s.\n",
            argv[q]);
        return EXIT_FAILURE;
      }
      if (retreive_word(f, roots[q], 100) != 0) {
        fprintf(stderr, "Erreur lors de l’extraction des mots depuis %s.\n",
            argv[q]);
        fclose(f);
        return EXIT_FAILURE;
      }
      fclose(f);
    }
    printf("Arbre binaire %d :\n", q);
    bst_repr_graphic(roots[q], put);
  }
  printf("teste de merde\n");
  int numerateur = bst_common_word(roots[1], roots[2]);
  int denominateur = bst_union_tree(roots[1], roots[2]);
  printf("l'intersection : %d\n", numerateur);
  printf("l'union : %d\n", denominateur);
  printf("jaccard : %f\n", bst_jaccard_tree(numerateur, denominateur));
  //graph();
  //liberer la memoire
  for (int l = 0; l < argc; ++l) {
    bst_dispose(&roots[l]);
  }
  goto dispose;

  goto dispose;
error_capacity:
  fprintf(stderr, "*** Error: Not enough memory\n");
  goto error;
/*error_read:
  fprintf(stderr, "*** Error: A read error occurs\n");
  goto error;
error_write:
  fprintf(stderr, "*** Error: A write error occurs\n");
  goto error;*/
error:
  r = EXIT_FAILURE;
  goto dispose;
dispose:
  //hashtable_dispose(&ht);
  //if (has != nullptr) {
    //holdall_apply(has, rfree);
  //}
  //holdall_dispose(&has);
  //if (hacptr != nullptr) {
    //holdall_apply(hacptr, rfree);
  //}
  //holdall_dispose(&hacptr);
  return r;
}
