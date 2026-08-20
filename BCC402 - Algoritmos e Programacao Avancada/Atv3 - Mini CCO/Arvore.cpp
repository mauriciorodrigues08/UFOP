#include "include/Arvore.h"

void numNosRec(No *raiz, int *n);
void numeroFolhasRec(No *raiz, int *n);
void numBifurcacoesRec(No *raiz, int *n);

void destroiArvore(No *raiz){
  if(raiz == nullptr)
    return;
  
  destroiArvore(raiz->esq);
  destroiArvore(raiz->dir);

  delete raiz;

}

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

int profundidadeMax(No *raiz) {
    if (raiz == nullptr) 
      return 0;
    return 1 + std::max(profundidadeMax(raiz->esq), profundidadeMax(raiz->dir));
}

void numBifurcacoesRec(No *raiz, int *n){
  if(raiz == nullptr)
    return;
  if(raiz->esq != nullptr && raiz->dir != nullptr)
    (*n)++;
  numBifurcacoesRec(raiz->esq, n);
  numBifurcacoesRec(raiz->dir, n);
}

int numBifurcacoes(No *raiz){
  int bifurcacoes = 0;
  numBifurcacoesRec(raiz, &bifurcacoes);
  return bifurcacoes;
}
