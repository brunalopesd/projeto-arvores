#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h"

int operacoes_AVL;

int altura(No* no);
No* balanceamento(No* no);

void inicia_arvore(Arvore *arvore) {
    operacoes_AVL = 0;
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
    esquerda = altura(no->esquerda) + 1;
  }

  if (no->direita != NULL) {
    direita = altura(no->direita) + 1;
  }

  return esquerda > direita ? esquerda : direita; 
}

int fator_balanceamento(No* no) {
    int alt_esquerda = 0, alt_direita = 0;
    if (no->esquerda != NULL) {
        alt_esquerda = altura(no->esquerda) + 1;
    }
    if (no->direita != NULL) {
        alt_direita = altura(no->direita) + 1;
    }
    return alt_esquerda - alt_direita;
}

No* rotacao_simples_esq(No* no) {
    operacoes_AVL++;

    No *pai = no->pai;
    No *no_rotaciona = no->direita;
    No *filho = no_rotaciona->esquerda;
    
    no->pai = no_rotaciona;
    no_rotaciona->esquerda = no;
    if (!filho) {
        no->direita = NULL;
    } else {
        filho->pai = no;
        no->direita = filho;
    }
    no_rotaciona->pai = pai;
    if (pai && pai->esquerda == no) {
        pai->esquerda = no_rotaciona;
    } else if (pai) {
        pai->direita = no_rotaciona;
    }
    return no_rotaciona;
}

No* rotacao_simples_dir(No* no) {
    operacoes_AVL ++;

    No *pai = no->pai; 
    No *no_rotaciona = no->esquerda; 
    No *filho = no_rotaciona->direita;

    no->pai = no_rotaciona;
    no_rotaciona->direita = no;
    if (!filho) {
        no->esquerda = NULL;
    } else {
        filho->pai = no;
        no->esquerda = filho;
    }
    no_rotaciona->pai = pai;
    if (pai && pai->esquerda == no) {
        pai->esquerda = no_rotaciona;
    } else if (pai) {
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
    while (no != NULL) {
        operacoes_AVL++;
        int fator = fator_balanceamento(no);
        if (fator > 1) {
            if (fator_balanceamento(no->esquerda) > 0) {
                return rotacao_simples_dir(no);
            } else {
                return rotacao_dupla_dir(no);
            }
        } else if (fator < -1) {
            if (fator_balanceamento(no->direita) < 0) {
                return rotacao_simples_esq(no);
            } else {
                return rotacao_dupla_esq(no);
            }
        }
        no = no->pai;
    }
    return no;
}

int adiciona_no(Arvore *arvore, int valor) {
    operacoes_AVL++;
    No* no = malloc(sizeof(No));
    if (no == NULL)
        return 0;
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    if (arvore_vazia(arvore)) {
        no->pai = NULL;
        arvore->raiz = no;
        return operacoes_AVL;
    } else {       
        No *n = arvore->raiz;
        No *no_centro = NULL;
        do {
            operacoes_AVL++;
            if (n->valor == valor) {
                free(no);
            } else if (valor < n->valor) {
                if (!n->esquerda) {
                    no->pai = n;
                    n->esquerda = no;
                    no_centro = balanceamento(n->pai);
                    
                    if (no_centro && !no_centro->pai) {
                        arvore->raiz = no_centro;
                    }
                    return operacoes_AVL;
                } else {
                    n = n->esquerda;
                }
            } else {
                if (!n->direita) {
                    no->pai = n;
                    n->direita = no;
                    no_centro = balanceamento(n->pai);
                    if (no_centro && !no_centro->pai) {
                        arvore->raiz = no_centro;
                    }
                    return operacoes_AVL;
                } else {
                    n = n->direita;
                }
            }
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