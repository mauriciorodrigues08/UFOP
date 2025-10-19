
#include "clausula.h"
#include <string.h>

//
struct Clausula{
  int *variaveis;
};

//
Clausula *criaClausula(int *variaveis, int numVariaveis){
  Clausula *pt;
  pt = (Clausula *) malloc(sizeof(Clausula));

  if(!pt)
    return 0;
  
  pt->variaveis = (int*) malloc(numVariaveis * sizeof(int));

  if(!pt->variaveis){
    free(pt);
    return 0;
  }

  for(int i = 0; i < numVariaveis; i++){
    pt->variaveis[i] = variaveis[i];
  }

  return pt;
}

//
Clausula *destroiClausula(Clausula *pt){
  free(pt->variaveis);
  free(pt);
  return 0; //??
}

//
void tostringClausula(Clausula *pt, int numVariaveis){
  
  printf("(");
  for(int i = 0; i < numVariaveis; i++){
    printf("%c%c%s", pt->variaveis[i] < 0? '~': 0, abs(pt->variaveis[i]) + 96, i == numVariaveis - 1? "\0":" V ");
  }
  printf(")");
}
