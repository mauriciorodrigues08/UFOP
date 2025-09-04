/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <string.h>
#define TAM 60

int main() {
  char name[TAM], lastName[TAM];
  int lastSpace, cont, ultCont = 0;

  //recebendo nome e retirando \n
  printf("Digite o nome completo: ");
  fgets(name, TAM, stdin);
  int t = strlen(name);
  name[t] = '\0';
  t--;
  cont = t;

  //separando ultimo nome e contando qtd de letras
  for (int i=0; i<t; i++)
    if (name[i] == ' ') {
      lastSpace = i;
      cont--;
    }

  name[lastSpace] = '\0';

  int j = 0;
  for (int i=lastSpace; i<t; i++) {
    lastName[j] = name[i];
    j++;
    ultCont++;
  }
  lastName[j+1] = '\0';

  //printando resultado
  printf("%s, %s\n", lastName, name);
  
  return 0;
}