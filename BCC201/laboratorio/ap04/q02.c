/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

int main() {
  float valor;
  int condicao;

  printf("\nDigite o preço do produto: ");
  scanf("%f", &valor);

  printf("\n1- A vista em dinheiro ou pix\n2- A vista no cartão de crédito\n3- Em duas vezes\n4- Em três vezes");

  printf("\nDigite a condição de pagamento: ");
  scanf("%d", &condicao);

  switch (condicao)
  {
  case 1:
    valor *= 0.9;
    break;
  
  case 2:
    valor *= 0.95;
    break;

  case 3:
    break;
  
  case 4:
    valor *= 1.1;
    break;
  
  default:
    printf("\nCondicao de pagamento invalida\n");
    return 0;
  }

  printf("O valor final do seu produto sera: R$ %.2f\n", valor);
  return 0;
}
