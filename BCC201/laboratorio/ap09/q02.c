/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM_MAX 100

int main() {
  int n, vet[TAM_MAX], acima[TAM_MAX], abaixo[TAM_MAX];
  float media = 0;

  //recebendo tamanho do vetor
  do {
    printf("Digite a quantidade de valores <= 100: ");
    scanf("%d", &n);
  } while (n > TAM_MAX);
  
  //adicionando valores ao vetor e calculando media
  printf("Digite os elementos do vetor: ");
  for (int i=0; i<n; i++) {
    scanf("%d", &vet[i]);
    media += vet[i];
  }
  media /= n;

  //verificar maiores e menores que a media
  for (int i=0; i<n; i++) {
    if (vet[i] >= media) {
      acima[i] = vet[i];
      abaixo[i] = 99999;
    }else if (vet[i] < media) {
      abaixo[i] = vet[i];
      acima[i] = 99999;
    }
  }

  //imprimir resultado
  //media
  printf("\nMédia: %.1f", media);

  //menores
  printf("\nValores abaixo da média: ");
  for (int i=0; i<n; i++) 
    if (abaixo[i] != 99999)
      printf("%d ", abaixo[i]);

  //maiores
  printf("\nValores acima da média: ");
  for (int i=0; i<n; i++) 
    if (acima[i] != 99999)
      printf("%d ", acima[i]);

  printf("\n");
  return 0;
}