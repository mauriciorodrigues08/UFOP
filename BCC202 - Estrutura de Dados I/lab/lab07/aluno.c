//modulos
#include "aluno.h"

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//structs
struct no {
  char palavra[MAX_PALAVRA];
  int freq;
  struct no *dir;
  struct no *esq;
};

//funcoes
No* iniciaArvore(char *palavra) {
  No *novo = (No*) malloc(sizeof(No));

  if (!novo)
    return NULL;

  novo->dir = NULL;
  novo->esq = NULL;
  strncpy(novo->palavra, palavra, MAX_PALAVRA);
  novo->freq = 1;

  return novo;
}

No* destroiArvore(No *raiz) {
  if (raiz != NULL) {
    destroiArvore(raiz->esq);
    destroiArvore(raiz->dir);
    free(raiz);
  }
  return NULL;
}

No* adicionaNo(No *raiz, char *palavra) {
  //verifica se a arvore ainda nao existe
  if (raiz == NULL) {
    return iniciaArvore(palavra);
  }

  //pega o resultado da comparacao entre a palavra e o no atual
  int comp = strcmp(palavra, raiz->palavra);

  //palavra igual ao no atual
  if (comp == 0) {
    //incrementa a frequencia do no atual
    raiz->freq++;
  } 

  //palavra menos que o no atual
  else if (comp < 0) {
    //vai para a esquerda
    raiz->esq = adicionaNo(raiz->esq, palavra);
  }

  //palavra maior que o no atual
  else {
    //vai para a direita
    raiz->dir = adicionaNo(raiz->dir, palavra);
  }

  return raiz;
}

void printResultado(No *raiz) {
  if (raiz != NULL) {
    printResultado(raiz->esq);
    printf("%s: %d\n", raiz->palavra, raiz->freq);
    printResultado(raiz->dir);
  }
}