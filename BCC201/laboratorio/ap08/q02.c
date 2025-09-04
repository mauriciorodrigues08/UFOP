/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

int main() {
  float som = 0, res, aux;
  int n = 0;

  do {
    printf("Digite um valor: ");
    scanf("%f", &aux);
    som += aux;
    if(aux!=0)
      n++;
  } while (aux != 0);

  if (n==0) {
    printf("\nNão foi possível calcular MA!\n");
  } else {
    res = (1.0/n) * som;
    printf("\nMA = %.2f\n", res);
  }
}