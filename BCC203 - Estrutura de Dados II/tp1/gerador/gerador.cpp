#include "gerador.h"
#include "../headers/registro.h"
#include "../headers/arvoreb.h"
#include "../headers/arvore_binaria.h"
#include "../headers/asi.h"
#include "../headers/arvore_b_estrela.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

#define ORDENACAO_CRESCENTE   1
#define ORDENACAO_DECRESCENTE 2
#define ORDENACAO_ALEATORIA   3

void geraDadosAleatorios(Registro *reg);
void shuffle(int *chaves, int numeroDeItens);

void geradorArvoreB(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes) {
    // verifica se foi passado um arquivo inválido
    if (!arq) return;

    /* CRIA UM VETOR DE CHAVES */
    int *chaves = (int*) malloc(numeroDeItens * sizeof(int));
    int k = 0;

    // verifica se é ordenação decrescente
    if (tipoDeOrdenacao == ORDENACAO_DECRESCENTE) {
        for (int i = numeroDeItens; i > 0; i--) chaves[i-1] = i;
    }
    // caso não for, gera o vetor normal
    else {
        for (int i = 1; i <= numeroDeItens; i++) chaves[i-1] = i;
    }

    // se for ordenação aleatória, chama a função shuffle
    if (tipoDeOrdenacao == ORDENACAO_ALEATORIA) shuffle(chaves, numeroDeItens);

    /* CRIA O PRIMEIRO REGISTRO*/
    Registro tempReg;
    tempReg.chave = chaves[k++];
    geraDadosAleatorios(&tempReg);

    /* CRIA A PRIMEIRA PAGINA */
    Pagina *tempPag = new Pagina();
    tempPag->n = 1;
    tempPag->r[0] = tempReg;
    for (int i=0; i < MM+1; i++) tempPag->p[i] = -1;

    /* ESCREVE A PRIMEIRA PAGINA NO ARQUIVO */
    fwrite(tempPag, sizeof(Pagina), 1, arq);

    /* CHAMA A FUNCAO INSERE PARA CADA NOVO REGISTRO GERADO */
    for (; k < numeroDeItens; k++) {
        tempReg.chave = chaves[k];
        geraDadosAleatorios(&tempReg);
        insereNaArvore(arq, &tempReg, qtdTransferencias, qtdComparacoes);
    }

    free(chaves);
    delete tempPag;
}

void geradorArvoreEstrela(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes) {
    // verifica se foi passado um arquivo inválido
    if (!arq) return;

    /* CRIA UM VETOR DE CHAVES */
    int *chaves = (int*) malloc(numeroDeItens * sizeof(int));
    int k = 0;

    // verifica se é ordenação decrescente
    if (tipoDeOrdenacao == ORDENACAO_DECRESCENTE) {
        for (int i = numeroDeItens; i > 0; i--) chaves[i-1] = i;
    }
    // caso não for, gera o vetor normal
    else {
        for (int i = 1; i <= numeroDeItens; i++) chaves[i-1] = i;
    }

    // se for ordenação aleatória, chama a função shuffle
    if (tipoDeOrdenacao == ORDENACAO_ALEATORIA) shuffle(chaves, numeroDeItens);

    /* CRIA O PRIMEIRO REGISTRO*/
    Registro tempReg;

    /* CHAMA A FUNCAO INSERE PARA CADA NOVO REGISTRO GERADO */
    for (; k < numeroDeItens; k++) {
        tempReg.chave = chaves[k];
        geraDadosAleatorios(&tempReg);
        insereArvoreB_estrela(arq, &tempReg, qtdTransferencias, qtdComparacoes);
    }

    free(chaves);
}

void geraDadosAleatorios(Registro *reg) {
    // gera o int para o dado 1
    reg->dado1 = (int) rand() % 10000 + 1;

    // gera a string para o dado 2
    char texto1[11];
    for (int i=0; i < 10; i++) {
        texto1[i] = 'a' + rand() % 26;
    }
    texto1[10] = '\0';

    strcpy(reg->dado2, texto1);
    
    // gera a string para o dado 3
    char texto2[21];
    for (int i=0; i < 20; i++) {
        texto2[i] = 'a' + rand() % 26;
    }
    texto2[20] = '\0';

    strcpy(reg->dado3, texto2);
}

void shuffle(int *chaves, int numeroDeItens) {
    for (int i = numeroDeItens - 1; i >= 0; i--) {
        int j = rand() % (i + 1);
        int temp = chaves[i];
        chaves[i] = chaves[j];
        chaves[j] = temp;
    }
}


void geradorArvoreBinaria(FILE *arq, int tipoDeOrdenacao, int numeroDeItens, int *qtdTransferencias, int *qtdComparacoes) {
    // verifica se foi passado um arquivo inválido
    if (!arq) return;

    /* CRIA UM VETOR DE CHAVES */
    int *chaves = (int*) malloc(numeroDeItens * sizeof(int));

    // verifica se é ordenação decrescente
    if (tipoDeOrdenacao == ORDENACAO_DECRESCENTE) {
        for (int i = numeroDeItens; i > 0; i--) chaves[i-1] = i;
    }
    // caso não for, gera o vetor normal
    else {
        for (int i = 1; i <= numeroDeItens; i++) chaves[i-1] = i;
    }

    // se for ordenação aleatória, chama a função shuffle
    if (tipoDeOrdenacao == ORDENACAO_ALEATORIA) shuffle(chaves, numeroDeItens);

    /* CHAMA A FUNCAO INSERE PARA CADA NOVO REGISTRO GERADO */
    Registro tempReg;
    for (int k = 0; k < numeroDeItens; k++) {
        tempReg.chave = chaves[k];
        geraDadosAleatorios(&tempReg);
        
        // insere na arvore binaria
        insereArvoreBinaria(arq, &tempReg, qtdTransferencias, qtdComparacoes);
    }

    free(chaves);
}

void geradorSequencial(FILE *arq, int tipoDeOrdenacao, int numeroDeItens,  int *qtdTransferencias, int *qtdComparacoes) {
    // verificacao
    if (!arq) return;

    // cria o vetor de chaves
    int *chaves = (int*)malloc(numeroDeItens * sizeof(int));

    if (!chaves) {
    printf("Erro ao alocar memória para as chaves.\n");
    return;
    }

    // gera chaves em ordem crescente
    for (int i = 1; i <= numeroDeItens; i++) {
    chaves[i - 1] = i;
    }

    // gera e escreve registros sequencialmente no arquivo
    Registro tempReg; 
    for (int i = 0; i < numeroDeItens; i++) {
        tempReg.chave = chaves[i];
        geraDadosAleatorios(&tempReg);

        // escreve o registro diretamente no arquivo
        fwrite(&tempReg, sizeof(Registro), 1, arq);
        (*qtdTransferencias)++;
    }
    // libera a memoria do vetor chaves
    free(chaves);

    // retorna o ponteiro no inicio do arquivo
    rewind(arq);
}