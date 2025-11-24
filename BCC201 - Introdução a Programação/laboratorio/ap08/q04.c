/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM 30

int main() {
  float temp[TAM], med = 0;
  int tempAcima = 0, tempAbaixo = 0;

  //recebendo valores
  printf("Entre com as temperaturas: ");
  for (int i=0; i<TAM; i++) {
    scanf("%f", &temp[i]);
    med += temp[i];
  }

  //calculando media
  med /= TAM;

  for (int i=0; i<TAM; i++) {
    if (temp[i] > med)
      tempAcima++;
    else if (temp[i] < med)
      tempAbaixo++;
  }

  //printando resultado
  printf("\nAcima: %d\nAbaixo: %d\n", tempAcima, tempAbaixo);

  return 0;
}