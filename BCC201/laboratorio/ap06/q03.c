/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

int main(){
  float n1, n2;
  
  do {
    printf("\nDigite as notas do aluno: ");
    scanf("%f%f", &n1, &n2);

    if (n1 > 0 && n2 > 0)
      printf("\nA média das notas é %.1f\n",(n1+n2)/2);
  } while (n1 > 0 && n2 > 0);

  return 0;
}