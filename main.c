#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arvore_avl.h"



int main() {

  int conjunto_dados[100], i, j


  //Gera chaves ordenadas - crescente - pior caso
  


  //Gera chaves aleatorias - caso medio
  srand(time(0));
  for (i = 0; i < 100; i++) {
    conjuntos[i] = malloc((i + 1) * sizeof(int));
    for (j = 0; j <= i; j++) {
      conjuntos[i][j] = rand();
    }
 }




  Arvore a;
  inicia_arvore(&a);
}