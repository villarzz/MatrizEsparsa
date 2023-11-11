#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da matriz
typedef struct Node {
    int coluna;
    int valor;
    struct Node* proximo;
    struct Node* anterior;
} Node;

// Estrutura para representar uma linha da matriz
typedef struct {
    Node* cabeca; // Ponteiro para o início da lista
} Linha;

// Estrutura para representar a matriz
typedef struct {
    int linhas;
    int colunas;
    Linha* linhasMatriz;
} Matriz;

// Função para criar uma nova matriz
Matriz criaMatriz(int linhas, int colunas) {
    Matriz novaMatriz;
    novaMatriz.linhas = linhas;
    novaMatriz.colunas = colunas;

    novaMatriz.linhasMatriz = (Linha*)malloc(linhas * sizeof(Linha));

    for (int i = 0; i < linhas; i++) {
        novaMatriz.linhasMatriz[i].cabeca = NULL;
    }

    return novaMatriz;
}

// Função para inserir um elemento na matriz
void insereElemento(Matriz* A, int linha, int coluna, int valor) {
    if (linha < 0 || linha >= A->linhas || coluna < 0 || coluna >= A->colunas) {
        printf("Erro: Índices fora dos limites.\n");
        return;
    }

    Node* novoElemento = (Node*)malloc(sizeof(Node));
    novoElemento->coluna = coluna;
    novoElemento->valor = valor;
    novoElemento->proximo = NULL;

    if (A->linhasMatriz[linha].cabeca == NULL) {
        // Se a linha estiver vazia, adiciona o primeiro elemento
        A->linhasMatriz[linha].cabeca = novoElemento;
        novoElemento->anterior = NULL;
    } else {
        // Se a linha já tiver elementos, adiciona no final
        Node* atual = A->linhasMatriz[linha].cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoElemento;
        novoElemento->anterior = atual;
    }
}

// Função para imprimir a matriz
void imprimeMatriz(Matriz A) {
    for (int i = 0; i < A.linhas; i++) {
        printf("Linha %d: ", i);

        Node* atual = A.linhasMatriz[i].cabeca;
        while (atual != NULL) {
            printf("(%d, %d)=%.2f ", i, atual->coluna, (float)atual->valor);
            atual = atual->proximo;
        }

        printf("\n");
    }
}

// Função para ler a matriz de um arquivo
Matriz leMatriz() {
    int linhas, colunas;
    printf("Informe o número de linhas e colunas da matriz: ");
    scanf("%d %d", &linhas, &colunas);

    Matriz novaMatriz = criaMatriz(linhas, colunas);

    int i, j;
    float valor;
    printf("Informe os elementos diferentes de zero da matriz (i, j, valor):\n");
    while (scanf("%d %d %f", &i, &j, &valor) == 3) {
        insereElemento(&novaMatriz, i, j, valor);
    }

    return novaMatriz;
}

// Função para somar duas matrizes
Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.linhas != B.linhas || A.colunas != B.colunas) {
        printf("Erro: As matrizes não têm o mesmo tamanho.\n");
        exit(1);
    }

    Matriz resultado = criaMatriz(A.linhas, A.colunas);

    for (int i = 0; i < A.linhas; i++) {
        Node* atualA = A.linhasMatriz[i].cabeca;
        Node* atualB = B.linhasMatriz[i].cabeca;

        while (atualA != NULL || atualB != NULL) {
            if (atualA == NULL) {
                insereElemento(&resultado, i, atualB->coluna, atualB->valor);
                atualB = atualB->proximo;
            } else if (atualB == NULL) {
                insereElemento(&resultado, i, atualA->coluna, atualA->valor);
                atualA = atualA->proximo;
            } else {
                if (atualA->coluna == atualB->coluna) {
                    insereElemento(&resultado, i, atualA->coluna, atualA->valor + atualB->valor);
                    atualA = atualA->proximo;
                    atualB = atualB->proximo;
                } else if (atualA->coluna < atualB->coluna) {
                    insereElemento(&resultado, i, atualA->coluna, atualA->valor);
                    atualA = atualA->proximo;
                } else {
                    insereElemento(&resultado, i, atualB->coluna, atualB->valor);
                    atualB = atualB->proximo;
                }
            }
        }
    }

    return resultado;
}

// Função para multiplicar duas matrizes
Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.colunas != B.linhas) {
        printf("Erro: Número de colunas de A não é igual ao número de linhas de B.\n");
        exit(1);
    }

    Matriz resultado = criaMatriz(A.linhas, B.colunas);

    for (int i = 0; i < A.linhas; i++) {
        for (int j = 0; j < B.colunas; j++) {
            float valor = 0.0;

            for (int k = 0; k < A.colunas; k++) {
                Node* atualA = A.linhasMatriz[i].cabeca;
                Node* atualB = B.linhasMatriz[k].cabeca;

                while (atualA != NULL && atualB != NULL) {
                    if (atualA->coluna == k && atualB->coluna == j) {
                        valor += atualA->valor * atualB->valor;
                        atualA = atualA->proximo;
                        atualB = atualB->proximo;
                    } else if (atualA->coluna < k) {
                        atualA = atualA->proximo;
                    } else if (atualB->coluna < j) {
                        atualB = atualB->proximo;
                    } else {
                        atualA = atualA->proximo;
                        atualB = atualB->proximo;
                    }
                }
            }

            if (valor != 0.0) {
                insereElemento(&resultado, i, j, valor);
            }
        }
    }

    return resultado;
}


// Função para liberar a memória alocada para a matriz
void liberaMatriz(Matriz* A) {
    for (int i = 0; i < A->linhas; i++) {
        Node* atual = A->linhasMatriz[i].cabeca;
        while (atual != NULL) {
            Node* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(A->linhasMatriz);
    A->linhas = 0;
    A->colunas = 0;
}

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
