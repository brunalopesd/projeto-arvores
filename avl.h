typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

int contador_avl;

Arvore* criar();
No* adicionar(Arvore* arvore, int valor);
void limpa_arvore(Arvore *arvore, No *no);