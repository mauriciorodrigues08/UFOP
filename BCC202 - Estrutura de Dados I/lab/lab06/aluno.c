#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aluno.h"

void getRegistros(Registro *dicionario, int qtd)  {
  for (int i=0; i<qtd; i++) {
    //recebe a palavra
    scanf("%s", dicionario[i].palavra);
    lower(dicionario[i].palavra);
    getchar();

    //recebe a descricao
    int j=0;
    char aux;
    while (true) {
      aux = getchar();

      if(aux == '\n') {
        j--;
        break;
      }

      dicionario[i].descricao[j] = aux;  
      j++;
    }

    dicionario[i].descricao[++j] = '\0';
  }
}

int comparaPalavras(const void *a, const void *b) {
  //Converte os ponteiros genéricos (void*) para Registro
  Registro *r1 = (Registro *)a;
  Registro *r2 = (Registro *)b;

  //Retorna o resultado da comparação alfabética
  return strcmp(r1->palavra, r2->palavra);
}

int buscaBinaria(Registro *dicionario, char *busca, int esq, int dir) {
  if (dir < esq)
    return -1;
  
  int meio = (esq + dir) / 2;
  int res = strcmp(dicionario[meio].palavra, busca);

  if (res > 0)
    return buscaBinaria(dicionario, busca, esq, meio-1);

  if (res < 0)
    return buscaBinaria(dicionario, busca, meio+1, dir);

  return meio;
}

void lower(char *palavra) {
  char *aux = palavra;
  while (*aux != '\0') {
    *aux = tolower(*aux);
    aux++;
  }
}