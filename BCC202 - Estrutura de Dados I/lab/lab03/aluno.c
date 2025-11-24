#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aluno.h"

//cria um novo nó
No* novoNo(int cidade) {
  No *no = malloc(sizeof(No));

  no->cidade = cidade;
  no->prox = NULL;

  return no;
}

//adiciona um novo caminho (a -> b)
void adicionaCaminho(MapaCidades *mapa, int a, int b) {
  No *no = novoNo(b);

  no->prox = mapa->vetor[a];
  mapa->vetor[a] = no;
}

//cria o mapa das cidades
MapaCidades criaMapa(int n, int m) {
  MapaCidades mapa;

  //criando mapa
  mapa.qtd = n;
  mapa.vetor = calloc(n, sizeof(No*));

  //adicionando caminhos de forma recursiva
  for (int i = 0; i < m; i++) {
    //recebe dois valores
    int a, b;
    scanf("%d %d", &a, &b);

    //adiciona o novo caminho
    if (a >= 0 && a < n && b >= 0 && b < n) {
      adicionaCaminho(&mapa, a, b);
    }
  }

  //retorna o mapa criado
  return mapa;
}

//verifica se existe caminho entre A e B
bool existeCaminho(MapaCidades *mapa, int a, int b, bool *visitado) {
  //verifica se o mapa ou posicoes do vetor sao nulos
  if (mapa == NULL || mapa->vetor == NULL)
    return false;

  //verifica se as cidades digitadas sao menores que 0 ou maiores/iguais que a quantidade de cidades na lista
  if (a < 0 || a >= mapa->qtd || b < 0 || b >= mapa->qtd)
    return false;

  //verifica se as cidades sao iguais
  if (a == b)
    return true;

  //posicao atual recebe marcacao (sinaliza que ja foi visitado na busca)
  visitado[a] = true;

  //busca recursiva
  No *prox = mapa->vetor[a];

  //analisa enquanto o prox elemento for não nulo
  while (prox != NULL) {
    int pos = prox->cidade;

    if (!visitado[pos]) {
      if (existeCaminho(mapa, pos, b, visitado))
        return true;
    }

    prox = prox->prox;
  }

  return false;
}

//libera a memoria alocada para o mapa
void liberaMapa(MapaCidades *mapa) {
  if (mapa == NULL || mapa->vetor == NULL) return;

  for (int i = 0; i < mapa->qtd; i++) {
    No *p = mapa->vetor[i];
    while (p != NULL) {
      No *aux = p->prox;
      free(p);
      p = aux;
    }
  }
  free(mapa->vetor);
  mapa->vetor = NULL;
  mapa->qtd = 0;
}
