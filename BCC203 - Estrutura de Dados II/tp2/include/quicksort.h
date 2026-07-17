#ifndef QUICKSORT_EXTERNO_H
#define QUICKSORT_EXTERNO_H

#include <iostream>
#include "arquivo.h"


#define LIMITE_MEMORIA 20

// typedef struct Item {
//     long int inscricao;
//     float nota;
//     char estado[3];
//     char cidade[51];
//     char curso[31];
// } Item;

void quicksort(FILE *arquivo, long quant, int *tranfLeitura, int *transfEscrita, int *comparacoes);

#endif