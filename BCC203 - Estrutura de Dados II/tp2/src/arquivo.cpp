#include "../include/arquivo.h"

void escreverAlunoTexto(FILE *arquivo, Item &aluno){
    fprintf(arquivo, "%08ld %5.1f %-2s %-50s %-30s\n", aluno.inscricao, aluno.nota, aluno.estado, aluno.cidade, aluno.curso);
}

void merge(Item *v, int l, int m, int r, int situacao) {
    // criar os subvetores
    int tamEsq = m - l + 1;
    int tamDir = r - m; 
    
    Item *EsqV = new Item[tamEsq];
    Item *DirV = new Item[tamDir];

    // copiar os valores para o subvetor
    int i, j;
    for (i = 0; i < tamEsq; i++) {
        EsqV[i] = v[i + l];
    }
    for (j = 0; j < tamDir; j++) {
        DirV[j] = v[j + m + 1];
    }

    int k = l;
    i = 0;
    j = 0;
    
    while (i < tamEsq && j < tamDir) {
        bool esqPrioridade = false;
        
        if (situacao == 1) { // 1 = Ascendente
            if (EsqV[i].nota <= DirV[j].nota) 
                esqPrioridade = true;
        } else if (situacao == 2) { // 2 = Descendente
            if (EsqV[i].nota >= DirV[j].nota) 
                esqPrioridade = true;
        }

        if (esqPrioridade) {
            v[k++] = EsqV[i++];
        } else {
            v[k++] = DirV[j++];
        }
    }
    
    while (i < tamEsq) {
        v[k++] = EsqV[i++];
    }
    while (j < tamDir) {
        v[k++] = DirV[j++];
    }
    
    delete[] EsqV;
    delete[] DirV;
}

void mergeRec(Item *v, int l, int r, int situacao) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeRec(v, l, m, situacao);
        mergeRec(v, m + 1, r, situacao);
        merge(v, l, m, r, situacao);
    }
}

void MergeSort(Item *v, int n, int situacao) {
    if (!v){
        return;
    }
    mergeRec(v, 0, n - 1, situacao);
}