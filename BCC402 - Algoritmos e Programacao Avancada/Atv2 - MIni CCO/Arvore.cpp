#include "include/Arvore.h"

void numNosRec(No *raiz, int *n);
void numeroFolhasRec(No *raiz, int *n);

int numeroNos(No *raiz){
  int n = 0;
  numNosRec(raiz, &n);
  return n;
}

void numNosRec(No *raiz, int *n){
  if(raiz != nullptr){
    (*n)++;
    numNosRec(raiz->esq, n);
    numNosRec(raiz->dir, n);
  }
}

int numeroFolhas(No *raiz){
  int n = 0;
  numeroFolhasRec(raiz, &n);
  return n;
}

void numeroFolhasRec(No *raiz, int *n){
  if(raiz != nullptr){
    if(raiz->esq == nullptr && raiz->dir == nullptr){
      (*n)++;
      return;
    }
    numeroFolhasRec(raiz->esq, n);
    numeroFolhasRec(raiz->dir, n);
  }
}