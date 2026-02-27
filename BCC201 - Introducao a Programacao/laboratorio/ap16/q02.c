/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <stdlib.h>

int** matAlloc(int m, int n);
void matFree(int **mat, int m);
int verificaQuadradoMagico(int **mat, int n);

int main() {
  int n; //índice da matriz
  int **mat, res;

  //recebendo indices da matriz
  do {
    printf("\nDigite o valor de n: ");
    scanf("%d", &n);
  } while (n < 1);

  //alocando memória para a matriz
  mat = matAlloc(n, n);

  //recebendo valores da matriz
  printf("\nDigite os valores da matriz n x n:\n");
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      scanf("%d", &mat[i][j]);

  //verificando se é quadrado mágico
  res = verificaQuadradoMagico(mat, n);

  (res == 1) ? printf("\nEsta matriz é um quadrado mágico!\n") : printf("\nEsta matriz NÃO é um quadrado mágico!\n");

  return 0;
}

int** matAlloc(int m, int n) {
  int **mat = malloc(m * sizeof(int *));

  for (int i=0; i<m; i++)
    mat[i] = malloc(n * sizeof(int));
    
  return mat;
}

void matFree(int **mat, int m) {
  for (int i=0; i<m; i++)
    free(mat[i]);

  free(mat);
}

int verificaQuadradoMagico(int **mat, int n) {
  int soma = 0, aux = 0;

  //verifica se possui dois números iguais
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      for (int k=i+1; k<n; k++)
        for (int l=j+1; l<n; l++)
          if (mat[i][j] == mat[k][l])
            return 0;

  //verifica linhas
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++)
      aux += mat[i][j];
    
    if (i == 0)
      soma = aux;
    else if (aux != soma)
      return 0;
    
    aux = 0;
  }
    
  //verifica colunas
  aux = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++)
      aux += mat[j][i];
    
    if (aux != soma)
      return 0;

    aux = 0;
  }

  //verifica diagonal principal
  aux = 0;
  for (int i=0; i<n; i++)
    aux += mat[i][i];

  if (aux != soma)
    return 0;

  //verifica diagonal secundária
  aux = 0;
  for (int j=0; j<n; j++)
    aux += mat[n-1-j][j];
  
  if (aux != soma)
    return 0;

  //caso não encontre nenhum erro, retorna 1
  return 1;
}