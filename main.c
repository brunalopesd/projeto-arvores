#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvoreAvl.h"
#include "rubro.h"
#include "arvoreB.h"



int main() {

  //iniciar árvores AVL, B e Rubro-negra
  Arvore arvore_avl_1;
  inicia_arvore(&arvore_avl_1);
  ArvoreB* arvore_b_1 = criaArvore(10);
  ArvoreR* arvore_rubro = criar_rubro();

  //criar arquivo CSV (permissoes)
  FILE *fp;
  char* filename = "pior_caso.csv";
  fp = fopen(filename, "w+");

  //pior caso - valores decrescente 
  int x, avl, b, rubro; 
  fprintf(fp, "Avl, B, Rubro");
  for (x = 999; x >= 0; x--) {
    adiciona_no(&arvore_avl_1, x); 
    avl = operacoes_AVL;

    adicionaChave(arvore_b_1, x);
    b = operacoes_b;

    adicionar_valor(arvore_rubro, x);
    rubro  = operacoes_R;

    fprintf(fp, "\n%d, %d, %d ", avl, b, rubro);
  }
  fclose(fp);

  //caso medio - valores aleatorios
  int i, j, *conjunto_numeros[1000];

  //gera conjuntos aleatorios crescentes
  srand(time(0));
  for (i = 0; i < 1000; i++) {
    conjunto_numeros[i] = malloc((i + 1) * sizeof(int));
    for (j = 0; j <= i; j++) {
      conjunto_numeros[i][j] = rand();
    }
  }
  //recriar arvores
  limpa_arvore(&arvore_avl_1, arvore_avl_1.raiz);
  Arvore arvoreAvl2[1000];
  ArvoreB* arvoreB2[1000];
  ArvoreR* arvore_rubro_2[1000];


  for (i = 0; i < 1000; i++) {
    inicia_arvore(&arvoreAvl2[i]);
    arvoreB2[i] = criaArvore(10);
    arvore_rubro_2[i] = criar_rubro();
  }

  filename = "caso_medio.csv";
  fp = fopen(filename, "w+");

  fprintf(fp, "Avl, B, Rubro");
  int rubro2, avl2, b2; 
  for (i = 0; i < 1000; i++) {
    for (j = 0; j < i; j++) {
      adiciona_no(&arvoreAvl2[i], conjunto_numeros[i][j]);
      avl2 = operacoes_AVL;
      adicionaChave(arvoreB2[i], conjunto_numeros[i][j]);
      b2 = operacoes_b;
      adicionar_valor(arvore_rubro_2[i], conjunto_numeros[i][j]);
      rubro2 = operacoes_R;
    
    }
    fprintf(fp, "\n%d, %d, %d", avl2, b2, rubro2);
    }
    fclose(fp);

  //limpar memoria
    for (i = 0; i < 1000; i++) {
      limpa_arvore(&arvoreAvl2[i], arvoreAvl2[i].raiz);
      free(conjunto_numeros [i]);
    }
  return 1;
}
