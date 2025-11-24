/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM 4

void printMatriz(int [TAM][TAM]);
void printPares(int [TAM][TAM]);

int main(int argc, char *argv[]) {
  int a[TAM][TAM], aux;
  
  //preenchendo matriz principal
  printf("Digite os valores da matriz: ");
  for (int i=0; i<TAM; i++)
  for (int j=0; j<TAM; j++) {
    do {
      scanf("%d", &aux);
      if (aux > 0)
        a[i][j] = aux;
    } while (aux <= 0);
  }
  
  //chamada das funções
  printMatriz(a);
  printf("\n");
  printPares(a);
  
  printf("\n");
  return 0;
}

//printa a matriz principal
void printMatriz(int a[TAM][TAM]) {
  for (int i=0; i<TAM; i++) {
    printf("\n");
    for (int j=0; j<TAM; j++)
      printf("%d ", a[i][j]);
  }
}

//printa as posições que contém valores pares
void printPares(int a[TAM][TAM]) {
  printf("\nPosições de valores pares:\n");
  for (int i=0; i<TAM; i++) 
    for (int j=0; j<TAM; j++)
      if (a[i][j] % 2 == 0)
        printf("%d %d\n", i, j);
  
  printf("\n");
}