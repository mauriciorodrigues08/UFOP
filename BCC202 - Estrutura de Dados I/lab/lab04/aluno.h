#ifndef ALUNO_H
#define ALUNO_H

#include <stdbool.h>

typedef struct no {
  int cidade;
  struct no *prox;
} No;

typedef struct {
  No **vetor;
  int qtd;
} MapaCidades;

No* novoNo(int cidade);
void adicionaCaminnho(MapaCidades *mapa, int a, int b);
MapaCidades criaMapa(int n, int m);
bool existeCaminho(MapaCidades *mapa, int a, int b, bool *visitado);
void liberaMapa(MapaCidades *mapa);

#endif
