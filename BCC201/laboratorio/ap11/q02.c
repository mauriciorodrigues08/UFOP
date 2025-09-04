/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#define TAM 50

void inverteStr(char p[], int t, char p2[]);

int main() {
  char p[TAM], p2[TAM];
  int t;
  
  do {
    printf("Digite uma palavra ou FIM para sair: ");
    fgets(p, TAM, stdin);
    if (strcmp(p, "FIM")) {
      //retirando \n
      t = strlen(p);
      p[t-1] = '\0';
      t--;
      
      //gerando string inversa
      inverteStr(p, t, p2);
      printf("1- %s\n", p);
      printf("2- %s\n", p2);
      
      //verificando palindromo
      if ( (strcmp(p, p2)) == 0 )
        printf("%s é um palíndromo\n", p);
      else
        printf("%s não é um palíndromo\n", p);
    }
    
  }while ((strcmp(p, "FIM") != 0));
}

void inverteStr(char p[], int t, char p2[]) {
  for (int i=0; i<=t; i++)
    p2[t-i] = p[i];

  p2[t] = '\0';
}