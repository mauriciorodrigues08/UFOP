/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

void converterLiquidos(float litros, float *oz, float *gallons);

int main() {
  float litros, oz, gallons;
  
  printf("\nDigite o total em litros: ");
  scanf("%f", &litros);
  
  converterLiquidos(litros, &oz, &gallons);
  
  printf("\nTotal em oz: %.2f\nTotal em gallons: %.2f\n", oz, gallons);
  
  return 0;
}

void converterLiquidos(float litros, float *oz, float *gallons) {
  *oz = litros * 33.814;
  *gallons = litros * 0.264172;
}
