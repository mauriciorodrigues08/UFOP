/*
Nome: Maurício de Oliveira Santos Rodrigues
Nome: 25.5.4020
*/

#include <stdio.h>

int main() {
  int matricula;
  float nota;
  char conceito;

  //recebendo variaveis
  printf("Digite a matrícula: ");
  scanf("%d", &matricula);

  printf("Digite a nota: ");
  scanf("%f", &nota);

  //verificando conceito
  if(nota<0) {
    printf("Nota inválida.\n");
    return 0;
  }
  else if(nota<3) {conceito = 'E';}
  else if(nota<6) {conceito = 'D';}
  else if(nota<8) {conceito = 'C';}
  else if(nota<9) {conceito = 'B';}
  else{conceito = 'A';}

  //imprimindo resultado
  printf("\nMatricula: %d", matricula);
  printf("\nConceito %c\n", conceito);

  return 0;
}