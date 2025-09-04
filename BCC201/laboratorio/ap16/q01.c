/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <stdlib.h>

int multiplicaMatrizes(int ***R, int **A, int n, int m, int **B, int p, int q);
int **alocaMatriz(int n, int m);
void matFree(int **mat, int m);

int main() {
  int n, m, p, q; //indices
  int **A, **B, **R; //matrizes 
  int res; //resultado da multiplicação
  
  //recebendo índices da matriz A
  printf("\nDigite os tamanhos da matriz A: ");
  scanf("%d %d", &n, &m);
  
  //alocando memória para a matriz A
  A = alocaMatriz(n, m);
  
  //recebendo dados da matriz A
  printf("Digite os dados da matriz A:\n");
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      scanf("%d", &A[i][j]);
  
  //recebendo índices da matriz B
  printf("\nDigite os tamanhos da matriz B: ");
  scanf("%d %d", &p, &q);

  //alocando memória para B
  B = alocaMatriz(p, q);

  //recebendo os valores de B
  printf("Digite os dados da matriz B:\n");
  for (int i=0; i<p; i++)
    for (int j=0; j<q; j++)
      scanf("%d", &B[i][j]);

  //multiplicando matrizes
  res = multiplicaMatrizes(&R, A, n, m, B, p, q);

  if (res == 0) {
    printf("\nNão é possível multiplicar as matrizes A e B.\n");
  }
  else {
    printf("\nResultado de A x B:\n");
    for (int i=0; i<n; i++) {
      for (int j=0; j<q; j++) {
        printf("%d ", R[i][j]);
      }
      printf("\n");
    }
    matFree(R, n);
  }
  
  matFree(A, n);
  matFree(B, p);

  printf("\n");
  return 0;
}

int** alocaMatriz(int m, int n) {
  int **mat = malloc(m * sizeof(int *));
    
  for (int i = 0; i<m; i++)
    mat[i] = malloc(n * sizeof(int));
    
  return mat;
}

void matFree(int **mat, int m) {
  for (int i=0; i<m; i++)
    free(mat[i]);

  free(mat);
}

int multiplicaMatrizes(int ***R, int **A, int n, int m, int **B, int p, int q) {
  if (m != p)
    return 0;
  
  //alocando matriz resultante
  *R = alocaMatriz(n, q);

  //zerando matriz
  for (int i=0; i<n; i++)
    for (int j=0; j<q; j++)
      (*R)[i][j] = 0;

  //multiplicando valores
  int aux;
  for (int i=0; i<n; i++) {
    for (int j=0; j<q; j++) {
      //zera auxiliar
      aux = 0;
      
      //calcula multiplicação
      for (int k=0; k<p; k++)
        aux += A[i][k] * B[k][j];

      //atribui valor do somatório para R[i][j]
      (*R)[i][j] = aux;
    }
  }

  return 1;
}