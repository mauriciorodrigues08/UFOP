/*Faça um programa que leia o nome completo de uma pessoa com até 60 caracteres. Em seguida, imprima o último sobrenome e nome (veja o exemplo abaixo) e a quantidade total de letras do nome completo (desconsidere espaços) e do último sobrenome.*/

#include <stdio.h>
#include <string.h>
#define TAM_MAX 60

int main() {
  int contUltimo = 0, contTot = 0, aux, i;
  char nome[TAM_MAX], ultimoNome[TAM_MAX];

  //recebendo string
  printf("Digite o nome completo: ");
  fgets(nome, TAM_MAX, stdin); //'\n' incluído na string

  //removendo o \n da string
  int tam = strlen(nome);
  nome[tam - 1] = '\0';

  //separando último nome
  int tamString = strlen(nome);

  for (i=0; i<tamString; i++) {
    if (nome[i] == ' ')
      aux = i;
    else
      contTot++;
  }

  for (i=0; i<tamString; i++)
    ultimoNome[i] = nome[aux+1+i];
  
  //organizando \0 e calculando contadores
  contUltimo = strlen(ultimoNome);
  nome[aux] = '\0';
  ultimoNome[contUltimo] = '\0';

  //imprimindo resultado
  printf("%s, %s\n", ultimoNome, nome);
  printf("Total de letras: %d\n", contTot);
  printf("Total de letras do último sobrenome: %d\n", contUltimo);

  return 0;
}