#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "aluno.h"

void getRegistros(Registro *dicionario, int qtd)  {
  for (int i=0; i<qtd; i++) {
    //recebe a palavra
    scanf("%s", dicionario[i].palavra);
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

int binarySearch(Registro *dicionario, char *search, int left, int right) {
  if (right < left)
    return -1;
  
  int meio = (left + right) / 2;
  int res = strcmp(dicionario[meio].palavra, search);

  if (res > 0)
    return binarySearch(dicionario, search, left, meio-1);

  if (res < 0)
    return binarySearch(dicionario, search, meio+1, right);

  return meio;
}