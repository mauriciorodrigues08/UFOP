/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <math.h>

int calculaRaizes(float, float, float, float*, float*);

int main() {
  float a, b, c, x1, x2;
  int res;
  
  printf("\nDigite os valores de a, b, c: ");
  scanf("%f%f%f", &a, &b, &c);
  
  res = calculaRaizes(a, b, c, &x1, &x2);
  
  switch (res) {
    case 1:
    printf("\nx1 = %.2f\nx2 = %.2f\n", x1, x2);
    break;
    
    case 0:
    printf("\nNão foi possível calcular as raízes!\n");
    break;
  }
  
  return 0;
}

int calculaRaizes(float a, float b, float c, float *x1, float *x2) {
  float delta = pow(b, 2) - (4 * a * c);
  if (delta < 0)
    return 0;
  else {
    *x1 = (-b + sqrt(delta)) / (2 * a);
    *x2 = (-b - sqrt(delta)) / (2 * a);
    return 1;
  }
}
