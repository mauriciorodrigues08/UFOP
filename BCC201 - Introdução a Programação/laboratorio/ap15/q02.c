/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

//Escreva um programa para ler uma matriz de inteiros (Am×n), um valor digitado pelo usuário e verifique se esse valor encontra-se na matriz. O programa deve ler os índices m, n, a matriz A e um valor a ser procurado. O programa deve imprimir se encontrou o valor na matriz ("Valor encontrado!") ou não ("Valor não encontrado!").

#include <stdio.h>
#include <stdlib.h>

int main() {
  int **mat, m, n, valor, encontrado = 0;

  //recebendo valor de m e n
  printf("Digite o valor de m e n: ");
  scanf("%d%d", &m, &n);

  //alocando matriz
  mat = malloc(m * sizeof(int*));
  for (int i=0; i<m; i++)
    mat[i] = malloc(n * sizeof(int));

  //preenchendo matriz
  printf("Digite a matriz:\n");
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      scanf("%d", &mat[i][j]);

  //recebendo número a ser procurado
  printf("\nDigite o valor a ser procurado: ");
  scanf("%d", &valor);

  //procurando valor
  int i = 0, j=0;
  while (i != m) {
    while (j != n) {
      if (mat[i][j] == valor) {
        encontrado = 1;
        break;
      }
      else j++;
    }
   
    if (encontrado == 1) {
      printf("\nValor encontrado!\n");
      break;
    }
    else {
      j = 0;
      i++;
    }
  }

  if (!encontrado) printf("\nValor não encontrado!\n");

  //liberando memória alocada
  for (int i=0; i<m; i++)
    free(mat[i]);
  free(mat);

  printf("\n");
  return 0;
}