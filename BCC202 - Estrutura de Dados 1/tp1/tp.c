//imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "formula.h"

//defines
#define tamanho_Clausula 3

//prototipo das funcoes locais
int **alocaMatrizFormula(int numClausulas, int numVariaveis);
void liberaMatrizFormula(int **var, int numClausulas);

//main
int main(){
  Formula *formula;
  int numVariaveis, numClausulas;
  int **matrizFormula;
  bool *conjuntoSolucao;

  //recebendo numero de variaveis
  scanf("%d", &numVariaveis);

  //recebendo numero de clausulas
  scanf("%d", &numClausulas);

  //alocacao da matriz da formula
  matrizFormula = alocaMatrizFormula(numClausulas, tamanho_Clausula);

  //recebendo clausulas
  for(int i = 0; i < numClausulas; i++){
    for(int j = 0; j < tamanho_Clausula; j++){
      do{
        //recebe a clausula
        scanf("%d", &matrizFormula[i][j]);

      } while(abs(matrizFormula[i][j]) > numVariaveis);
    }
    // printf("\n");
  }

  //alocacao da formula
  formula = criaFormula(numVariaveis, numClausulas);

  //adicao das clausulas
  for(int i = 0; i < numClausulas; i++){
    adicionaClausula(formula, i, matrizFormula[i], numVariaveis, tamanho_Clausula);
  }

  //liberacao da matriz da formula
  liberaMatrizFormula(matrizFormula, numClausulas);

  //print da formula
  printf("Formula:\n");
  imprimeFormula(formula, tamanho_Clausula);

  //alocacao do conjunto solucao
  conjuntoSolucao = (bool*) malloc(numVariaveis * sizeof(bool));
  
  //chamada da funcao solucao
  bool existeSolucao = solucionaFormula(formula, &conjuntoSolucao, tamanho_Clausula);
  
  //print do resultado
  if(!existeSolucao){
    printf("\nFormula insatisfazivel!\n");
  }
  else{
    char *varlist = malloc(numVariaveis * sizeof(char));
    printf("Valoracao:\n");

    getVarList(varlist, formula);

    for(int i = 0; i < numVariaveis; i++){
      printf("%c = %s\n", varlist[i], conjuntoSolucao[i] ? "True" : "False");
    }

    free(varlist);
  }

  //liberando alocacoes
  free(conjuntoSolucao);
  destroiFormula(formula);

  return 0;
}

//funcao para alocar matriz da formula
int **alocaMatrizFormula(int numClausulas, int numVariaveis){
  int **pt;
  pt = (int**) malloc(numClausulas * sizeof(int*));

  if(!pt)
    return NULL;
  
  for(int i = 0; i < numClausulas; i++){
    pt[i] = (int*) malloc(numVariaveis * sizeof(int));

    if(!pt[i]){
      for(int j = i-1; j >= 0; j--)
        free(pt[j]);
      free(pt);
      return NULL;
    }
  }
  return pt;
}

//funcao para liberar a matriz da formula alocada
void liberaMatrizFormula(int **var, int numClausulas){
  for(int i = 0; i < numClausulas; i++){
    free(var[i]);
  }
  free(var);
}
