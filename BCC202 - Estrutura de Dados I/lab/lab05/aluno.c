#include "aluno.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//funcao que adiciona uma peca ao vetor
void addPeca(Peca *pecas, Peca aux, int index) {
  pecas[index].tipo = aux.tipo; //tipo
  pecas[index].lote = aux.lote; //lote
  pecas[index].preco = aux.preco; //preco
  pecas[index].peso = aux.peso; //peso

  strcpy(pecas[index].id, aux.id); //id 
}

//funcao de ordenacao do vetor
void sort(Peca *pecas, int qtd) {
  quicksort(pecas, 0, qtd - 1); 
}

//implementacao do quick sort
void quicksort(Peca *pecas, int ini, int fim) {
  if (ini < fim) {
    int p = particiona(pecas, ini, fim);
    quicksort(pecas, ini, p - 1);
    quicksort(pecas, p + 1, fim);
  }
}

//funcao que faz a particao do vetor
int particiona(Peca *pecas, int ini, int fim) {
  Peca pivo = pecas[fim]; //pivo sempre no final
  int i = ini - 1;

  for (int j = ini; j < fim; j++) {
    if (compara(pecas[j], pivo) <= 0) {
      i++;
      troca(&pecas[i], &pecas[j]);
    }
  }

  troca(&pecas[++i], &pecas[fim]);
  return i;
}

int compara(Peca a, Peca b) {
  //ordena por tipo: A -> B -> C
  if (a.tipo != b.tipo)
    return a.tipo - b.tipo;

  //critério principal: tipo
  if (a.tipo == 'A' && a.peso != b.peso)
    return a.peso - b.peso;

  if (a.tipo == 'B' && a.preco != b.preco)
    return (a.preco > b.preco) ? 1 : -1;

  if (a.tipo == 'C' && a.lote != b.lote)
    return a.lote - b.lote;

  //desempates: lote - peso - preco
  if (a.lote != b.lote)
    return a.lote - b.lote;

  if (a.peso != b.peso)
    return a.peso - b.peso;

  if (a.preco != b.preco)
    return (a.preco > b.preco) ? 1 : -1;

  return 0;
}

void troca(Peca *a, Peca *b) {
  Peca temp = *a;
  *a = *b;
  *b = temp;
}