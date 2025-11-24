//imports
#include "formula.h"
#include "clausula.h"

//structs
struct Formula{
  Clausula ***clausulas;
  int numClausulas;
  int numVariaveis;
  char *listaDeVariaveis;
};

//prototipos das funcoes locais
Clausula ***utilMallocClausulas(int numVariaveis, int numClausulas);
bool solucaoFormula(Formula *formula, bool **conjuntoSolucao, int varIndex, int tamClausula);
bool testaFormula(bool *conjuntoSolucao, Formula *f, int tamClausula);

//implementacoes das funcoes relacionadas a formulas

//funcao que aloca uma nova formula
Formula *criaFormula(int numVariaveis, int numClausulas){
  Formula *pt;
  pt = (Formula *) malloc(sizeof(Formula));

  pt->numClausulas =  numClausulas;
  pt->numVariaveis = numVariaveis;

  pt->listaDeVariaveis = (char*) calloc(numVariaveis, sizeof(char));

  pt->clausulas = utilMallocClausulas(pt->numVariaveis, pt->numClausulas);

  return pt;
}

//funcao que libera uma formula alocada
void destroiFormula(Formula *formula){
  for(int i = 0; i < formula->numClausulas; i++){
    *(formula->clausulas[i]) = destroiClausula(*(formula->clausulas[i]));
  }
  for(int i = 0; i < formula->numClausulas; i++){
    free(formula->clausulas[i]);
  }
  free(formula->clausulas);
  free(formula->listaDeVariaveis);


  free(formula);
}

//funcao que adiciona uma nova clausula na formula
void adicionaClausula(Formula *formula, int index, int *var, int numVariaveis, int tamanhoClausula){
  *(formula->clausulas[index]) = criaClausula(var, tamanhoClausula);

  bool novaVariavel;

  for(int i = 0; i < tamanhoClausula; i++){
    novaVariavel = true;
    for(int j = 0; (j < numVariaveis) && novaVariavel; j++){
      if(abs(var[i]) + 96 == formula->listaDeVariaveis[j])
        novaVariavel = false;
    }
    if(novaVariavel)
      formula->listaDeVariaveis[abs(var[i])-1] = abs(var[i]) + 96;
  }

}

//funcao que pega uma lista de variaveis e atribui a um vetor
void getVarList(char *listaVar, Formula *formula){
  for(int i = 0; i < formula->numVariaveis; i++){
    listaVar[i] = formula->listaDeVariaveis[i];
  }
}

//funcao que imprime a formula no terminal
void imprimeFormula(Formula *formula, int tamClausula){
  int tempC;;
  tempC = formula->numClausulas;

  for(int i = 0; i < tempC; i++){
    tostringClausula(*(formula->clausulas[i]), tamClausula);
    if(i < tempC - 1)
      printf(" ∧ ");
    else
      printf("\n");
  }
}

// função wrapper que inicia o processo de solução com backtracking.
bool solucionaFormula(Formula *formula, bool **conjuntoSolucao, int tamClausula){
  // inicia a busca pela primeira variável (índice 0)
  const int varInicial = 0; 
  int n = formula->numVariaveis;

  // inicializa o conjunto solução com TRUE
  for(int i = 0; i < n; i++) {
    (*conjuntoSolucao)[i] = true;
  }
  
  // chama a funcao de backtracking
  return solucaoFormula(formula, conjuntoSolucao, varInicial, tamClausula);
}

// função recursiva que procura a solução para a fórmula usando Backtracking
bool solucaoFormula(Formula *formula, bool **conjuntoSolucao, int varIndex, int tamClausula) {
  int n = formula->numVariaveis;
  
  // caso base: todas as variáveis foram valoradas
  if (varIndex == n) {
    // testa se a valoração atual satisfaz a fórmula
    return testaFormula(*conjuntoSolucao, formula, tamClausula);
  }


  // variavel atual passa a ser TRUE
  (*conjuntoSolucao)[varIndex] = true;
  
  // chama a recursão para a próxima variável
  if (solucaoFormula(formula, conjuntoSolucao, varIndex + 1, tamClausula)) {
    return true; // se encontrou a solução, retorna e para a busca
  }
  
  // variável atual passa a ser FALSE
  (*conjuntoSolucao)[varIndex] = false;
  
  // chama a recursão para a próxima variável
  if (solucaoFormula(formula, conjuntoSolucao, varIndex + 1, tamClausula)) {
    return true; // se encontrou a solução, retorna e para a busca
  }
  
  // se nem TRUE nem FALSE levaram a uma solução no subproblema, retorna FALSE
  return false;
}

//funcao que testa se a formula foi satisfeita
bool testaFormula(bool *conjuntoSolucao, Formula *formula, int tamClausula){
  bool result;

  int *clausula = (int*) malloc(tamClausula * sizeof(int));
  int *posvariaveis = (int*) malloc(tamClausula * sizeof(int));

  for(int i = 0; i < formula->numClausulas; i++){
    retornaValoresDaClausula(*(formula->clausulas[i]), tamClausula, &clausula);

    for(int j = 0; j < tamClausula; j++){
      posvariaveis[j] = abs(clausula[j]) - 1;
    }

    result = testaClausula(clausula, posvariaveis, conjuntoSolucao, tamClausula);
    if(!result){
      free(posvariaveis);
      free(clausula);
      return result;
    }
  }

  free(posvariaveis);
  free(clausula);
  return true;
}

//funcao para alocar clausula
Clausula ***utilMallocClausulas(int numVariaveis, int numClausulas){
  Clausula ***auxAlloc = (Clausula***) malloc(numClausulas * sizeof(Clausula**)); //alocacao auxiliar que sera retornada

  if(!auxAlloc){
    return NULL;
  }

  for(int i = 0; i < numClausulas; i++){
    auxAlloc[i] = (Clausula**) malloc(numVariaveis * sizeof(Clausula*));
    
    if(!auxAlloc[i]){
      for(int j = i - 1; j >= 0; j--){
        free(auxAlloc[j]);
      }
      free(auxAlloc);
      return NULL;
    }
  }

  return auxAlloc; 
}
