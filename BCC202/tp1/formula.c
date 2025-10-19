#include "formula.h"
#include "clausula.h"

//Criação da struct Formula
struct Formula{
  Clausula **clausulas;
  int *numClausulas;
  int *numVariaveis;
  char *listaDeVariaveis;
};

//
Clausula **utilMallocClausulas(int numVariaveis, int numClausulas);

//
Formula *criaFormula(int numVariaveis, int numClausulas){
  
  Formula *pt;
  pt = (Formula *) malloc(sizeof(Formula));

  pt->numClausulas = (int*) malloc(sizeof(int));
  pt->numVariaveis = (int*) malloc(sizeof(int));

  *(pt->numClausulas) =  numClausulas;
  *(pt->numVariaveis) = numVariaveis;

  pt->listaDeVariaveis = (char*) malloc(numVariaveis * sizeof(char));

  pt->clausulas = utilMallocClausulas(*(pt->numVariaveis), *(pt->numClausulas));

  return pt;
}

//
void destroiFormula(Formula *pt){
  for(int i = 0; i < *(pt->numClausulas); i++){
    free(pt->clausulas[i]);
  }
  free(pt->clausulas);

  free(pt->listaDeVariaveis);
  free(pt->numClausulas);
  free(pt->numVariaveis);
}

//
void adicionaClausula(Formula *pt, int index,int *var, int numVariaveis){
  pt->clausulas[index] = criaClausula(var, numVariaveis);
  if(index == 0) {
    for(int i = 0; i < numVariaveis; i++){
      pt->listaDeVariaveis[i] = (char) (abs(var[i]) + 96);
    }
  }
}

//
void getVarList(char *listaVar, Formula *pt){
  for(int i = 0; i < *(pt->numVariaveis); i++){
    listaVar[i] = pt->listaDeVariaveis[i];
  }
}

//
void imprimeFormula(Formula *pt){
  int tempVar, tempC;
  tempVar = *(pt->numVariaveis);
  tempC = *(pt->numClausulas);

  for(int i = 0; i < tempC; i++){
    tostringClausula(pt->clausulas[i], tempVar);
    if(i < tempC - 1)
      printf(" ^ ");
    else
      printf("\n");
  }
}

//
bool solucaoFormula(Formula *pt, bool *conjuntoSolucao){

  return false;
}

//
Clausula **utilMallocClausulas(int numVariaveis, int numClausulas){
  Clausula **temp;
  
  temp = (Clausula**) malloc(numClausulas * sizeof(Clausula*));

  if(!temp){
    return 0;
  }

  for(int i = 0; i < numClausulas; i++){
    temp[i] = (Clausula*) malloc(numVariaveis * sizeof(Clausula*));
    
    if(!temp[i]){
      for(int j = i - 1; j >= 0; j--){
        free(temp[j]);
      }
      free(temp);
      return 0;
    }
  }

  return temp; 
}