//Crie uma função recursiva que calcula a potência de um número.

#include <stdio.h>

int pot(int base, int exp);

int main() {
  int base = 2;
  int exp = 10;
  
  printf("%d ^ %d = %d\n", base, exp, pot(base, exp));
  
  return 0;
}

int pot(int base, int exp) {
  //caso base
  if (exp <= 0)
    return 1;

  //chamada recursiva ( pot(base, exp-1) ) e processamento complementar ( base * )
  return base * pot(base, exp-1);
}
