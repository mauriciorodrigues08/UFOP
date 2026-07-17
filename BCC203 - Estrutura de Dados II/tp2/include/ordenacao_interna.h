#ifndef ORDENACAO_INTERNA_H
#define ORDENACAO_INTERNA_H

#include "intercalacao_b.h" 

void OrdenacaoInterna(Item bloco[], int n, int *comparacoes);
void GeracaoBlocosOrdenados(FILE *arqEntrada, FILE **arqSaida, int numFitasSaida, int quant, int n_blocos[], int *tranfLeitura, int *transfEscrita, int *comparacoes);

#endif
