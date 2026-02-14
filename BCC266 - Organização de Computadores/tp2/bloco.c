#include "bloco.h"

void criaBloco(BlocoDeMemoria *bloco, int quantidadePalavras, int endereco){
  bloco->addBloco = endereco;
  bloco->quantidadePalavras = quantidadePalavras;
  bloco->palavras = (int*) malloc(quantidadePalavras * sizeof(int));
  bloco->atualizado = false;
  bloco->lru = 0;
}

void liberaBloco(BlocoDeMemoria *bloco){
  if (bloco->palavras != NULL) {
    free(bloco->palavras);
    bloco->palavras = NULL;
  }
}

void copiarBloco(BlocoDeMemoria *origem, BlocoDeMemoria *dest){
  for(int i = 0; i < origem->quantidadePalavras; i++){
    dest->palavras[i] = origem->palavras[i];
  }
  dest->addBloco = origem->addBloco;
  dest->atualizado = origem->atualizado;
  dest->lru = origem->lru;
}