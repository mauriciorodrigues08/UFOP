/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <string.h>
#define TAM 31
#define TAM_MAX 91

int main() {
  char p1[TAM_MAX], p2[TAM], p3[TAM];
  
  //recebendo palavras
  do {
    printf("Digite a 1 palavra: ");
    scanf("%s", p1);
  } while (strlen(p1) > 30);
  
  do {
    printf("Digite a 2 palavra: ");
    scanf("%s", p2);
    getchar();
  } while (strlen(p2) > 30);
  
  do {
    printf("Digite a 3 palavra: ");
    scanf("%s", p3);
    getchar();
  } while (strlen(p3) > 30);
  
  //concatenando palavra s
  strcat(p1, p2);
  strcat(p1, p3);

  //imprimindo resultado
  printf("%s\n", p1);
  
  return 0;
}