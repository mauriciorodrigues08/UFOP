/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

void divisores(int);

int main() {
  int n;
  
  printf("Digite o valor de n: ");
  scanf("%d", &n);
  
  divisores(n);
  return 0;
}

void divisores(int n) {
  printf("Os divisores de %d são: ",n);
  for (int i=1; i<=n; i++) {
    if (n % i == 0)
      printf("%d ", i);
  }
  printf("\n");
}