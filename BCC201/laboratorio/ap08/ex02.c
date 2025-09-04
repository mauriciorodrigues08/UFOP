/*Um número natural é primo se ele possui apenas dois divisores distintos. Assim, um número maior que 1 é primo se for divisível apenas por si próprio e por 1. Crie uma função que retorna 1 se o número passado como argumento for primo e 0 caso contrário. Implemente também a função main() para ler o valor de n e imprimir se n é primo ou não.*/

#include <stdio.h>

int primo(int n);

int main() {
  int n, res;
  
  //recebendo valor de n
  printf("Digite um número: ");
  scanf("%d", &n);
  
  //analisando n
  res = primo(n);
  
  //printando resultado
  if (res == 1)
    printf("%d é um número primo!\n", n);
  else
    printf("%d não é um número primo!\n", n);
  
  return 0;
}

int primo(int n) {
  int cont = 0;

  //verificando divisores
  for (int i=n; i>0; i--) {
    if (n % i == 0)
      cont++;
  }

  //analisando qtd de divisores
  if (cont == 2)
    return 1;
  
  return 0;
}