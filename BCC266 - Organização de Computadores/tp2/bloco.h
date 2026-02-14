#ifndef BLOCO_H
#define BLOCO_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct BlocoDeMemoria {
  int *palavras;
  int quantidadePalavras;
  int addBloco;
  bool atualizado;
  int lru;
} BlocoDeMemoria;

void criaBloco(BlocoDeMemoria *bloco, int quantidadePalavras, int endereco);
void liberaBloco(BlocoDeMemoria *bloco);
void copiarBloco(BlocoDeMemoria *origem, BlocoDeMemoria *dest);

#endif