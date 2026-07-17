#include "../include/intercalacao_b.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ***FUNÇÕES HEAP***

void RefazHeap(Item V[], int esq, int dir, int *comparacoes){
    int i = esq;
    int j = i * 2 + 1; // indice do filho esquerdo
    Item aux = V[i];

    while (j <= dir){
        // verifica se tem filho direito e se ele tem prioridade
        if(j < dir){
            bool trocarPorDireita = false;

            if(V[j].marcado > V[j+1].marcado){ 
                trocarPorDireita = true;
            }
            else if (V[j].marcado == V[j+1].marcado){
                (*comparacoes)++;
                if(V[j].nota > V[j+1].nota){
                    trocarPorDireita = true;
                }
            }

            if(trocarPorDireita){
                j++; // olha o filho direito
            }
        }

        // compara o pai(aux) com o menor dos filhos
        bool paiMaior = false;
        if(aux.marcado > V[j].marcado){
            paiMaior = true;
        }
        else if(aux.marcado == V[j].marcado){
            (*comparacoes)++;
            if(aux.nota > V[j].nota)
                paiMaior = true;
        }

        // se pai for menor ou igual, a prioridade esta garantida
        if(!paiMaior){
            break;
        }

        // se o pai for maior, o filho sobe
        V[i] = V[j];
        i = j;
        j = i * 2 + 1;
    }

    V[i] = aux;
}

void ConstroiHeap(Item V[], int n, int *comparacoes){
    // o ultimo no pai é (n/2) - 1
    for (int esq = (n/2) - 1; esq >= 0; esq--){
        RefazHeap(V, esq, n-1, comparacoes);
    }
}

// ***FUNÇÕES LEITURA E ESCRITA***

bool lerProximoAluno(FILE *arquivo, Item *aluno){
    char linha[150];
    char buffer[55];

    if(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(strlen(linha) < 99){
            return false;
        }

        strncpy(buffer, linha, 8);
        buffer[8] = '\0';
        aluno->inscricao = atol(buffer);

        strncpy(buffer, linha + 9, 5);
        buffer[5] = '\0';
        aluno->nota = atof(buffer);

        strncpy(aluno->estado, linha + 15, 2);
        aluno->estado[2] = '\0';

        strncpy(aluno->cidade, linha + 18, 50);
        aluno->cidade[50] = '\0';

        strncpy(aluno->curso, linha + 69, 30);
        aluno->curso[30] = '\0';

        // remove possivel \n de curso
        int tam = strlen(aluno->curso);
        while(tam > 0 && (aluno->curso[tam-1] == '\n')) {
            aluno->curso[tam-1] = '\0';
            tam--;
        }

        return true;
    }

    return false; // fim do arquivo
}

void escreverAlunoNaFita(FILE *arquivo, Item *aluno){
    fwrite(aluno, sizeof(Item), 1, arquivo);
}

// ***FUNÇÕES SELEÇÃO POR SUBSTITUIÇÃO***

void SelecaoSubstituicao(FILE *arqEntrada, FILE **arqSaida, int numFitasSaida, int quant, int n_blocos[], int *tranfLeitura, int *transfEscrita, int *comparacoes){
    Item V[20];

    int n = 0;
    int fitaAtual = 0;
    n_blocos[0] = 1;
    int totalLidos = 0;

    // construcao do heap
    while(n < 20 && totalLidos < quant && lerProximoAluno(arqEntrada, &V[n])){
        V[n].marcado = false;
        n++;
        totalLidos++;
        (*tranfLeitura)++;
    }
    ConstroiHeap(V, n, comparacoes);

    // distribuicao nas fitas
    while (n > 0){
        // se todos estiverem marcados, troca de fita
        if(V[0].marcado == true){
            fitaAtual = (fitaAtual + 1) % numFitasSaida;
            n_blocos[fitaAtual]++;
            for(int i = 0; i < n; i++){
                V[i].marcado = false;
            }
            ConstroiHeap(V, n, comparacoes);
        }

        // grava na fita
        escreverAlunoNaFita(arqSaida[fitaAtual], &V[0]);
        (*transfEscrita)++;

        float notaGravada = V[0].nota;
        Item novoAluno;

        // substituicao
        if(totalLidos < quant && lerProximoAluno(arqEntrada, &novoAluno)){
            totalLidos++;
            (*tranfLeitura)++;
            
            (*comparacoes)++;
            if(novoAluno.nota < notaGravada){
                novoAluno.marcado = true;
            }else{
                novoAluno.marcado = false;
            }

            V[0] = novoAluno; // insere na raiz

        }else{
            V[0] = V[n - 1]; // atingiu a quantidade, diminui o heap
            n--;
        }

        if(n > 0){
            RefazHeap(V, 0, n - 1, comparacoes); // reestruturacao do heap
        }
    }
}


// Funcao auxiliar para verificar se o arquivo ja esta totalmente ordenado
// Retorna -1 se ainda houver 2 ou mais fitas com blocos (precisa de mais intercalacao)
// Retorna o indice da fita se restar apenas UMA fita com blocos (arquivo ordenado)
int restaUmaFitaPreenchida(int nBlocos[], int n, int inicio) {
    int preenchida = -1;
    for (int i = 0; i < n; i++) {
        if (nBlocos[inicio + i] > 0) {
            if (preenchida == -1) {
                preenchida = i; // encontrou a primeira fita com dados
            } else {
                return -1; // mais de uma fita tem blocos
            }
        }
    }
    if (preenchida == -1) return -1;
    else return inicio + preenchida;
}


// Funcao principal da intercalacao balanceada de varios caminhos
// Realiza o merge dos blocos ordenados gerados pela etapa de selecao por substituicao
void intercalacao_balanceada(FILE **fitas, int n_blocos[], int *leituras, int *escritas, int *comparacoes) {
    // grupoEntrada define qual metade das fitas é leitura e qual é escrita
    // 0: le das fitas 0 a F-1, Escreve nas fitas F a 2F-1
    // 1: le das fitas F a 2F-1, Escreve nas fitas 0 a F-1
    short grupoEntrada = 0;

    // loop continua ate que reste apenas 1 fita preenchida no grupo de entrada
    while (restaUmaFitaPreenchida(n_blocos, F, grupoEntrada * F) == -1) {
        int entradaInicio = grupoEntrada * F;
        int saidaInicio = (1 - grupoEntrada) * F;

        // limpa saida
        for (int i = 0; i < F; i++) {
            rewind(fitas[saidaInicio + i]);
            if (ftruncate(fileno(fitas[saidaInicio + i]), 0) != 0) {
                perror("Erro ao truncar arquivo de fita");
            }
            n_blocos[saidaInicio + i] = 0;
        }

        // reposiciona os ponteiros das fitas de entrada para o inicio do arquivo
        for (int i = 0; i < F; i++) {
            rewind(fitas[entradaInicio + i]);
        }

        // controla em qual fita de saida o bloco atual sera gravado
        int fitaSaida = saidaInicio;
        int blocosRestantes[F];

        // Copia a quantidade de blocos de cada fita de entrada para controle local
        memcpy(blocosRestantes, &n_blocos[entradaInicio], sizeof(int) * F);

        bool continuar = true;

        // Loop para processar e mesclar todos os blocos disponiveis nesta passada
        while (continuar) {
            Item memoria[F];
            short ativa[F];
            continuar = false;

            // Carrega o primeiro registro de cada fita de entrada para iniciar o merge do bloco
            for (int i = 0; i < F; i++) {
                if (blocosRestantes[i] > 0) {
                    if (fread(&memoria[i], sizeof(Item), 1, fitas[entradaInicio + i])) {
                        ativa[i] = 1;
                        (*leituras)++;
                        continuar = true;
                    } else {
                        ativa[i] = -1;
                    }
                } else {
                    ativa[i] = -1;
                }
            }

            // Se nenhuma fita tinha dados, encerra a passada
            if (!continuar) break;

            n_blocos[fitaSaida]++;

            // Cconstroi um bloco na fita de saida intercalando os registros das fitas de entrada
            while (true) {
                int menor = -1;

                // encontra o registro com a MENOR nota entre todas as fitas ativas
                for (int i = 0; i < F; i++) {
                    if (ativa[i] != -1) {
                        (*comparacoes)++;
                        if (menor == -1 || memoria[i].nota < memoria[menor].nota) {
                            menor = i;
                        }
                    }
                }

                // Se nao ha mais fitas ativas para este bloco, sai do laço
                if (menor == -1) break;

                // Grava o menor registro encontrado na fita de saida atual
                fwrite(&memoria[menor], sizeof(Item), 1, fitas[fitaSaida]);
                (*escritas)++;

                Item novo;

                // le o proximo registro da fita de onde o menor valor acabou de sair
                if (fread(&novo, sizeof(Item), 1, fitas[entradaInicio + menor])) {
                    (*leituras)++;

                    // quebra de bloco: Verifica se o novo registro pertence ao proximo bloco
                    // se for menor que o recem-gravado, a ordem quebrou
                    if (novo.nota < memoria[menor].nota) {
                        ativa[menor] = -1;
                        fseek(fitas[entradaInicio + menor], -sizeof(Item), SEEK_CUR);
                    } else {
                        memoria[menor] = novo;
                    }
                } else {
                    ativa[menor] = -1;
                    blocosRestantes[menor]--;
                }
            }

            // Alterna a fita de saida de forma circular para o proximo bloco gerado
            fitaSaida = (fitaSaida + 1 - saidaInicio) % F + saidaInicio;
        }

        // Alterna os grupos (quem era saida vira entrada e vice-versa) para a proxima passada
        grupoEntrada = 1 - grupoEntrada;
    }

    // Identifica qual fita possui o arquivo finalizado em um unico bloco
    int final = restaUmaFitaPreenchida(n_blocos, F, grupoEntrada * F);

    // Se encontrou a fita com o resultado final, copia para "ordenado.bin"
    if (final != -1) {
        rewind(fitas[final]);
        FILE* out = fopen("fitas/ordenado.bin", "wb");

        Item x;
        while (fread(&x, sizeof(Item), 1, fitas[final])) {
            fwrite(&x, sizeof(Item), 1, out);
        }

        fclose(out);
    }
}