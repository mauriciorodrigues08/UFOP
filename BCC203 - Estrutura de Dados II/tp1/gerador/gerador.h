#ifndef _GERADOR_H_
#define _GERADOR_H_

#include "../headers/registro.h"
#include <stdio.h>

void geradorArvoreB(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes);
void geradorArvoreBinaria(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes);
void geradorSequencial(FILE *arq, int tipoDeOrdenacao, int numeroDeItens,  int *qtdTransferencias, int *qtdComparacoes);
void geradorArvoreEstrela(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes);



#endif