/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <math.h>

float calculaArea(float);

int main() {
  float l, area;
  printf("\nDigite o lado do dodecaedro regular: ");
  scanf("%f", &l);
  
  area = calculaArea(l);
  
  printf("\nA area e: %.2f\n", area);
  
  return 0;
}

float calculaArea(float l) {
  return 3* pow(l, 2) * sqrt(25 + 10 * sqrt(5));
}
