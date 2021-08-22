
int operacoes_R;

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct nor {
    struct nor* pai;
    struct nor* esquerda;
    struct nor* direita;
    Cor cor;
    int valor;
} Nor;

typedef struct arvoreR {
    struct nor* raiz;
    struct nor* nulo; 
} ArvoreR;

Nor* adicionar_valor(ArvoreR* arvore, int valor);
ArvoreR* criar_rubro();