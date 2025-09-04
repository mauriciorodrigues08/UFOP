/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

long long fat(int n);

int main() {
  long long res;
  int n;
  
  printf("Digite o valor de n: ");
  scanf("%d", &n);

  res = fat(n);
  
  printf("\nFatorial de %d = %lld\n", n, res);
  
  return 0;
}

long long fat(int n) {
  long long res = 1;

  for (int i=n; i>0; i--) {
    res *= i;
  }

  return res;
}