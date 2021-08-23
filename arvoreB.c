#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

ArvoreB* criaArvore(int ordem) {
  operacoes_b = 0;
  ArvoreB* a = malloc(sizeof(ArvoreB));
  a->ordem = ordem;
  a->raiz = criaNo(a);

  return a;
}

Nob* criaNo(ArvoreB* arvore) {
  operacoes_b++;
  int max = arvore->ordem * 2;
  Nob* no = malloc(sizeof(Nob));
  no->pai = NULL;
  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(Nob) * (max + 2));
  no->total = 0;

  for (int i = 0; i < max + 2; i++) {
    no->filhos[i] = NULL;
  }
  return no;
}

void percorreArvore(Nob* no) {
  if (no != NULL) {
    for (int i = 0; i < no->total; i++){
      percorreArvore(no->filhos[i]); //visita o filho a esquerda
    }

    percorreArvore(no->filhos[no->total]); //visita ultimo filho (direita)
  }
}

int pesquisaBinaria(Nob* no, int chave) {
  int inicio = 0, fim = no->total - 1, meio;		
  while (inicio <= fim) {	
    operacoes_b++;
    meio = (inicio + fim) / 2;
    if (no->chaves[meio] == chave) {	
    return meio; //encontrou	
    } else if (no->chaves[meio] > chave) {
      fim	= meio - 1;	
    } else {
      inicio = meio + 1;
    }
  }
  return inicio; //não encontrou	
}

int localizaChave(ArvoreB* arvore, int chave) {	
  Nob *no = arvore->raiz;
  
  while (no != NULL) {
    int i = pesquisaBinaria(no, chave);

    if (i < no->total && no->chaves[i] == chave) {
      return 1; //encontrou
    } else {
      no = no->filhos[i];
    }
  }

    return 0; //não encontrou	
}

Nob* localizaNo(ArvoreB* arvore, int chave) {	
  Nob *no = arvore->raiz;
  while (no != NULL) {
    operacoes_b++;
    int i = pesquisaBinaria(no, chave);
    operacoes_b++;
    if (no->filhos[i] == NULL)
      return no; //encontrou nó
    else
      operacoes_b++;
      no = no->filhos[i];
  }

  return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(Nob* no, Nob* novo, int chave) {
  int i = pesquisaBinaria(no, chave);

  for (int j = no->total - 1; j >= i; j--) {
    operacoes_b++;
    no->chaves[j + 1] = no->chaves[j];
    no->filhos[j + 2] = no->filhos[j + 1];
  }
  no->chaves[i] = chave;
  no->filhos[i + 1] = novo;
  no->total++;
}

int transbordo(ArvoreB* arvore, Nob* no) {
  operacoes_b++;
  return no->total > arvore->ordem * 2;
}

Nob* divideNo(ArvoreB* arvore, Nob* no) {
  int meio = no->total / 2;
  Nob* novo = criaNo(arvore);
  novo->pai = no->pai;
  for (int i = meio + 1; i < no->total; i++) {
    operacoes_b++;
    novo->filhos[novo->total] = no->filhos[i];
    novo->chaves[novo->total] = no->chaves[i];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
    
    novo->total++;
  }

  novo->filhos[novo->total] = no->filhos[no->total];
  if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
  no->total = meio;
  return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, Nob* no, Nob* novo, int chave) {
  adicionaChaveNo(no, novo, chave);
  operacoes_b++;
  if (transbordo(arvore, no)) {
    int promovido = no->chaves[arvore->ordem]; 
    Nob* novo = divideNo(arvore, no);

    if (no->pai == NULL) {
      operacoes_b++;
      Nob* pai = criaNo(arvore);
      pai->filhos[0] = no;
      adicionaChaveNo(pai, novo, promovido);
      
      no->pai = pai;
      novo->pai = pai;
      arvore->raiz = pai;
    } else
      adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
  }
}

int  adicionaChave(ArvoreB* arvore, int chave) {
  operacoes_b++;
  Nob* no = localizaNo(arvore, chave);

  adicionaChaveRecursivo(arvore, no, NULL, chave);
  return operacoes_b;
}

