#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Node {
    int coluna;
    int valor;
    struct Node* proximo;
    struct Node* anterior;
} Node;

typedef struct {
    int linhas;
    int colunas;
    Linha* linhasMatriz;
} Matriz;

Matriz criaMatriz(int linhas, int colunas);
void insereElemento(Matriz* A, int linha, int coluna, int valor);
void imprimeMatriz(Matriz A);
Matriz leMatriz();
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
void liberaMatriz(Matriz* A);

#endif
