//Faça uma função recursiva que calcula a soma dos números entre o intervalo 1 e n (n é fornecido pelo usuário).

#include <stdio.h>

int somaRec(int n);

int main() {
  int n;
  
  printf("Digite o valor de n: ");
  scanf("%d", &n);

  printf("Soma de 1 até %d = %d\n", n, somaRec(n));
  
  return 0;
}

int somaRec(int n) {
  //caso base
  if (n==1)
    return n;

  //soma
  return n + somaRec(n-1);
}