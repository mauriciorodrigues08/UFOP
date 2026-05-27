#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "registro.h"


typedef struct {
    Registro reg;
    int esq;
    int dir;
} NoBinario;

void insereArvoreBinaria(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes);
bool pesquisaArvoreBinaria(FILE *arquivo, int chaveBuscada, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes);
void printArvoreBinaria(FILE *arq);


#endif