#include "ordenacao_interna.h"

// FUNCAO DE ORDENACAO INTERNA

// ordena o bloco em memoria de forma ascendente por insercao direta
void OrdenacaoInterna(Item bloco[], int n, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Item atual = bloco[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            if (bloco[j].nota > atual.nota) {
                bloco[j + 1] = bloco[j];
                j--;
            } else {
                break;
            }
        }

        bloco[j + 1] = atual;
    }
}

// FUNCAO GERACAO DOS BLOCOS ORDENADOS

// le o arquivo de entrada em blocos de ate 20 registros, ordena cada bloco em
// memoria (OrdenacaoInterna) e distribui os blocos nas fitas de saida
void GeracaoBlocosOrdenados(FILE *arqEntrada, FILE **arqSaida, int numFitasSaida, int quant, int n_blocos[], int *tranfLeitura, int *transfEscrita, int *comparacoes) {
    Item bloco[20];

    int fitaAtual = 0;
    int totalLidos = 0;

    while (totalLidos < quant) {
        int n = 0;

        // preenche a memoria interna com ate 20 registros
        while (n < 20 && totalLidos < quant && lerProximoAluno(arqEntrada, &bloco[n])) {
            n++;
            totalLidos++;
            (*tranfLeitura)++;
        }

        if (n == 0) {
            break; // nao havia mais registros para ler
        }

        // ordena o bloco inteiro em memoria antes de gravar na fita
        OrdenacaoInterna(bloco, n, comparacoes);

        // grava o bloco ja ordenado na fita atual
        for (int i = 0; i < n; i++) {
            escreverAlunoNaFita(arqSaida[fitaAtual], &bloco[i]);
            (*transfEscrita)++;
        }

        n_blocos[fitaAtual]++;

        // avanca para a proxima fita de forma circular
        fitaAtual = (fitaAtual + 1) % numFitasSaida;
    }
}
