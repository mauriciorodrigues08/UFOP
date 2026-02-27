/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

int main() {
  int ano;
  
  //recebendo ano
  printf("\nEntre com o ano: ");
  scanf("%d", &ano);

  //calcular se é bissexto
  if( (ano % 4 == 0 && ano % 100 != 0) || (ano % 100 == 0 && ano % 400 == 0) ){
    printf("O ano %d é bissexto\n", ano);
  }
  else{printf("O ano %d não é bissexto\n", ano);}


  return 0;
}
