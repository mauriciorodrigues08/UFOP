/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

// Escreva um programa que leia os elementos de um vetor (vet1) de inteiros, dado seu tamanho n. Em seguida, o programa irá separar os valores lidos em dois vetores, sendo um de valores pares, e um de valores ímpares.

#include <stdio.h>
#include <stdlib.h>

int main() {
  int *v, *vPares, *vImpares, n, qtdPares = 0, qtdImpares = 0;

  //recebendi valor de n
  printf("Digite o valore de n: ");
  scanf("%d", &n);

  //alocando vetores
  v = malloc(n * sizeof(int));
  vPares = malloc(n * sizeof(int));
  vImpares = malloc(n * sizeof(int));

  //recebendo valores
  printf("Digite os valores do vetor: ");
  for (int i=0; i<n; i++)
    scanf("%d", &v[i]);

  //verificando pares e ímpares
  for (int i=0; i<n; i++) {
    if (v[i] % 2 == 0) {
      vPares[i] = v[i];
      vImpares[i] = -99999;
      qtdPares++;
    }
    else {
      vPares[i] = -99999;
      vImpares[i] = v[i];
      qtdImpares++;
    }
  }

  //printando vetor de pares
  if (qtdPares > 0) {
    printf("\nVetor com os valores pares: [ ");
    for (int i=0; i<n; i++)
    if (vPares[i] != -99999)
      printf("%d ", vPares[i]);
    
    printf("]");
  }
  else printf("\nVetor com os valores pares: Vazio");

  //printando vetor de ímpares
  if (qtdImpares > 0) {
    printf("\nVetor com os valores ímpares: [ ");
    for (int i=0; i<n; i++)
      if (vImpares[i] != -99999)
        printf("%d ", vImpares[i]);
    
    printf("]");
  }
  else printf("\nVetor com os valores ímpares: Vazio");

  //liberando memórias alocadas
  free(v);
  free(vPares);
  free(vImpares);

  printf("\n");
  return 0;
}