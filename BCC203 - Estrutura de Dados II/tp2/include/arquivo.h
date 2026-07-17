#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>         
#include "intercalacao_b.h" // Necessário para reconhecer a estrutura Item

// Formata a saída exatamente como o PROVAO.TXT
void escreverAlunoTexto(FILE *arquivo, Item &aluno);

// Funções do algoritmo MergeSort Interno
void merge(Item *v, int l, int m, int r, int situacao);
void mergeRec(Item *v, int l, int r, int situacao);
void MergeSort(Item *v, int n, int situacao);

#endif // ARQUIVO_H