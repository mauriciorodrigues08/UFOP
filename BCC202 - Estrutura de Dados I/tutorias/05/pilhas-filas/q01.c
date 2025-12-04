//Implemente as funções PilhaEhVazia(verifica se a pilha está vazia), PilhaPush(adiciona um elemento ao topo) e PilhaPop(retira o elemento do topo). Você deve implementar via ponteiro e via vetor.

#include <stdbool.h>
#include <stdlib.h>

/* IMPLEMENTAÇÕES POR VETOR */

#define MAX 100

typedef struct {
  int dados[MAX];
  int topo;
} PilhaVet;

bool PilhaEhVaziaVet(PilhaVet *pPilha) {
  if (!pPilha)
    return true;
  
  return pPilha->topo < 0; 
}

bool PilhaPushVet(PilhaVet *pPilha, int dado) {
  if (!pPilha)
    return false;
  
  if (pPilha->topo == MAX-1)
    return false;
  
  pPilha->dados[++(pPilha->topo)] = dado; //atualiza o indice do topo e adiciona o valor
  
  return true;
}

bool PilhaPopVet(PilhaVet *pPilha, int *x) {
  if (!pPilha)
    return false;
  
  if (PilhaEhVaziaVet(pPilha))
    return false;
  
  *x = pPilha->dados[pPilha->topo];
  pPilha->topo--;
  return true;
}

/* IMPLEMENTAÇÕES POR PONTEIRO */

typedef struct no {
  int dado;
  struct no *prox;
} No;

typedef struct {
  No *topo;
} PilhaPoint;

bool PilhaEhVaziaPoint(PilhaPoint *pPilha) {
  if (!pPilha)
    return true;

  return pPilha->topo == NULL;
}

bool PilhaPushPoint(PilhaPoint *pPilha, int dado) {
  if (!pPilha)
    return false;

  No *novo = (No *) malloc(sizeof(No)); //aloca um novo nó
  if (!novo) 
    return false;

  novo->dado = dado; //adiciona o dado ao novo nó
  novo->prox = pPilha->topo; //prox do novo nó passa a ser o antigo topo
  pPilha->topo = novo; //topo da pilha passa a ser o novo valor

  return true;
}

bool PilhaPopPoint(PilhaPoint *pPilha, int *x) {
  if (!pPilha)
    return false;

  if (PilhaEhVaziaPoint(pPilha))
    return false;

  No *aux = pPilha->topo; //variavel aux recebe o valor a ser retirado (topo)
  pPilha->topo = pPilha->topo->prox; //novo topo recebe o prox nó (antigo segundo elemento)

  *x = aux->dado; //informa o valor que foi excluído

  free(aux);
  return true;
}

#include <stdio.h>

int main() {
  printf("\n===== TESTANDO PILHA POR VETOR =====\n");

  PilhaVet pilhaVet;
  pilhaVet.topo = -1; //inicialização
  int removidoVet;

  printf("\nA pilha está vazia? %s\n\n", PilhaEhVaziaVet(&pilhaVet) ? "sim" : "não");

  PilhaPushVet(&pilhaVet, 10) ? printf("10 empilhado\n") : printf("Falha ao empilhar 10\n");
  PilhaPushVet(&pilhaVet, 20) ? printf("20 empilhado\n") : printf("Falha ao empilhar 20\n");
  PilhaPushVet(&pilhaVet, 30) ? printf("30 empilhado\n") : printf("Falha ao empilhar 30\n");

  printf("\nA pilha está vazia? %s\n", PilhaEhVaziaVet(&pilhaVet) ? "sim" : "não");

  printf("\nDesempilhando:\n");
  if (PilhaPopVet(&pilhaVet, &removidoVet))
    printf("Valor removido: %d\n", removidoVet);

  if (PilhaPopVet(&pilhaVet, &removidoVet))
    printf("Valor removido: %d\n", removidoVet);

  if (PilhaPopVet(&pilhaVet, &removidoVet))
    printf("Valor removido: %d\n", removidoVet);

  printf("\nA pilha está vazia? %s\n", PilhaEhVaziaVet(&pilhaVet) ? "sim" : "não");



  printf("\n===== TESTANDO PILHA POR PONTEIRO =====\n");
  PilhaPoint pilhaPoint;
  pilhaPoint.topo = NULL; //inicialização
  int removidoPoint;

  printf("\nA pilha está vazia? %s\n\n", PilhaEhVaziaPoint(&pilhaPoint) ? "sim" : "não");
  
  PilhaPushPoint(&pilhaPoint, 5) ? printf("5 empilhado\n") : printf("Falha ao empilhar 5\n");
  PilhaPushPoint(&pilhaPoint, 15) ? printf("15 empilhado\n") : printf("Falha ao empilhar 15\n");
  PilhaPushPoint(&pilhaPoint, 25) ? printf("25 empilhado\n") : printf("Falha ao empilhar 25\n");
  
  printf("\nA pilha está vazia? %s\n", PilhaEhVaziaPoint(&pilhaPoint) ? "sim" : "não");
  
  printf("\nDesempilhando:\n");
  if (PilhaPopPoint(&pilhaPoint, &removidoPoint))
    printf("Valor removido: %d\n", removidoPoint);

  if (PilhaPopPoint(&pilhaPoint, &removidoPoint))
    printf("Valor removido: %d\n", removidoPoint);

  if (PilhaPopPoint(&pilhaPoint, &removidoPoint))
    printf("Valor removido: %d\n", removidoPoint);

  printf("\nA pilha está vazia? %s\n", PilhaEhVaziaPoint(&pilhaPoint) ? "sim" : "não");

  return 0;
}
