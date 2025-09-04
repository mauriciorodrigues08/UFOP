/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

int quadrado_por_soma(int n);

int main() {
  int n, res;
  
  printf("Digite o valor de n: ");
  scanf("%d", &n);
  
  res = quadrado_por_soma(n);
  
  printf("O quadrado de %d é %d\n", n, res);
  
  return 0;
}

int quadrado_por_soma(int n) {
  int aux = 0, i = 1;
  do {
    aux += i;
    i += 2;
  } while(i/2 < n);

  return aux;
}