#include <stdio.h>

//a
int fatorialRecursivo(int n);

//b
int fibonacciRecursivo(int n);

//c
int potenciaRecursivo(int n, int exp);

int main(){
  int n, exp;
  int resultFat, resultFib, resultPot;

  printf("Digite o valor de n: ");
  scanf("%d", &n);

  resultFat = fatorialRecursivo(n);

  resultFib = fibonacciRecursivo(n);

  printf("\nInsira o expoente de %d: ", n);
  scanf("%d", &exp);
  resultPot = potenciaRecursivo(n, exp);

  printf("\nFatorial: %d\nFibonacci: %d\nPotencia: %d\n", resultFat, resultFib, resultPot);


  return 0;
}

int fatorialRecursivo(int n){
  if(n == 0 || n == 1)
    return 1;
  else
    return n * fatorialRecursivo(n-1);
}

int fibonacciRecursivo(int n){
  if(n == 1)
    return 1;
  else if(n == 2)
    return 1;
  else
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

int potenciaRecursivo(int n, int exp){
  if(exp == 0)
    return 1;
  else
    return n * potenciaRecursivo(n, exp-1);
}