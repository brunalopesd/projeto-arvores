#include <stdlib.h>
#include <stdio.h>
#include "rubro.h"


Nor* criarNo(ArvoreR*, Nor*, int);
void balancear(ArvoreR*, Nor*);
void rotacionarEsquerda(ArvoreR*, Nor*);
void rotacionarDireita(ArvoreR*, Nor*);

ArvoreR* criar_rubro() {
  ArvoreR *arvore = malloc(sizeof(ArvoreR));
  arvore->nulo = NULL;
  arvore->raiz = NULL;

  arvore->nulo = criarNo(arvore, NULL, 0);
  arvore->nulo->cor = Preto;

  return arvore;
}

int vazia(ArvoreR* arvore) {
  return arvore->raiz == NULL;
}

Nor* criarNo(ArvoreR* arvore, Nor* pai, int valor) {
  operacoes_R++;
  Nor* no = malloc(sizeof(Nor));
  operacoes_R++;


  no->pai = pai;    
  no->valor = valor;
  no->direita = arvore->nulo;
  no->esquerda = arvore->nulo;

  operacoes_R+=4;

  return no;
}

Nor* adicionarNo(ArvoreR* arvore, Nor* no, int valor) {
  operacoes_R++;
  if (valor > no->valor) {
    operacoes_R++;

    if (no->direita == arvore->nulo) {
      operacoes_R++;
      no->direita = criarNo(arvore, no, valor);     
      no->direita->cor = Vermelho;
      operacoes_R++;     
      
      return no->direita;
    } else {
      operacoes_R++;
      return adicionarNo(arvore, no->direita, valor);
    }
  } else {
    if (no->esquerda == arvore->nulo) {
      operacoes_R++;
      no->esquerda = criarNo(arvore, no, valor);
      no->esquerda->cor = Vermelho;
      operacoes_R++;
      
      return no->esquerda;
    } else {
      operacoes_R++;
      return adicionarNo(arvore, no->esquerda, valor);
    }
  }
}

Nor* adicionar_valor(ArvoreR* arvore, int valor) { // eh publico
  operacoes_R = 0;
  if (vazia(arvore)) {
    operacoes_R++;
    arvore->raiz = criarNo(arvore, arvore->nulo, valor);
    arvore->raiz->cor = Preto;
    operacoes_R++;
      
    return arvore->raiz;
  } else {
    operacoes_R++;
    Nor* no = adicionarNo(arvore, arvore->raiz, valor);
    balancear(arvore, no);
    
    return no;
  }
}

Nor* localizar(ArvoreR* arvore, int valor) {
  if (!vazia(arvore)) {
    Nor* no = arvore->raiz;

    while (no != arvore->nulo) {
      if (no->valor == valor) {
        return no;
      } else {
        no = valor < no->valor ? no->esquerda : no->direita;
      }
    }
  }
  return NULL;
}

void in_order(ArvoreR* arvore, Nor* no, void (*callback)(int)) {
  if (no != arvore->nulo) {
      
    in_order(arvore, no->esquerda,callback);
    callback(no->valor);
    in_order(arvore, no->direita,callback);
  }
}

void pre_order(ArvoreR* arvore, Nor* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        pre_order(arvore, no->esquerda,callback);
        pre_order(arvore, no->direita,callback);
    }
}

void pos_order(ArvoreR* arvore, Nor* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        pos_order(arvore, no->esquerda,callback);
        pos_order(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void balancear(ArvoreR* arvore, Nor* no) {
  operacoes_R++;
  while (no->pai->cor == Vermelho) {
    if (no->pai == no->pai->pai->esquerda) {
      operacoes_R++;
      Nor *tio = no->pai->pai->direita;
      
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 
        operacoes_R+=2;

        no->pai->pai->cor = Vermelho; //Caso 1
        no = no->pai->pai; //Caso 1
        operacoes_R+=2;
      } else {
        if (no == no->pai->direita) {
          operacoes_R++;
          no = no->pai; //Caso 2
          rotacionarEsquerda(arvore, no); //Caso 2
        } else {
          no->pai->cor = Preto; 
          operacoes_R++;
          no->pai->pai->cor = Vermelho; //Caso 3
          operacoes_R++;
          rotacionarDireita(arvore, no->pai->pai); //Caso 3
        }
      }
    } else {
      operacoes_R++;
      Nor *tio = no->pai->pai->esquerda;
      
      if (tio->cor == Vermelho) {
        tio->cor = Preto; //Caso 1
        no->pai->cor = Preto; 
        operacoes_R++;

        no->pai->pai->cor = Vermelho; //Caso 1
        operacoes_R++;
        no = no->pai->pai; //Caso 1
      } else {
        operacoes_R++;
        if (no == no->pai->esquerda) {
          no = no->pai; //Caso 2
          operacoes_R++;
          rotacionarDireita(arvore, no); //Caso 2
        } else {
          no->pai->cor = Preto; 
          operacoes_R++;
          no->pai->pai->cor = Vermelho; //Caso 3
          operacoes_R++;
          rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
        }
      }
    }
  }
  arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(ArvoreR* arvore, Nor* no) {
  operacoes_R++;
    Nor* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
      direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
      arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
      no->pai->esquerda = direita;
    } else {
      no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(ArvoreR* arvore, Nor* no) {
  operacoes_R++;
    Nor* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    if (esquerda->direita != arvore->nulo) {
      esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
      arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
      no->pai->esquerda = esquerda;
    } else {
      no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

