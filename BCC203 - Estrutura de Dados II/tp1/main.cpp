#include "gerador/gerador.h"
#include "headers/asi.h"
#include "headers/arvoreb.h"
#include "headers/arvore_binaria.h"
#include "headers/arvore_b_estrela.h"
#include <time.h>
#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

void busca_sequencial(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes);
void busca_arvoreBinaria(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes);
void busca_arvoreB(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes);
void busca_arvoreEstrela(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes);

int main(int argc, char* argv[]) {
    /* VARIÁVEIS AUXILIARES */
    FILE *arq;
    clock_t inicio, fim;
    int qtdTransferencias = 0;
    int qtdComparacoes = 0;

    /* VERIFICA SE FORAM PASSADOS OS ARGUMENTOS CORRETAMENTE */
    // verifica a quantidade de argumentos
    if (argc != 5 && argc != 6) {
        cout << "Erro! Execução inválida!\n" << endl;
        cout << "Modelos de execução:" << endl;
        cout << "./pesquisa <método> <quantidade> <situação> <chave>" << endl;
        cout << "./pesquisa <método> <quantidade> <situação> <chave> <[-P]>" << endl;
        
        return -1;
    }

    // caso tenha sido passado o número correto, atribui as variáveis
    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int chave = atoi(argv[4]);

    // verifica a quantidade de registros
    if (quantidade <= 0 || quantidade > 1000000) {
        cout << "Erro! Quantidade inválida!" << endl;
        cout << "A quantidade deve ser maior que 0 e menor que 1.000.000" << endl;

        return -1;
    }
    
    // verifica se o método é válido
    if (metodo < 1 || metodo > 4) {
        cout << "Erro! Método inválido! Deve ser um número entre 1 e 4." << endl;
        return -1;
    }

    // verifica se a situação é válida
    if (situacao < 1 || situacao > 3) {
        cout << "Erro! Situação inválida! Deve ser 1, 2 ou 3." << endl;
        return -1;
    }



    /* CRIA A VARIÁVEL DE RETORNO */
    Registro regRetorno;
    regRetorno.chave = -1;

    srand(time(NULL));
    cout << fixed << setprecision(6);

    /* CHAMA O MÉTODO SELECIONADO */
    switch (metodo) {
        case 1:
            // o ASI requer arquivo ordenado crescentemente
            if (situacao != 1) {
                cout << "Erro: o método de Acesso Sequencial Indexado requer arquivos ordenados crescentemente." << endl;
                return 1;
            }
            
            // chama a busca sequencial
            arq = fopen("arq_sequencial.dat", "wb+"); //Cria e abre o arquivo limpo
            
            busca_sequencial(arq, &inicio, situacao, quantidade, chave, &regRetorno, &qtdTransferencias, &qtdComparacoes);
            break;

        case 2:
            //chama a arvore binaria
            arq = fopen("arq_arvoreBinaria.dat", "wb+"); //Cria e abre o arquivo limpo
            
            busca_arvoreBinaria(arq, &inicio, situacao, quantidade, chave, &regRetorno, &qtdTransferencias, &qtdComparacoes);
            break;
            
        case 3:
            // chama a arvore b
            arq = fopen("arq_arvoreB.dat", "wb+");

            busca_arvoreB(arq, &inicio, situacao, quantidade, chave, &regRetorno, &qtdTransferencias, &qtdComparacoes);
            break;

        case 4:
            // chama a arvore b*
            arq = fopen("arq_arvore_estrela.dat", "wb+");

            busca_arvoreEstrela(arq, &inicio, situacao, quantidade, chave, &regRetorno, &qtdTransferencias, &qtdComparacoes);
            break;

        default:
            cout << "Erro! Método inválido!" << endl;
            return -1;
    }

    // pega o tempo final
    fim = clock();
    
    
    // verifica se foi passada a flag opcional (-P)
    if (argc == 6 && strcmp(argv[5], "-P") == 0) {
        cout << "Arquivos Considerados:" << endl;

        // Para ASI (metodo 1)
        if (metodo == 1) {
            // salva a posicao atual do ponteiro
            long posicaoAtual = ftell(arq);

            // volta ao inicio do arquivo
            rewind(arq);
            Registro reg;
            int count = 0;
            cout << "Chaves presentes no arquivo:" << endl;

            while (fread(&reg, sizeof(Registro), 1, arq) == 1) {
                cout << reg.chave;
                count++;
                if (count % 20 == 0) {
                    cout << endl; // quebra de linha a cada 20 chaves
                } else {
                    cout << " ";
                }
            }
            cout << "\n\nTotal de registros: " << count << endl;

            // volta para posicao original do ponteiro
            fseek(arq, posicaoAtual, SEEK_SET);
        }
        // para arvore binaria (matodo 2)
        else if (metodo == 2) {
            printArvoreBinaria(arq);
        }
        // para arvore b (metodo 3)
        else if (metodo == 3) {
            printArvore(arq, &qtdTransferencias);
        }
        // para arvore b* (metodo 4)
        else if (metodo == 4) {
            printArvoreB_estrela(arq, &qtdTransferencias);
        }
    }
    fclose(arq);

    /* MOSTRA OS DADOS RETORNADOS E RESULTADOS */
    if (chave != -1) {
        if (regRetorno.chave != -1) {
            cout << "Arquivo encontrado:" << endl;
            cout << "  Chave: " << regRetorno.chave << endl;
            cout << "  Dado 1: " << regRetorno.dado1 << endl;
            cout << "  Dado 2: " << regRetorno.dado2 << endl;
            cout << "  Dado 3: " << regRetorno.dado3 << endl;
        } else {
            cout << "Chave não encontrada!" << endl;
        }

        cout << "\n============= RESULTADOS OBTIDOS =============" << endl;
        cout << "Quantidade Total de Transferências: " << qtdTransferencias << endl;
        cout << "Quantidade Total de Comparações: " << qtdComparacoes << endl;
        cout << "Tempo Total de Execução: " << ((double)(fim - inicio)) / CLOCKS_PER_SEC << " segundos" << endl;
        cout << "==============================================\n" << endl;
    } 
    else {
        cout << "\n============= MÉDIAS OBTIDAS (10 BUSCAS) =============" << endl;
        cout << "Media de Transferencias: " << qtdTransferencias << endl;
        cout << "Media de Comparacoes: " << qtdComparacoes << endl;
        cout << "Tempo Medio de Execucao: " << ((double)(fim - inicio)) / CLOCKS_PER_SEC << " segundos" << endl;
        cout << "======================================================\n" << endl;
    }

    return 0;
}


void busca_sequencial(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes){
    // CHAMA O GERADOR 
    int qtdTransfCriacao = 0, qtdCompCriacao = 0;
    geradorSequencial(arq, tipoDeOrdenacao, quant, &qtdTransfCriacao, &qtdCompCriacao);
    TipoIndice tabela[MAXTABELA];
    int tamanhoTabela = criaTabelaIndice(arq, tabela, &qtdTransfCriacao);

    cout << "--- Criação ---" << endl;
    cout << "Transferências: " << qtdTransfCriacao << endl;
    cout << "Comparações: " << qtdCompCriacao << endl;

    if (chave != -1) {
        *inicio = clock(); // cronômetro só da pesquisa
        
        /* CHAMA A PESQUISA ASI */
        if (!pesquisaASI(arq, tabela, tamanhoTabela, chave, regRetorno, qtdTransferencias, qtdComparacoes)) {
            regRetorno->chave = -1;
        }
    } 
    else {
        cout << "\n--- MODO AUTOMATICO: PROCESSANDO 10 BUSCAS (ASI) ---" << endl;
        long totalTransf = 0, totalComp = 0;
        double totalTempo = 0.0;

        for (int i = 0; i < 10; i++) {
            int chaveAleatoria = (rand() % quant) + 1;
            int transfAtual = 0, compAtual = 0;
            Registro regAtual;
            
            clock_t t_inicio = clock();
            pesquisaASI(arq, tabela, tamanhoTabela, chaveAleatoria, &regAtual, &transfAtual, &compAtual);
            clock_t t_fim = clock();
            
            double tempoAtual = ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC;

            cout << "Busca " << (i + 1) << " (Chave " << chaveAleatoria << ") -> "
                 << "Transf: " << transfAtual << " | Comp: " << compAtual << " | Tempo: " << tempoAtual << " s" << endl;
            
            totalTransf += transfAtual;
            totalComp += compAtual;
            totalTempo += tempoAtual;
        }

        *qtdTransferencias = totalTransf / 10;
        *qtdComparacoes = totalComp / 10;
        *inicio = clock() - (clock_t)((totalTempo / 10.0) * CLOCKS_PER_SEC);
    }
}


void busca_arvoreB(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes) {
    /* CHAMA O GERADOR */
    int qtdTransfCriacao = 0, qtdCompCriacao = 0;
    geradorArvoreB(arq, tipoDeOrdenacao, quant, &qtdTransfCriacao, &qtdCompCriacao);
    
    cout << "--- Criação ---" << endl;
    cout << "Transferências: " << qtdTransfCriacao << endl;
    cout << "Comparações: " << qtdCompCriacao << endl;

    if (chave != -1) {
        *inicio = clock(); // cronômetro só da pesquisa

        /* CHAMA A PESQUISA DA ARVORE B */
        if (!pesquisaChave(arq, chave, regRetorno, qtdTransferencias, qtdComparacoes)) {
            regRetorno->chave = -1;
        }
    } 
    else {
        cout << "\n--- MODO AUTOMATICO: PROCESSANDO 10 BUSCAS (ARVORE B) ---" << endl;
        long totalTransf = 0, totalComp = 0;
        double totalTempo = 0.0;

        for (int i = 0; i < 10; i++) {
            int chaveAleatoria = (rand() % quant) + 1;
            int transfAtual = 0, compAtual = 0;
            Registro regAtual;
            
            clock_t t_inicio = clock();
            pesquisaChave(arq, chaveAleatoria, &regAtual, &transfAtual, &compAtual);
            clock_t t_fim = clock();
            
            double tempoAtual = ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC;

            cout << "Busca " << (i + 1) << " (Chave " << chaveAleatoria << ") -> "
                 << "Transf: " << transfAtual << " | Comp: " << compAtual << " | Tempo: " << tempoAtual << " s" << endl;
            
            totalTransf += transfAtual;
            totalComp += compAtual;
            totalTempo += tempoAtual;
        }

        *qtdTransferencias = totalTransf / 10;
        *qtdComparacoes = totalComp / 10;
        *inicio = clock() - (clock_t)((totalTempo / 10.0) * CLOCKS_PER_SEC);
    }
}


void busca_arvoreBinaria(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes) {
    int qtdTransfCriacao = 0, qtdCompCriacao = 0;

    // fase de criação usa contadores próprios
    geradorArvoreBinaria(arq, tipoDeOrdenacao, quant, &qtdTransfCriacao, &qtdCompCriacao);

    cout << "--- Criação ---" << endl;
    cout << "Transferências: " << qtdTransfCriacao << endl;
    cout << "Comparações: " << qtdCompCriacao << endl;

    if (chave != -1) {
        *inicio = clock(); // cronômetro só da pesquisa

        // fase de pesquisa usa os contadores originais
        if (!pesquisaArvoreBinaria(arq, chave, regRetorno, qtdTransferencias, qtdComparacoes)) {
            regRetorno->chave = -1;
        }
    } 
    else {
        cout << "\n--- MODO AUTOMATICO: PROCESSANDO 10 BUSCAS (ARVORE BINARIA) ---" << endl;
        long totalTransf = 0, totalComp = 0;
        double totalTempo = 0.0;

        for (int i = 0; i < 10; i++) {
            int chaveAleatoria = (rand() % quant) + 1;
            int transfAtual = 0, compAtual = 0;
            Registro regAtual;
            
            clock_t t_inicio = clock();
            pesquisaArvoreBinaria(arq, chaveAleatoria, &regAtual, &transfAtual, &compAtual);
            clock_t t_fim = clock();
            
            double tempoAtual = ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC;

            cout << "Busca " << (i + 1) << " (Chave " << chaveAleatoria << ") -> "
                 << "Transf: " << transfAtual << " | Comp: " << compAtual << " | Tempo: " << tempoAtual << " s" << endl;
            
            totalTransf += transfAtual;
            totalComp += compAtual;
            totalTempo += tempoAtual;
        }

        *qtdTransferencias = totalTransf / 10;
        *qtdComparacoes = totalComp / 10;
        *inicio = clock() - (clock_t)((totalTempo / 10.0) * CLOCKS_PER_SEC);
    }
}

void busca_arvoreEstrela(FILE *arq, clock_t *inicio, int tipoDeOrdenacao, int quant, int chave, Registro *regRetorno, int *qtdTransferencias, int *qtdComparacoes){    
    /* CHAMA O GERADOR */
    int qtdTransfCriacao = 0, qtdCompCriacao = 0;
    geradorArvoreEstrela(arq, tipoDeOrdenacao, quant, &qtdTransfCriacao, &qtdCompCriacao);
    
    cout << "--- Criação ---" << endl;
    cout << "Transferências: " << qtdTransfCriacao << endl;
    cout << "Comparações: " << qtdCompCriacao << endl;

    if (chave != -1) {
        *inicio = clock(); // cronômetro só da pesquisa

        /* CHAMA A PESQUISA DA ARVORE B* */
        if (!pesquisarChaveB_estrela(arq, chave, regRetorno, qtdTransferencias, qtdComparacoes)) {
            regRetorno->chave = -1;
        }
    } 
    else {
        cout << "\n--- MODO AUTOMATICO: PROCESSANDO 10 BUSCAS (ARVORE B*) ---" << endl;
        long totalTransf = 0, totalComp = 0;
        double totalTempo = 0.0;

        for (int i = 0; i < 10; i++) {
            int chaveAleatoria = (rand() % quant) + 1;
            int transfAtual = 0, compAtual = 0;
            Registro regAtual;
            
            clock_t t_inicio = clock();
            pesquisarChaveB_estrela(arq, chaveAleatoria, &regAtual, &transfAtual, &compAtual);
            clock_t t_fim = clock();
            
            double tempoAtual = ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC;

            cout << "Busca " << (i + 1) << " (Chave " << chaveAleatoria << ") -> "
                 << "Transf: " << transfAtual << " | Comp: " << compAtual << " | Tempo: " << tempoAtual << " s" << endl;
            
            totalTransf += transfAtual;
            totalComp += compAtual;
            totalTempo += tempoAtual;
        }

        *qtdTransferencias = totalTransf / 10;
        *qtdComparacoes = totalComp / 10;
        *inicio = clock() - (clock_t)((totalTempo / 10.0) * CLOCKS_PER_SEC);
    }
}