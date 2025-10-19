#ifndef FORMULA_H_
#define FORMULA_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "clausula.h"

typedef struct Formula Formula;

Formula *criaFormula(int numVariaveis, int numClausulas);
void destroiFormula(Formula *pt);
void adicionaClausula(Formula *pt, int index,int *var, int numVariaveis);
void imprimeFormula(Formula *pt);
bool solucaoFormula(Formula *pt, bool *conjuntoSolucao);

void getVarList(char *listaVar, Formula *pt);

#endif //FORMULA_H_