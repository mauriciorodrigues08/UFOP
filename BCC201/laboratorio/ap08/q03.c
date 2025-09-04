/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <ctype.h>
#define TAM 10

void limpar_buffer();

int main() {
  char vchar[TAM], vog[TAM], cons[TAM], aux;
  int contv = 0, contc = 0;
  
  //preenchendo vetores
  for (int i=0; i<TAM; i++) {
  
  //verificando se é uma letra e analisando vogal ou consoante
  do {
    printf("Digite o %d caractere: ", i+1);
    aux = tolower(getchar());
    limpar_buffer();
    if(aux>='a' && aux<='z') {
      vchar[i] = aux;
      if (vchar[i] == 'a' || vchar[i] == 'e' || vchar[i] == 'i' || vchar[i] == 'o' || vchar[i] == 'u') {
        vog[i] = vchar[i];
        cons[i] = '#';
        contv++;
      }else {
        cons[i] = vchar[i];
        vog[i] = '#';
        contc++;
      }
    }else
        printf("\nCaracter inválido! Digite novamente.\n");
    } while (aux<'a' || aux>='z');
  }

  //imprimindo vogais
  printf("\n%d vogais: ", contv);
  for (int i=0; i<TAM; i++) {
    if (vog[i]>='a' && vog[i]<='z')
      printf("%c ", vog[i]);
  }
  printf("\n");

  //imprimindo consoantes
  printf("%d consoantes: ", contc);
  for (int i=0; i<TAM; i++) {
    if (cons[i]>='a' && cons[i]<='z')
      printf("%c ", cons[i]);
  }
  printf("\n");
  
  return 0;
}

void limpar_buffer() {
   int ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
}