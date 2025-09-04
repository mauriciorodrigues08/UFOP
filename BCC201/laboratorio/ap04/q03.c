/*
Nome: Maurício de Oliveira Santos Rodrigues
Martícula: 25.1.4020
*/

#include <stdio.h>
#include <ctype.h>

int main() {
  char sx;
  int idade, tempo;

  //recebendo variaveis
  printf("\nDigite o sexo: ");
  scanf(" %c", &sx);

  printf("Digite a idade: ");
  scanf("%d", &idade);

  printf("Digite o tempo de contribuição para o INSS: ");
  scanf("%d", &tempo);

  //analisando variaveis e imprimindo resultado
  if(toupper(sx) == 'M') {
    if((tempo >= 35 && idade >= 65) || (tempo + idade == 100)) {
      printf("\nVoce pode se aposentar com salario integral\n");
    } 
    else {printf("\nVoce nao pode se aposentar com salario integral\n");}
  } 
  else if(toupper(sx) == 'F') {
    if((tempo >= 30 && idade >= 60) || (tempo + idade == 90)){
      printf("\nVoce pode se aposentar com salario integral\n");
    }
    else {printf("\nVoce nao pode se aposentar com salario integral\n");}
  }
  else {printf("\nSexo inválido\n");}

  return 0;
}
