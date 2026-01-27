#ifndef ALUNO_H
#define ALUNO_H

typedef struct peca {
  char tipo; //A, B ou C
  char id[4]; //identificador
  int lote; //numero de lote
  float preco; //preco em reais
  int peso; //peso em gramas
} Peca;

void addPeca(Peca *pecas, Peca aux, int index);
void sort(Peca *pecas, int qtd);
void quicksort(Peca *pecas, int ini, int fim);
int particiona(Peca *pecas, int ini, int fim);
void troca(Peca *a, Peca *b);
int compara(Peca a, Peca b);


#endif