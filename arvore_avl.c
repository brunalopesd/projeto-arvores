#include <stdlib.h>
#include <stdio.h>


typedef struct no {
  struct no *pai;
  struct no *esquerda;
  struct no *direita;
  int valor;
} No;

typedef struct arvore {
  struct no *raiz;
} Arvore;


void inicia_arvore(Arvore *arvore) {
  arvore->raiz = NULL;
}

int arvore_vazia(Arvore* arvore) {
	return (arvore->raiz == NULL);
}

void balanceamento(Arvore* arvore, No* no) {
    while (no != NULL) {
    int fator = fb(no);

    if (fator > 1) { //árvore mais pesada para esquerda
      //rotação para a direita
      if (fb(no->esquerda) > 0) {
        printf("RSD(%d)\n",no->valor);
        rotaca_simples_dir(arvore, no); //rotação simples a direita, pois o FB do filho tem sinal igual
      } else {
        printf("RDD(%d)\n",no->valor);
        rotacao_dupla_dir(arvore, no); //rotação dupla a direita, pois o FB do filho tem sinal diferente
      }
  } else if (fator < -1) { //árvore mais pesada para a direita
      //rotação para a esquerda
      if (fb(no->direita) < 0) {
        printf("RSE(%d)\n",no->valor);
        rotaca_simples_esq(arvore, no); //rotação simples a esquerda, pois o FB do filho tem sinal igual
      } else {
        printf("RDE(%d)\n",no->valor);
        rotaca_dupla_esq(arvore, no); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
      }
    }
    no = no->pai; 
  }
}

No* adicionar_no(No* no, int valor) {
  if (valor > no->valor) {
    if (no->direita == NULL) {
      printf("Adicionando %d\n",valor);
      No* novo = malloc(sizeof(No));
      novo->valor = valor;
      novo->pai = no;

      no->direita = novo;
  
      return novo;
    } else {
      return adicionarNo(no->direita, valor);
    }
  } else {
    if (no->esquerda == NULL) {
      printf("Adicionando %d\n",valor);
      No* novo = malloc(sizeof(No));
      novo->valor = valor;
      novo->pai = no;

      no->esquerda = novo;

      return novo;
      } else {
        return adicionarNo(no->esquerda, valor);
      }
  }
}

No* adicionar(Arvore* arvore, int valor) {
  if (arvore->raiz == NULL) {
    printf("Adicionando %d\n",valor);
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    
    arvore->raiz = novo;
  
    return novo;
  } else {
    No* no = adicionar_no(arvore->raiz, valor);
    balanceamento(arvore, no);
    
    return no;
  }
}

void remover_no(Arvore* arvore, No* no) {
 if (no->esquerda != NULL)
	 remover_no(arvore, no->esquerda);

 if (no->direita != NULL)
	 remover_no(arvore, no->direita);

 if (no->pai == NULL) { // raiz da arvore
	 arvore->raiz = NULL;
 } else {
 if (no->pai->esquerda == no)
	 no->pai->esquerda = NULL;
 else
	 no->pai->direita = NULL;
 }
 free(no);
}

void pre_order(No *no, void(*callback) (int)){
  if (no) {
    callback(no->valor);
    pre_order(no->esquerda, callback);
    pre_order(no->direita, callback);

  }
}

void in_order(No *no, void(*callback) (int)){
  if (no) {
    in_order(no->esquerda, callback);
    callback(no->valor);
    in_order(no->direita, callback);

  }
}

void pos_order(No *no, void (*callback) (int)) {
  if (no) {
    pos_order(no->esquerda, callback);
    pos_order(no->direita, callback);
    callback(no->valor);
  }
}

int fator_balanceamento(No* no) {
  // operacoes_AVL += 2;
  int altura_esquerda = 0, altura_direita = 0;
  operacoes_AVL++;
  if (no->esquerda != NULL) {
    // operacoes_AVL++;
    altura_esquerda = altura(no->esquerda) + 1;
  }
  operacoes_AVL++;
  if (no->direita) {
    // operacoes_AVL++;
    altura_direita = altura(no->direita) + 1;
  }
  // operacoes_AVL++;
  return altura_esquerda - altura_direita;
}

int altura(No* no){
  int esquerda = 0,direita = 0;

  if (no->esquerda != NULL) {
    esquerda = altura(no->esquerda) + 1;
  }

  if (no->direita != NULL) {
    direita = altura(no->direita) + 1;
  }

  return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

No* rotaca_simples_esq(Arvore* arvore, No* no) {
  No* pai = no->pai;
  No* direita = no->direita;

  no->direita = direita->esquerda;
  no->pai = direita;

  direita->esquerda = no;
  direita->pai = pai;

  if (pai == NULL) {
    arvore->raiz = direita;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = direita;
    } else {
      pai->direita = direita;
    }
  }

  return direita;
}

No* rotaca_simples_dir(Arvore* arvore, No* no) {
  No* pai = no->pai;
  No* esquerda = no->esquerda;

  no->esquerda = esquerda->direita;
  no->pai = esquerda;

  esquerda->direita = no;
  esquerda->pai = pai;

  if (pai == NULL) {
    arvore->raiz = esquerda;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = esquerda;
    } else {
      pai->direita = esquerda;
    }
  }

  return esquerda;
}

No* rotaca_dupla_esq(Arvore* arvore, No* no) {
  no->direita = rsd(arvore, no->direita);
  return rse(arvore, no);
}

No* rotacao_dupla_dir(Arvore* arvore, No* no) {
  no->esquerda = rse(arvore, no->esquerda);
  return rsd(arvore, no);
}



