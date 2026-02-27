/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#define TAM 15

int main() {
  float kwh[TAM], maiorCons = -99999, menorCons = 99999, consMedio = 0;

  //recebendo e analisando dados
  for (int i=0; i<TAM; i++) {
    printf("Digite o consumo da %d residência: ", i+1);
    scanf("%f", &kwh[i]);
  }
  
  for (int i=0; i<TAM; i++) {
    consMedio += kwh[i];

    if (kwh[i] > maiorCons)
      maiorCons = kwh[i];
      
    if (kwh[i] < menorCons)
      menorCons = kwh[i];
  }

  consMedio /= TAM;

  //imprimindo resultado
  printf("\nConsumo médio: %.2f Kwh\n", consMedio);
  printf("Maior consumo: %.2f Kwm\n", maiorCons);
  printf("Menor consumo: %.2f Kwm\n", menorCons);

  return 0;
}