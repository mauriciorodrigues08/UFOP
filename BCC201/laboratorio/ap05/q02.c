/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

void ordena3valores(int a, int b, int c, int* menor, int* meio, int* maior);

int main() {
  int a, b, c, maior, meio, menor;
  
  printf("\nDigite três valores: ");
  scanf("%d%d%d", &a, &b, &c);
  
  ordena3valores(a, b, c, &menor, &meio, &maior);
  
  printf("Os valores ordenados são: %d %d %d\n", menor, meio, maior);
  
  return 0;
}

void ordena3valores(int a, int b, int c, int* menor, int* meio, int* maior) {
  // a maior
  if (a>b && a>c){
    *maior = a;
    if (b>c) {
      *meio = b;
      *menor = c;
    }else {
      *meio = c;
      *menor = b;
    }
  }
  // b maior
  else if (b>c) {
    *maior = b;
    if (a>c) {
      *meio = a;
      *menor = c;
    }
    else {
      *meio = c;
      *menor = a;
    }
  }
  //c maior
  else {
    *maior = c;
    if (a>b) {
      *meio = a;
      *menor = b;
    }
    else {
      *meio = b;
      *menor = a;
    }
  }
}
