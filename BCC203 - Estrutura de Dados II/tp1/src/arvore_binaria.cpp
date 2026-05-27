#include "../headers/arvore_binaria.h"
#include <iostream>
using namespace std;


void insereArvoreBinaria(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes) {
    if (!arq) return;

    //prepara o novo no que sera inserido como folha
    NoBinario novoNo;
    novoNo.reg = *reg;
    novoNo.esq = -1;
    novoNo.dir = -1;

    //posiciona no final do arquivo para verificar se esta vazio
    fseek(arq, 0, SEEK_END);
    if (ftell(arq) == 0) {
        //insere o no como raiz no início do arquivo
        fwrite(&novoNo, sizeof(NoBinario), 1, arq);
        (*qtdTransferencias)++;
        return;
    }

    int indiceAtual = 0;
    int indicePai = -1;
    NoBinario noLido;
    bool irParaEsquerda = false;

    //percorre a arvore procurando pela posicao de insercao
    while (indiceAtual != -1) {
        indicePai = indiceAtual;

        fseek(arq, indiceAtual * sizeof(NoBinario), SEEK_SET);
        fread(&noLido, sizeof(NoBinario), 1, arq);

        (*qtdTransferencias)++;
        (*qtdComparacoes)++;

        if (reg->chave < noLido.reg.chave) {
            irParaEsquerda = true;
            indiceAtual = noLido.esq;
        } else {
            irParaEsquerda = false;
            indiceAtual = noLido.dir;
        }
    }

    //posiciona no fim do arquivo
    fseek(arq, 0, SEEK_END);
    long posicaoFinal = ftell(arq);
    int novoIndice = (int)(posicaoFinal / sizeof(NoBinario));
    fwrite(&novoNo, sizeof(NoBinario), 1, arq);
    (*qtdTransferencias)++;

    //atualiza o ponteiro do no pai
    if (irParaEsquerda) {
        noLido.esq = novoIndice;
    } else {
        noLido.dir = novoIndice;
    }

    //sobrescreve o no pai com o ponteiro atualizado
    fseek(arq, indicePai * sizeof(NoBinario), SEEK_SET);
    fwrite(&noLido, sizeof(NoBinario), 1, arq);
    (*qtdTransferencias)++;
}

bool pesquisaArvoreBinaria(FILE *arquivo, int chaveBuscada, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes) {

    if (!arquivo) return false;

    int indiceAtual = 0; 
    NoBinario noLido;

    //percorre a arvore enquanto nao for um ponteiro nulo
    while (indiceAtual != -1) {
        
        //recupera o no atual do arquivo
        fseek(arquivo, indiceAtual * sizeof(NoBinario), SEEK_SET);

        //se der erro na leitura ou o arquivo acabar
        if (fread(&noLido, sizeof(NoBinario), 1, arquivo) != 1) {
            break;
        }
        
        (*qtdTransferencias)++;
        (*qtdComparacoes)++;

        //compara a chave buscada com a do no atual
        if (chaveBuscada == noLido.reg.chave) {
            //copia o registro inteiro para a variavel de retorno
            *regRetorno = noLido.reg; 
            return true;
        }

        //decide para qual lado descer
        (*qtdComparacoes)++; 
        if (chaveBuscada < noLido.reg.chave) {
            indiceAtual = noLido.esq;
        } else {
            indiceAtual = noLido.dir;
        }
    }

    //se o while terminar e chegar aqui, eh porque nao achou
    return false;
}

//imprime todas as chaves armazenadas na arvore binaria
void printArvoreBinaria(FILE *arq) {
    if (!arq) return;

    fseek(arq, 0, SEEK_SET);
    NoBinario no;
    int i = 0;

    while (fread(&no, sizeof(NoBinario), 1, arq) == 1) {
        cout << "Indice " << i++ << ": chave = " << no.reg.chave << endl;
    }
}