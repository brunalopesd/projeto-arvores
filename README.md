

## Descricão
Trabalho realizado para disciplina de Projetos de Arquivos. Para analisar o desempenho de estruturas de arvores


### Alunos: 

- Bruna Lopes
- Victor Saramento

## Problema:

O objetivo deste trabalho consiste em analisar a complexidade algorítmica das operações de adição de nós e balanceamento em árvores:
1 - AVL
2 - rubro-negra 
3 - B. 

A análise deve ser realizada considerando a geração de um conjunto de dados (registros) com tamanho variando entre 1 e 1000. 

Os registros devem ser geradas prevendo o pior caso (chaves ordenadas crescente ou decrescente) e caso médio (chaves aleatórias). Para geração das chaves aleatórias, sugere-se o uso da função rand e srand em C considerando um tamanho de amostra de 10 conjuntos para validade estatística.

O resultado final do experimento deve ser exibido em DOIS gráficos de linha (um para o pior caso e outro para o caso médio), onde o eixo X representa o tamanho dos conjuntos de dados (1 a 1000) e o eixo Y representa o esforço computacional das operações (adição de chaves e balanceamento). Cada gráfico deve apresentar 3 linhas, as quais representam as respectivas operações para cada estrutura de dados avaliada.


## Executando 

```bash
gcc -Wall main.c arvoreAvl.c arvoreB.c rubro.c -o output
./output
```

## Plotando os graficos

Apos a execução, baixe os arquivos csv e gere os graficos via excel ou google sheets