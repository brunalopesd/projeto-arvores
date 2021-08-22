#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h"

int operacoes_AVL;

int altura(No* no);
No* balanceamento(No* no);

void inicia_arvore(Arvore *arvore) {
    arvore->raiz = NULL;
}

int arvore_vazia(Arvore *arvore) {
    return (arvore->raiz == NULL);
}

void remover_no(Arvore *arvore, No *no) {
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

void in_Order(No* no, void (*callback) (int)) {
    if (no) {
        in_Order(no->esquerda, callback);
        callback(no->valor);
        in_Order(no->direita, callback);
    }
}

void pre_Order(No* no, void (*callback) (int)) {
    if (no) {
        callback(no->valor);
        pre_Order(no->esquerda, callback);
        pre_Order(no->direita, callback);
    }
}

void pos_Order(No* no, void (*callback) (int)) {
    if (no) {
        pos_Order(no->esquerda, callback);
        pos_Order(no->direita, callback);
        callback(no->valor);
    }
}

int altura(No* no) {
  int esquerda = 0,direita = 0;

  if (no->esquerda != NULL) {
    operacoes_AVL++;
    esquerda = altura(no->esquerda) + 1;
  }

  if (no->direita != NULL) {
    operacoes_AVL++;
    direita = altura(no->direita) + 1;
  }

  return esquerda > direita ? esquerda : direita; 
}

int fator_balanceamento(No* no) {
    operacoes_AVL += 2;
    int alt_esquerda = 0, alt_direita = 0; //mudar nome 
    operacoes_AVL++;
    if (no->esquerda != NULL) {
        operacoes_AVL++;
        alt_esquerda = altura(no->esquerda) + 1;
    }
    operacoes_AVL++;
    if (no->direita != NULL) {
        operacoes_AVL++;
        alt_direita = altura(no->direita) + 1;
    }
    operacoes_AVL++;
    return alt_esquerda - alt_direita;
}

No* rotacao_simples_esq(No* no) {
    
    No *pai = no->pai;
    No *no_rotaciona = no->direita;
    No *filho = no_rotaciona->esquerda;

    operacoes_AVL++;
    no->pai = no_rotaciona;
    operacoes_AVL++;
    no_rotaciona->esquerda = no;
    operacoes_AVL++;
    if (!filho) {
        operacoes_AVL++;
        no->direita = NULL;
    } else {
        operacoes_AVL++;
        filho->pai = no;
        operacoes_AVL++;
        no->direita = filho;
    }
    operacoes_AVL++;
    no_rotaciona->pai = pai;
    operacoes_AVL += 2;
    if (pai && pai->esquerda == no) {
        operacoes_AVL++;
        pai->esquerda = no_rotaciona;
    } else if (pai) {
        operacoes_AVL += 2;
        pai->direita = no_rotaciona;
    }
    return no_rotaciona;
}

No* rotacao_simples_dir(No* no) {
    operacoes_AVL += 3;
    No *pai = no->pai; 
    No *no_rotaciona = no->esquerda; 
    No *filho = no_rotaciona->direita;

    operacoes_AVL++;
    no->pai = no_rotaciona;
    operacoes_AVL++;
    no_rotaciona->direita = no;
    operacoes_AVL++;
    if (!filho) {
        operacoes_AVL++;
        no->esquerda = NULL;
    } else {
        operacoes_AVL++;
        filho->pai = no;
        operacoes_AVL++;
        no->esquerda = filho;
    }
    operacoes_AVL++;
    no_rotaciona->pai = pai;
    operacoes_AVL += 2;
    if (pai && pai->esquerda == no) {
        operacoes_AVL++;
        pai->esquerda = no_rotaciona;
    } else if (pai) {
        operacoes_AVL += 2;
        pai->direita = no_rotaciona;
    }
    return no_rotaciona;
}

No* rotacao_dupla_esq(No* no) {
    operacoes_AVL++;
    no->direita = rotacao_simples_dir(no->direita);
    return rotacao_simples_esq(no);
}

No* rotacao_dupla_dir(No* no) {
    operacoes_AVL++;
    no->esquerda = rotacao_simples_esq(no->esquerda);
    return rotacao_simples_dir(no);
}

No* balanceamento(No* no) {
    operacoes_AVL++;
    while (no != NULL) {
        operacoes_AVL++;
        int fator = fator_balanceamento(no);
        operacoes_AVL++;
        if (fator > 1) {
            operacoes_AVL++;
            operacoes_AVL++;
            if (fator_balanceamento(no->esquerda) > 0) {
                return rotacao_simples_dir(no);
            } else {
                return rotacao_dupla_dir(no);
            }
        } else if (fator < -1) {
            operacoes_AVL += 2;
            operacoes_AVL++;
            if (fator_balanceamento(no->direita) < 0) {
                return rotacao_simples_esq(no);
            } else {
                return rotacao_dupla_esq(no);
            }
        }
        operacoes_AVL++;
        no = no->pai;
    }
    return no;
}

int adiciona_no(Arvore *arvore, int valor) {
    operacoes_AVL = 0;
    operacoes_AVL += 3;
    No* no = malloc(sizeof(No));
    operacoes_AVL++;
    if (no == NULL)
        return 0;
    operacoes_AVL++;
    no->valor = valor;
    operacoes_AVL++;
    no->esquerda = NULL;
    operacoes_AVL++;
    no->direita = NULL;
    operacoes_AVL++;
    if (arvore_vazia(arvore)) {
        operacoes_AVL++;
        no->pai = NULL;
        operacoes_AVL++;
        arvore->raiz = no;
        return operacoes_AVL;
    } else {
        operacoes_AVL += 2;
       
        No *n = arvore->raiz;
        No *no_centro = NULL;
        do {
            operacoes_AVL++;
            if (n->valor == valor) {
                free(no);
            } else if (valor < n->valor) {
                operacoes_AVL += 2;
                if (!n->esquerda) {
                    operacoes_AVL++;
                    no->pai = n;
                    operacoes_AVL++;
                    n->esquerda = no;
                    operacoes_AVL++;
                    no_centro = balanceamento(n->pai);
                    operacoes_AVL++;
                    if (no_centro && !no_centro->pai) {
                        operacoes_AVL++;
                        arvore->raiz = no_centro;
                    }
                    return operacoes_AVL;
                } else {
                    operacoes_AVL++;
                    n = n->esquerda;
                }
            } else {
                operacoes_AVL++;
                if (!n->direita) {
                    operacoes_AVL++;
                    no->pai = n;
                    operacoes_AVL++;
                    n->direita = no;
                    operacoes_AVL++;
                    no_centro = balanceamento(n->pai);
                    operacoes_AVL++;
                    if (no_centro && !no_centro->pai) {
                        operacoes_AVL++;
                        arvore->raiz = no_centro;
                    }
                    return operacoes_AVL;
                } else {
                    operacoes_AVL++;
                    n = n->direita;
                }
            }
        operacoes_AVL++;
        } while (1);
    }        
}

void limpa_arvore(Arvore *arvore, No *no) {
    if (no) {
        limpa_arvore(arvore, no->esquerda);
        limpa_arvore(arvore, no->direita);
        remover_no(arvore, no);
    }
}