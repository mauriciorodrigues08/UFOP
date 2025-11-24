//Faça uma função recursiva que, dado um número n, calcule a soma dos números pares entre 0 e n. Após isso, fale qual é a complexidade dela.

#include <stdio.h>
int soma0aN(int n);

int main() {
  int n, res = 0;

  //recebe valor de n
  printf("Digite o valor de n: ");
  scanf("%d", &n);

  //chamda da função recursiva
  res = soma0aN(n);

  //print resultado
  printf("Soma dos números pares de 0 até %d: %d\n", n, res);

  return 0;
}

int soma0aN(int n) { //O(n)
  //caso base
  if (n <= 0) return 0;

  //processamento
  if (n % 2 == 0)
     return n + soma0aN(n-1);

  //chamada recursiva
  return soma0aN(n-1);
}