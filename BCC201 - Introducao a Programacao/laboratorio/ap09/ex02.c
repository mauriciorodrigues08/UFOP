/*Faça um programa que leia uma frase (de no máximo 50 caracteres), e duas letras L1 e L2.  O seu programa deve trocar todas as ocorrências da letra L1 na frase pela letra L2, e mostrar a frase com as letras trocadas. Fique atento pois letras maíusculas, minúsculas e acentuadas devem ser considerados caracteres diferentes.*/

#include <stdio.h>
#include <string.h>
#define TAM_MAX 50

int main() {
  char frase[TAM_MAX], l1, l2;

  //recebendo frase
  printf("Digite uma frase: ");
  fgets(frase, TAM_MAX-1, stdin); //armazena '\n' na string
  frase[strlen(frase)-1] = '\0'; //retirando '\n'

  //recebendo L1 e L2
  printf("Digite L1: ");
  scanf("%c", &l1);
  getchar();

  printf("Digite L2: ");
  scanf("%c", &l2);

  //percorrendo frase e alterando letras
  for (int i=0; i<TAM_MAX; i++)
    if (frase[i] == l1)
      frase[i] = l2;

  printf("%s", frase);

  return 0;
}