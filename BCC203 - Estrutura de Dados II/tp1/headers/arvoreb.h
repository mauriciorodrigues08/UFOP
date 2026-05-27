#ifndef _ARVOREB_H_
#define _ARVOREB_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "registro.h"

#define M 4
#define MM (2*M) 

typedef struct Pagina{
  short n;
  Registro r[MM]; //registro
  int p[MM + 1]; //offset dos filhos
}Pagina;

bool pesquisaChave(FILE *arquivo, int chave, Registro *reg, int *qtdTransferencias, int *qtdComparacoes);
void insereNaArvore(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes);
void printArvore(FILE *arquivo, int *qtdTransferencias);

#endif