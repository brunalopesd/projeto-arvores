#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvoreAvl.h"
#include "rubro.h"
#include "arvoreB.h"



int main() {

  // Inicia árvores AVL, B e Rubro-negra
  Arvore arvore_avl_1;
  inicia_arvore(&arvore_avl_1);

  ArvoreB* arvore_b_1 = criaArvore(2);

  ArvoreR* arvore_rubro = criar_rubro();


  // Cria arquivo CSV
  FILE *fp;
  char* filename = "pior_caso.csv";
  fp = fopen(filename, "w+");

  //Pior caso - valoes decrescente 
  int x, avl, b, rubro; 
  fprintf(fp, "AVL, B, RUBRO");
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

  //CASO MEDIO - valores aleatorios
  limpa_arvore(&arvore_avl_1, arvore_avl_1.raiz);

  Arvore arvore_avl_2[10];
  ArvoreB* arvore_b_2[10];
  ArvoreR* arvore_rubro_2[10];

 // cria 10 arvores para validacao esttistica 
  for (int i = 0; i < 10; i++) {
    inicia_arvore(&arvore_avl_2[i]);
    arvore_b_2[i] = criaArvore(2);
    arvore_rubro_2[i] = criar_rubro();      
  }

  // Caso moderado -  valores aleatórios)
  srand(time(0));
  int t, numeros[1000];
  for(t = 0; t<1000; t++) {
    numeros[t] = rand();
  }

  // Cria arquivo CSV - caso moderado
  filename = "caso_medio.csv";
  fp = fopen(filename, "w+");


  int avl_2, b_2, rubro_2, y;
  fprintf(fp, "AVL, B, R");
  for (y = 0; y < 10; y++) {
    adiciona_no(&arvore_avl_2[y], numeros[y]); 
    avl_2 = operacoes_AVL;

    adicionaChave(arvore_b_2[y], numeros[y]);
    b_2 = operacoes_b;

    adicionar_valor(arvore_rubro_2[y], numeros[y]);
    rubro_2  = operacoes_R;    
    fprintf(fp, "\n%d, %d, %d ", avl_2, b_2, rubro_2);
  }
  fclose(fp);

  for (int c = 0; c < 10; c++) {
    limpa_arvore(&arvore_avl_2[c], arvore_avl_2[c].raiz);
  }

  return 1;
}