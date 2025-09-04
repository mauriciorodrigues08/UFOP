/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 100000

int main() {
  int n, a[TAM], arr[500];
  
  //recebendo valor de n
  do {  
    printf("Entre com um número inteiro <= 500: ");
    scanf("%d", &n);
  } while(n > 500 || n < 1);
  
  //sorteando valores
  srand(5);
  for(int i=0; i<TAM; i++) {
    arr[i] =  (rand() % n) + 1;
  }
  
  //inicializando vetor resultado com 0
  for (int i=0; i<n; i++)
    a[i] = 0;

  //verificando quantidade de vezes de cada termo
  for (int i=1; i<=n; i++)
    for (int j=0; j<TAM; j++)
      if (arr[j] == i)
        a[i]++;


  //printando resultado
  for (int i=1; i<=n; i++)
    printf("\nA[%d] = %d", i, a[i]);

  printf("\n");
  return 0;
}