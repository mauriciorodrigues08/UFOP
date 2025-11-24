#ifndef CLAUSULA_H_
#define CLAUSULA_H_

//imports
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//definicao futura de structs
typedef struct Clausula Clausula;

//prototipos das funcoes relacionadas a clausulas
Clausula *criaClausula(int *variaveis, int numVariaveis);
Clausula *destroiClausula(Clausula *clausula);
void tostringClausula(Clausula *clausula, int numVariaveis);
bool testaClausula(int *variaveisUsadas, int *posicoesDasVariaveis, bool *conjuntoSolucao, int tam);
void retornaValoresDaClausula(Clausula *clausula, int tamClausula, int **vec);

#endif
