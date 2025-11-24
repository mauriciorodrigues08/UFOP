#ifndef FORMULA_H_
#define FORMULA_H_

//imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//definicao futura de structs
typedef struct Formula Formula;

//prototipos das funcoes relacionadas a formulas
Formula *criaFormula(int numVariaveis, int numClausulas);
void destroiFormula(Formula *formula);
void adicionaClausula(Formula *formula, int index, int *var, int numVariaveis, int tamanhoClausula);
void imprimeFormula(Formula *formula, int tamClausula);
bool solucionaFormula(Formula *formula, bool **conjuntoSolucao, int tamClausula);
void getVarList(char *listaVar, Formula *formula);

#endif
