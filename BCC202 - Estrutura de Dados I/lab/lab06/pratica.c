#include <stdio.h>
#include <stdlib.h>

#include "aluno.h"

int main() {
  int qtd;
  char busca[MAX_PALAVRA];
  Registro *dicionario;

  //recebe a quantidade de palavras
  scanf("%d", &qtd);
  getchar();

  //cria o vetor
  dicionario = (Registro *) malloc(qtd * sizeof(Registro));

  //recebe os registros
  getRegistros(dicionario, qtd);

  //ordena o vetor
  qsort(dicionario, qtd, sizeof(Registro), comparaPalavras);

  //recebe palavra para ser buscada
  scanf("%s", busca);
  lower(busca);

  //busca binaria
  int index = buscaBinaria(dicionario, busca, 0, qtd);

  if (index < 0)
    printf("Palavra nao encontrada!\n");

  else
    printf("%s: %s\n", dicionario[index].palavra, dicionario[index].descricao);

  //libera a memoria do vetor
  free(dicionario);

  return 0;
}