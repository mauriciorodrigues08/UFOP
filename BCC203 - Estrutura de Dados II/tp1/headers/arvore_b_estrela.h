#ifndef _ARVORE_B_ESTRELA_H
#define _ARVORE_B_ESTRELA_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "registro.h"

#define M 4
#define MM (2*M) 

typedef enum {interna, externa} intExt;

typedef struct PaginaEstrela{
  intExt tipoDePagina;
  union{
    struct {
      int n;
      int ri[MM];
      int p[MM + 1];
    } paginaInterna;
    struct {
      int n;
      Registro r[MM];
    } paginaExterna;
  } UU;
}PaginaEstrela;



bool pesquisarChaveB_estrela(FILE *arquivo, int chave, Registro *reg, int *qtdTransferencias, int *qtdComparacoes);
void insereArvoreB_estrela(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes);
void printArvoreB_estrela(FILE *arquivo, int *qtdTransferencias);

#endif