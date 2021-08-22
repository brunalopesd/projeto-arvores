
int operacoes_b;

typedef struct nob {
    int total;
    int* chaves;
    struct nob** filhos;
    struct nob* pai; 
} Nob;

typedef struct arvoreB {
  Nob* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criaArvore(int);
Nob* criaNo(ArvoreB*);
void percorreArvore(Nob*);
int pesquisaBinaria(Nob*, int);
int localizaChave(ArvoreB*, int);
Nob* localizaNo(ArvoreB*, int);
void adicionaChaveNo(Nob*, Nob*, int);
int transbordo(ArvoreB*,Nob*);
Nob* divideNo(ArvoreB*, Nob*);
void adicionaChaveRecursivo(ArvoreB*, Nob*, Nob*, int);
int  adicionaChave(ArvoreB* arvore, int chave);