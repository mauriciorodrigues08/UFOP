#include "instrucao.h"
#include "ram.h"

#include <stdio.h>
#include <stdbool.h>

Instrucao *criaInstrucoes(int n){
  Instrucao *result = (Instrucao*) malloc(n * sizeof(Instrucao));
  return result;
}

Instrucao *destroiInstrucoes(Instrucao *inst){
  free(inst);
  return NULL;
}