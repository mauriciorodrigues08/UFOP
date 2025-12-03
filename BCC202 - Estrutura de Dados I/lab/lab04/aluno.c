#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aluno.h"

//cria um novo nó
No* novoNo(int cidade) {
  No *no = malloc(sizeof(No));

  if (!novoNo)
    return NULL;

  no->cidade = cidade;
  no->prox = NULL;

  return no;
}

//adiciona um novo caminho (a -> b)
void adicionaCaminho(MapaCidades *mapa, int a, int b) {
  No *no = novoNo(b);

  if (!novoNo)
    return NULL;

  no->prox = mapa->vetor[a];
  mapa->vetor[a] = no;
}

//cria o mapa das cidades
MapaCidades criaMapa(int n, int m) {
  MapaCidades mapa;

  //criando mapa
  mapa.qtd = n;
  mapa.vetor = calloc(n, sizeof(No*));

  if (!mapa.vetor) {
    mapa.vetor = NULL;
    return mapa;
  }

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

  /* busca iterativa - pilha */
  
  //pega a quantidade de cidades
  int n = mapa->qtd;

  //aloca a pilha
  int *pilha = malloc(n * sizeof(int));
  if (!pilha)
    return false;
  
  //inicia a busca a partir de a
  int topo = 0;
  pilha[topo++] = a;
  visitado[a] = true;

  while (topo > 0) {
    int ultimo = pilha[--topo]; //pega o ultimo valor e desempilha

    //verifica se encontrou
    if (ultimo == b) {
      free(pilha);
      return true;
    }

    //empilha vizinhos não visitados
    No *pNo = mapa->vetor[ultimo];
    
    while(pNo != NULL) {
      int i = pNo->cidade;

      if (!visitado[i]) {
        visitado[i] = true;
        pilha[topo++] = i;
      }

      pNo = pNo->prox;
    }
  }

  free(pilha);
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
