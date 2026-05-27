#include "../headers/asi.h"

int criaTabelaIndice(FILE* arq, TipoIndice tabela[], int* transferencias) {
    Registro reg;
    int tamanhoTabela = 0;
    int posicaoPagina = 0;

    // garante que o ponteiro esteja no inicio do arquivo
    rewind(arq);

    // LE PRIMEIRO REGISTRO DE CADA PAGINA
    while (fread(&reg, sizeof(Registro), 1, arq) == 1) {
        (*transferencias)++;
        
        tabela[tamanhoTabela].chave = reg.chave;
        tabela[tamanhoTabela].posicao = posicaoPagina;
        tamanhoTabela++;

        // pula ITENSPAGINA - 1 pq ja lemos o primeiro item da pagina
        fseek(arq, (ITENSPAGINA - 1) * sizeof(Registro), SEEK_CUR);
        posicaoPagina++;
    }

    return tamanhoTabela;
}

bool pesquisaASI(FILE* arq, TipoIndice tab[], int tamTab, int chaveBusca, Registro* item, int* transferencias, int* comparacoes) {
    Registro pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;

    // BUSCA BINARIA NA TABELA DE INDICES
    int esq = 0, dir = tamTab - 1;
    int p = -1; // guarda o indice da pagina para busca
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
    
        (*comparacoes)++;
        if (tab[meio].chave <= chaveBusca) {
            p = meio; // possivel pagina para busca (chavePag menor ou igual)
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    // se a chave for menor que a primeira chave do arquivo
    if (p == -1) 
        return false; 
    

    /*
    PARA USAR O CODIGO DO SLIDE:
    a pesquisa da pagina antes era feita sequencialmente na tabela de paginas.
    quando saia do laço, a variavel i indicava a pagina seguinte da correta para busca
    */
    i = p + 1; 

    // VERIFICA QUANTIDADE DE ITENS NA PAGINA
    if (i < tamTab) {
        quantitens = ITENSPAGINA; 
    } else {
        fseek(arq, 0, SEEK_END); 

        //quantidade de itens da ultima pagina = resto do (total de registros / quantidade de reg nas paginas)
        quantitens = (ftell(arq) / sizeof(Registro)) % ITENSPAGINA;
        
        if (quantitens == 0) {
            quantitens = ITENSPAGINA;
        }
    }

    // deslocamento = posição da pagina * tamanho da pagina * tamanho do registro
    desloc = tab[i - 1].posicao * ITENSPAGINA * sizeof(Registro); 
    fseek(arq, desloc, SEEK_SET);
    fread(pagina, sizeof(Registro), quantitens, arq);
    (*transferencias)++;

    esq = 0;
    dir = quantitens - 1;
    
    //BUSCA BINARIA NA PAGINA 
    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        (*comparacoes)++;
        if (pagina[meio].chave == chaveBusca) {
            *item = pagina[meio]; // encontrou!!
            return true;         
        } else if (pagina[meio].chave < chaveBusca) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    return false; // não encontrou
}