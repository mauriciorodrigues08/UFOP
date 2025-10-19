#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "formula.h"

void printClausula(int *vec);
int **alocaMatrizFormula(int numClausulas, int numVariaveis);
void liberaMatrizFormula(int **var, int numClausulas);

int main(){
  Formula *formula;
  int numVariaveis, numClausulas;
  int **matrizFormula;
  bool *conjuntoSolucao;

  printf("Entre com o numero de variaveis: ");
  scanf("%d", &numVariaveis);


  printf("\nEntre com o numero de clausulas: ");
  scanf("%d", &numClausulas);

  matrizFormula = alocaMatrizFormula(numClausulas, numVariaveis);

  for(int i = 0; i < numClausulas; i++){
    printf("Entre com a clausula %d: ", i + 1);
    for(int j = 0; j < numVariaveis; j++){
      scanf("%d", &matrizFormula[i][j]);
    }
    printf("\n");
  }

  formula = criaFormula(numVariaveis, numClausulas);
  for(int i = 0; i < numClausulas; i++){
    adicionaClausula(formula, i, matrizFormula[i], numVariaveis);
  }

  liberaMatrizFormula(matrizFormula, numClausulas);

  printf("Formula: ");
  imprimeFormula(formula);

  conjuntoSolucao = malloc(numVariaveis * sizeof(bool));

  bool existeSolucao = solucaoFormula(formula, conjuntoSolucao);

  if(!existeSolucao){
    printf("\nFormula insatisfazivel!\n");
  }
  else{
    char *varlist = malloc(numVariaveis * sizeof(char));
    printf("\nValoracao:\n");

    getVarList(varlist, formula);

    for(int i = 0; i < numVariaveis; i++){
      printf("%c = %s\n", varlist[i], conjuntoSolucao[i]? "True":"False");
    }

    free(varlist);
  }


  free(conjuntoSolucao);
  destroiFormula(formula);

  return 0;
}

//
int **alocaMatrizFormula(int numClausulas, int numVariaveis){
  int **pt;
  pt = (int**) malloc(numClausulas * sizeof(int*));

  if(!pt)
    return 0;
  
  for(int i = 0; i < numClausulas; i++){
    pt[i] = (int*) malloc(numVariaveis * sizeof(int));

    if(!pt[i]){
      for(int j = i-1; j >= 0; j--)
        free(pt[j]);
      free(pt);
      return 0;
    }
  }
  return pt;
}

//
void liberaMatrizFormula(int **var, int numClausulas){
  for(int i = 0; i < numClausulas; i++){
    free(var[i]);
  }
  free(var);
}