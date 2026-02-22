#ifndef FILAPROCESSOS_H
#define FILAPROCESSOS_H

//imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//defines
#define MAX_NOME 15
#define MAX_CONTEUDO 9

//structs
typedef struct Variavel{
  char nome[MAX_NOME];
  char conteudo[MAX_CONTEUDO];
} Variavel;

typedef struct erro {
  int tipo; //tipo de erro
  char mensagemErro[50]; 
} Erro;

typedef struct Pilha Pilha;
typedef struct No No;
typedef No *Arvore;

//prototipos das funcoes
Pilha *criarPilha(); //inicializa uma pilha
bool adicionaPilha(Pilha *pilha); //adiciona um escopo vazio a pilha
bool desempilha(Pilha *pilha, Arvore **raiz); //libera o topo da pilha
Arvore *getTopo(Pilha *pilha); //retorna o escopo no topo da pilha (sem liberar o mesmo)
Pilha *destroiPilha(Pilha *pilha); //libera uma pilha

bool buscaEmEscopos(Pilha *pilha, char *chave, Variavel *var); //busca binaria pela chave no escopo atual e nos anteriores 
Arvore *criarEscopo(); //inicializa uma arvore
bool adicionaVar(Arvore *raiz, Variavel *var); //adiciona uma variavel na arvore binaria
Arvore *destroiEscopo(Arvore *raiz); //libera a arvore
bool arvoreBusca(Arvore *raiz, char *chave, Variavel *var); //busca binaria pela chave

void executar(Pilha *pilha, Erro *erro); //executa o programa

#endif