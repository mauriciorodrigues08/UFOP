/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM 3

int main(int argc, char *argv[]) {
  int a[TAM][TAM], maior = -99999, menor = 99999;
  
  //preenchendo matriz
  printf("Digite os elementos da matriz: ");
  for (int i=0; i<TAM; i++)
    for (int j=0; j<TAM; j++) {
      scanf("%d", &a[i][j]);

      //verificando maior e menor
      if (a[i][j] > maior)
        maior = a[i][j];
      
      if (a[i][j] < menor)
        menor = a[i][j];
    }  

  //printando resultado
  printf("\nMaior elemento: %d", maior);
  printf("\nMenor elemento: %d\n", menor);

  return 0;
}