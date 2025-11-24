//imports
#include "clausula.h"

//structs
struct Clausula{
  int *variaveis;
};

//implementacoes das funcoes relacionadas a clausulas

//funcao que aloca uma nova clausula
Clausula *criaClausula(int *variaveis, int numVariaveis){
  Clausula *pt;
  pt = (Clausula *) malloc(sizeof(Clausula));

  if(!pt)
    return NULL;
  
  pt->variaveis = (int*) malloc(numVariaveis * sizeof(int));

  if(!pt->variaveis){
    free(pt);
    return NULL;
  }

  for(int i = 0; i < numVariaveis; i++){
    pt->variaveis[i] = variaveis[i];
  }

  return pt;
}

//funcao que libera uma clausula alocada
Clausula *destroiClausula(Clausula *clausula){
  free(clausula->variaveis);
  free(clausula);
  return NULL;
}

//funcao que transforma a clausula em uma string
void tostringClausula(Clausula *clausula, int numVariaveis){  
  printf("(");
  for(int i = 0; i < numVariaveis; i++){
    //soma 96 ao valor devido a tabela ASCII
    printf("%c%c%s", clausula->variaveis[i] < 0? '~': 0, abs(clausula->variaveis[i]) + 96, i == numVariaveis - 1? "\0":" ∨ ");
  }
  printf(")");
}

//funcao que faz o teste da clausula atual
bool testaClausula(int *variaveisUsadas, int *posicoesDasVariaveis, bool *conjuntoSolucao, int tam){
  bool result = false;

  for(int i = 0; i < tam; i++){
    if(variaveisUsadas[i] < 0) {
      result = result || (!conjuntoSolucao[posicoesDasVariaveis[i]]);
    }
    else {
      result = result || conjuntoSolucao[posicoesDasVariaveis[i]];
    }

    if(result)  {
      return true;
    }
  }
  
  return result;
}

//altera o vetor com os valores das variaveis
void retornaValoresDaClausula(Clausula *clausula, int tamClausula, int **vec) {
  for (int i = 0; i < tamClausula; i++) {
    (*vec)[i] = clausula->variaveis[i];
  }
}
