#include <stdio.h>
#include <stdlib.h>
#include <str.h>

int main(){
  const char *a = "ABCDE";
  const char *b = "BCF";

  int cl = common_letters(a, b);
  int tl = total_letters(a, b);

  printf("Communes : %d\n", cl);
  printf("Total : %d\n", tl);
  printf("Distance de Jaccard : %f\n", 1-((float)cl/(float)tl));

  return EXIT_SUCCESS;
}

