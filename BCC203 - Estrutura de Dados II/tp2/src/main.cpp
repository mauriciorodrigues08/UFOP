#include <time.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>

#include "../include/intercalacao_b.h"
#include "../include/ordenacao_interna.h"
#include "../include/arquivo.h"
#include "../include/quicksort.h"
using namespace std;


void intercalacao1(FILE *arq, clock_t *inicio, int quant, int *qtdTransferenciasLeitura, int *qtdTransferenciasEscrita, int *qtdComparacoes);
void intercalacao2(FILE *arq, clock_t *inicio, int quant, int *qtdTransferenciasLeitura, int *qtdTransferenciasEscrita, int *qtdComparacoes);
void imprimirArquivo(const char *nomeArquivo);

int main(int argc, char* argv[]) {
    /* VARIÁVEIS AUXILIARES */
    FILE *arq = NULL;
    clock_t inicio, fim;
    int qtdTransfLeitura = 0;
    int qtdTransfEscrita = 0;
    int qtdComparacoes = 0;
    cout << fixed << setprecision(6); //para não imprimir em notacao cientifica

    /* VERIFICA SE FORAM PASSADOS OS ARGUMENTOS CORRETAMENTE */
    if (argc != 4  && argc != 5) {
        cout << "Erro! Execução inválida!\n" << endl;
        cout << "Modelos de execução:" << endl;
        cout << "./ordena <método> <quantidade> <situação>" << endl;
        cout << "./ordena <método> <quantidade> <situação> <[-P]>" << endl;
        return -1;
    }

    // caso tenha sido passado o número correto, atribui as variáveis
    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);

    if (quantidade <= 0 || quantidade > 471705) {
        cout << "Erro! Quantidade inválida!" << endl;
        cout << "A quantidade deve ser maior que 0 e menor que 471.705" << endl;
        return -1;
    }
    
    if (metodo < 1 || metodo > 3) {
        cout << "Erro! Método inválido! Deve ser 1, 2 ou 3" << endl;
        return -1;
    }

    if (situacao < 1 || situacao > 3) {
        cout << "Erro! Situação inválida! Deve ser 1, 2 ou 3." << endl;
        return -1;
    }

    /* PREPARA O ARQUIVO PARA ORDENAÇÃO */

    FILE *provaoOriginal = fopen("PROVAO.TXT", "r");
    if (provaoOriginal == NULL) {
        cout << "Erro! Arquivo PROVAO.TXT não encontrado." << endl;
        return -1;
    }

    // aloca vetor para guardar os registros
    Item *dados = new Item[quantidade];
    int i = 0;
    for(i = 0; i < quantidade; i++){
        if(!lerProximoAluno(provaoOriginal, &dados[i])){
            break;
        }
    }
    fclose (provaoOriginal);

    if(situacao == 1 || situacao == 2){
        MergeSort(dados, i, situacao);
    }

    // Os métodos 1 e 2 (intercalação) leem os registros em formato texto,
    // por meio de lerProximoAluno(). O método 3 (quicksort externo) opera
    // diretamente sobre structs Item em disco (fread/fwrite binários), então
    // precisa de um arquivo binário próprio, não do arquivo texto.
    const char *nomeArquivoOrdenacao = (metodo == 3) ? "teste.bin" : "teste.txt";

    if (metodo == 3) {
        FILE *arqBin = fopen("teste.bin", "wb+");
        if (arqBin == NULL) {
            cout << "Erro ao criar o arquivo binário de teste!" << endl;
            delete[] dados;
            return -1;
        }
        fwrite(dados, sizeof(Item), i, arqBin);
        fclose(arqBin);
    } else {
        FILE *arqTeste = fopen("teste.txt", "w");
        for (int j = 0; j < i; j++) {
            escreverAlunoTexto(arqTeste, dados[j]);
        }
        fclose(arqTeste);
    }
    delete[] dados;

    /* ORDENAÇÃO... */
    // Método 3 precisa de leitura E escrita binária ("rb+");
    // métodos 1 e 2 leem o arquivo texto ("r").
    arq = fopen(nomeArquivoOrdenacao, (metodo == 3) ? "rb+" : "r");
    if (arq == NULL) {
        cout << "Erro ao abrir o arquivo de teste!" << endl;
        return -1;
    }

    /* CHAMA O MÉTODO SELECIONADO */
    switch (metodo) {
        case 1:
            //intercalacao 1
            intercalacao1(arq, &inicio, quantidade, &qtdTransfLeitura, &qtdTransfEscrita, &qtdComparacoes);
            break;

        case 2:
            //intercalação 2
            intercalacao2(arq, &inicio, quantidade, &qtdTransfLeitura, &qtdTransfEscrita, &qtdComparacoes);
            break;
            
        case 3:
            //quick sort
            inicio = clock();
            quicksort(arq, quantidade, &qtdTransfLeitura, &qtdTransfEscrita, &qtdComparacoes);
            break;

        default:
            cout << "Erro! Método inválido!" << endl;
            return -1;
    }

    // pega o tempo final
    fim = clock();
    fclose(arq);

    // verifica se foi passada a flag opcional (-P)
    if (argc == 5 && strcmp(argv[4], "-P") == 0) {
        // Método 2 grava o resultado final em "ordenado.bin" (última fita
        // intercalada). Método 3 ordena "teste.bin" no próprio lugar.
        if (metodo == 1 || metodo == 2) {
            imprimirArquivo("fitas/ordenado.bin");
        } else if (metodo == 3) {
            imprimirArquivo("teste.bin");
        }
    }

    
    cout << "\n============= RESULTADOS OBTIDOS =============" << endl;
    cout << "Quantidade Total de Transferências Leitura: " << qtdTransfLeitura << endl;
    cout << "Quantidade Total de Transferências Escrita: " << qtdTransfEscrita << endl;
    cout << "Quantidade Total de Comparações: " << qtdComparacoes << endl;
    cout << "Tempo Total de Execução: " << ((double)(fim - inicio)) / CLOCKS_PER_SEC << " segundos" << endl;
    cout << "==============================================\n" << endl;

    return 0;
}


void intercalacao1(FILE *arq, clock_t *inicio, int quant, int *leituras, int *escritas, int *comparacoes) {
    *inicio = clock();
    FILE* fitas[FF];
    char nome[50];

    for (int i = 0; i < FF; i++) {
        sprintf(nome, "fitas/fita_%02d.bin", i);
        fitas[i] = fopen(nome, "wb+");

        if (fitas[i] == NULL) {
            cout << "Erro: Nao foi possivel abrir/criar o arquivo " << nome << endl;
            return;
        }
    }

    int n_blocos[FF] = {0};

    GeracaoBlocosOrdenados(arq, fitas, F, quant, n_blocos, leituras, escritas, comparacoes);
    intercalacao_balanceada(fitas, n_blocos, leituras, escritas, comparacoes);

    for (int i = 0; i < FF; i++) {
        fclose(fitas[i]);
    }
}

void intercalacao2(FILE *arq, clock_t *inicio, int quant, int *leituras, int *escritas, int *comparacoes) {
    *inicio = clock();
    FILE* fitas[FF];
    char nome[50];

    for (int i = 0; i < FF; i++) {
        sprintf(nome, "fitas/fita_%02d.bin", i);
        fitas[i] = fopen(nome, "wb+");

        if (fitas[i] == NULL) {
            cout << "Erro: Nao foi possivel abrir/criar o arquivo " << nome << endl;
            return;
        }
    }

    int n_blocos[FF] = {0};

    SelecaoSubstituicao(arq, fitas, F, quant, n_blocos, leituras, escritas, comparacoes);
    intercalacao_balanceada(fitas, n_blocos, leituras, escritas, comparacoes);
    
    for (int i = 0; i < FF; i++) {
        fclose(fitas[i]);
    }
}


void imprimirArquivo(const char *nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "rb");

    if (arq == NULL) {
        cout << nomeArquivo << " nao encontrado" << endl;
        return;
    }

    Item x;

    while (fread(&x, sizeof(Item), 1, arq) == 1) {
        cout << x.inscricao << " " << x.nota << endl;
    }

    fclose(arq);
}