//modulos
#include "aluno.h"

//bibliotecas
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
  //le a frase
  char frase[1000];
  fgets(frase, 999, stdin);

  //remove o \n do final, se houver
  frase[strcspn(frase, "\n")] = '\0';

  //passa todas as letras para lower case
  int i=0;
  while(frase[i] != '\0') {  
    frase[i] = tolower(frase[i]);
    i++;
  }

  //cria o no raiz
  No *raiz = NULL;

  //a funcao strtok() localiza um delimitador e troca por '\0'
  //delimitadores definidos -> espaco, virgula, ponto e quebra de linha
  char *token = strtok(frase, " ,.\n");

  //cria e preenche a arvore
  while (token != NULL) { //O laço continua enquanto a função strtok() conseguir encontrar um novo delimitador
    raiz = adicionaNo(raiz, token); //token eh um ponteiro para o início da palavra atual dentro da frase.
    token = strtok(NULL, " ,.\n"); //continua de onde parou (NULL faz com que o ponteiro da funcao nao seja atualizado)
  }

  //printa resultado
  printResultado(raiz);

  //libera a memoria alocada para a arvore
  raiz = destroiArvore(raiz);

  return 0;
}