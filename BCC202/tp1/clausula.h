#ifndef CLAUSULA_H_
#define CLAUSULA_H_

#include <stdlib.h>
#include <stdio.h>



typedef struct Clausula Clausula;

Clausula *criaClausula(int *variaveis, int numVariaveis);

Clausula *destroiClausula(Clausula *pt);

void tostringClausula(Clausula *pt, int numVariaveis);

#endif //CLAUSULA_H_