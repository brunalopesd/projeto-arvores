typedef struct no {
  struct no *pai;
  struct no *esquerda;
  struct no *direita;
  int valor;
} No;

typedef struct arvore {
  struct no *raiz;
} Arvore;


//add os metodos que vo precisar usar na main