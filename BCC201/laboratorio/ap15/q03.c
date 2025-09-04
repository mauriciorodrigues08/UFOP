/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <stdlib.h>

int** transposta(int **A, int m, int n);
int** criaMatriz(int m, int n);
void liberaMatriz(int** A, int m);

int main() {
    int **mat, **matTransposta, m, n;

    // recebendo dimensões e criando matriz
    printf("Digite o valor de m e n: ");
    scanf("%d%d", &m, &n);
    mat = criaMatriz(m, n);

    // recebendo valores
    printf("Digite a matriz:\n");
    for (int i = 0; i<m; i++)
        for (int j = 0; j<n; j++)
            scanf("%d", &mat[i][j]);

    // transposição da matriz
    matTransposta = transposta(mat, m, n);

    // printando resultado
    printf("Transposta:\n");
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++)
            printf("%d ", matTransposta[i][j]);
        printf("\n");
    }

    // liberando matrizes
    liberaMatriz(mat, m);
    liberaMatriz(matTransposta, n);

    return 0;
}

// Recebe uma matriz e seus índices e retorna a matriz transposta
int** transposta(int **A, int m, int n) {
    int **B = criaMatriz(n, m);

    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
            B[i][j] = A[j][i];

    return B;
}

// Aloca espaço para uma matriz m x n
int** criaMatriz(int m, int n) {
    int **mat = malloc(m * sizeof(int *));
    for (int i = 0; i<m; i++)
        mat[i] = malloc(n * sizeof(int));
    return mat;
}

// Libera o espaço utilizado por uma matriz
void liberaMatriz(int** A, int m) {
    for (int i = 0; i<m; i++)
        free(A[i]);
    free(A);
}
