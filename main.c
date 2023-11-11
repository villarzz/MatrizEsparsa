#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Teste 1: Criação de Matriz
    printf("Teste 1: Criação de Matriz\n");
    Matriz A = criaMatriz(3, 3);
    printf("Matriz A criada:\n");
    imprimeMatriz(A);

    // Teste 2: Inserção de Elementos
    printf("\nTeste 2: Inserção de Elementos\n");
    insereElemento(&A, 0, 1, 10);
    insereElemento(&A, 1, 2, 20);
    insereElemento(&A, 2, 0, 30);
    printf("Matriz A após a inserção de elementos:\n");
    imprimeMatriz(A);

    // Teste 3: Leitura de Matriz
    printf("\nTeste 3: Leitura de Matriz\n");
    Matriz B = leMatriz();
    printf("\nMatriz B lida do arquivo:\n");
    imprimeMatriz(B);

    // Teste 4: Soma de Matrizes
    printf("\nTeste 4: Soma de Matrizes\n");
    Matriz C = somaMatrizes(A, B);
    printf("Matriz C (soma de A e B):\n");
    imprimeMatriz(C);

    // Teste 5: Multiplicação de Matrizes
    printf("\nTeste 5: Multiplicação de Matrizes\n");
    Matriz D = multiplicaMatrizes(A, B);
    printf("Matriz D (produto de A e B):\n");
    imprimeMatriz(D);

    // Teste 6: Liberação de Memória
    printf("\nTeste 6: Liberação de Memória\n");
    liberaMatriz(&A);
    liberaMatriz(&B);
    liberaMatriz(&C);
    liberaMatriz(&D);
    printf("Memória liberada com sucesso.\n");

    return 0;
}
