#include "aluno.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
  int qtd;

  //recebe a quantidade de pecas
  scanf("%d", &qtd);

  //aloca o vetor de pecas
  Peca *pecas = (Peca*) malloc(qtd * sizeof(Peca));

  //adiciona os valores ao vetor
  for (int i=0; i<qtd; i++) {
    getchar(); //limpa o buffer

    Peca aux;
    aux.tipo = toupper(getchar());
    scanf("%s %d %f %d", aux.id, &aux.lote, &aux.preco, &aux.peso);
    
    addPeca(pecas, aux, i);
  }

  // //teste de entrada
  // printf("\n--- TESTE DE INSERÇÃO DE PEÇAS ---");
  // for (int i=0; i<qtd; i++) {
  //   printf("\nPeça %d:\n", i+1);
  //   printf("%c - %s - %d - %.2f - %d\n", pecas[i].tipo, pecas[i].id, pecas[i].lote, pecas[i].preco, pecas[i].peso);
  // }
  // printf("----------------------------------\n\n");

  //quick sort
  sort(pecas, qtd);

  //print do resultado
  int i = 0;

  printf("Tipo A: ");
  while (pecas[i].tipo == 'A') {
    printf("%s ", pecas[i].id);
    i++;
  }
  
  printf("\nTipo B: ");
  while (pecas[i].tipo == 'B') {
    printf("%s ", pecas[i].id);
    i++;
  }

  printf("\nTipo C: ");
  while (pecas[i].tipo == 'C') {
    printf("%s ", pecas[i].id);
    i++;
  }

  printf("\n");

  //libera o vetor de pecas
  free(pecas);

  return 0;
}