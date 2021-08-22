
int operacoes_AVL;

 
typedef struct no {
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
    int valor;
} No;

typedef struct arvore {
    struct no *raiz;
} Arvore;

int adiciona_no(Arvore *arvore, int valor);

void inicia_arvore(Arvore* arvore);
int arvore_vazia(Arvore* arvore);
int adiciona_no(Arvore* arvore, int valor);
void remover_no(Arvore* arvore, No* no);
void in_Order(No* no, void (*callback) (int));
void pre_Order(No* no, void (*callback) (int));
void pos_Order(No* no, void (*callback) (int));
void limpa_arvore(Arvore* arvore, No* no);
