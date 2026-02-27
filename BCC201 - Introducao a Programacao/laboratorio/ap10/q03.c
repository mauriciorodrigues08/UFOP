/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM_MAX 10

void leMatriz(int a[TAM_MAX][TAM_MAX], int m, int n);
void printMatriz(int a[TAM_MAX][TAM_MAX], int m, int n);
void multMatriz(int a[TAM_MAX][TAM_MAX], int b[TAM_MAX][TAM_MAX], int c[TAM_MAX][TAM_MAX], int m, int p, int q, int n);

int main(int argc, char *argv[]) {
  int m, n, p, q;
  int a[TAM_MAX][TAM_MAX], b[TAM_MAX][TAM_MAX], c[TAM_MAX][TAM_MAX];
  
  //recebendo e validando m, n, p, q
  do {
    printf("Entre com os valores de m, p, q, n: ");
    scanf("%d %d %d %d", &m, &p, &q, &n);
    if (m <= 0 || n <= 0 || p <= 0 || q <= 0 || m > TAM_MAX || n > TAM_MAX || p > TAM_MAX || q > TAM_MAX || p != q)
      printf("Valores inválidos!\n");
  } while (m <= 0 || n <= 0 || p <= 0 || q <= 0 || m > TAM_MAX || n > TAM_MAX || p > TAM_MAX || q > TAM_MAX || p != q);

  //preenchendo matrizes
  leMatriz(a, m, p);
  leMatriz(b, q, n);
  
  //multiplicando matrizes
  multMatriz(a, b, c, m, p, q, n);
  
  //printando matriz resultante
  printMatriz(c, m, n);
  printf("\n");
  
  return 0;
}

void leMatriz(int a[TAM_MAX][TAM_MAX], int m, int n) {
  printf("Entre com os elementos da matriz: ");
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      scanf("%d", &a[i][j]);
}

void multMatriz(int a[TAM_MAX][TAM_MAX], int b[TAM_MAX][TAM_MAX], int c[TAM_MAX][TAM_MAX], int m, int p, int q, int n) {
  int aux, i, j;
  
  for (i=0; i<m; i++) {
    for (j=0; j<n; j++) {
      //zerando auxiliar
      aux = 0;
      
      //calculado multiplicação
      for (int k=0; k<p; k++)
        aux += a[i][k] * b[k][j];

      //atribuindo valor do somatório para c[i][j]
      c[i][j] = aux;
    }
  }
}

void printMatriz(int a[TAM_MAX][TAM_MAX], int m, int n) {
  for (int i=0; i<m; i++) {
    printf("\n");
    for (int j=0; j<n; j++)
      printf("%d ", a[i][j]);
  }
}