#ifndef INTERCALACAO_B_H
#define INTERCALACAO_B_H

#include <stdio.h>

#define F 20
#define FF 40

struct Item {
    long int inscricao;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    
    bool marcado; // true = marcado para o próximo bloco
};

void RefazHeap(Item V[], int esq, int dir, int *comparacoes);
void ConstroiHeap(Item V[], int n, int *comparacoes);

bool lerProximoAluno(FILE *arquivo, Item *aluno);
void escreverAlunoNaFita(FILE *arquivo, Item *aluno);

void SelecaoSubstituicao(FILE *arqEntrada, FILE **arqSaida, int numFitasSaida, int quant, int n_blocos[], int *tranfLeitura, int *transfEscrita, int *comparacoes);
void intercalacao_balanceada(FILE **fitas, int n_blocos[], int *leituras, int *escritas, int *comparacoes);

#endif