#include "../include/quicksort.h"
#include <float.h>

// Protótipos das funções auxiliares
void particiona(FILE *arq, long Esq, long Dir, long *i, long *j, int *tranfLeitura, int *transfEscrita, int *comparacoes);
void quicksortRec(FILE *arq, long Esq, long Dir, int *tranfLeitura, int *transfEscrita, int *comparacoes);


void particiona(FILE *arq, long Esq, long Dir, long *i, long *j, int *tranfLeitura, int *transfEscrita, int *comparacoes) {
    long LeituraEsq = Esq, LeituraDir = Dir; 
    long EscritaEsq = Esq, EscritaDir = Dir; 
    
    float Linf = -FLT_MAX;
    float Lsup = FLT_MAX;
    
    bool lerSuperior = true;
    int N = 0;
    Item pivo[LIMITE_MEMORIA];
    
    while (LeituraEsq <= LeituraDir) {
        if (LeituraEsq == EscritaEsq) 
          lerSuperior = false;
        else if (LeituraDir == EscritaDir) 
          lerSuperior = true;
        
        Item lido;
        
        if (lerSuperior) {
          fseek(arq, LeituraDir * sizeof(Item), SEEK_SET);
          if (fread(&lido, sizeof(Item), 1, arq) != 1) {
              perror("Erro ao ler registro (superior)");
          }
          (*tranfLeitura)++;
          LeituraDir--;
          lerSuperior = false;
        } 
        else {
          fseek(arq, LeituraEsq * sizeof(Item), SEEK_SET);
          if (fread(&lido, sizeof(Item), 1, arq) != 1) {
              perror("Erro ao ler registro (inferior)");
          }
          (*tranfLeitura)++;
          LeituraEsq++;
          lerSuperior = true;
        }
        
        (*comparacoes)++;
        if (lido.nota > Lsup) {
          fseek(arq, EscritaDir * sizeof(Item), SEEK_SET);
          fwrite(&lido, sizeof(Item), 1, arq);
          (*transfEscrita)++;
          EscritaDir--;
        } 
        else {
          (*comparacoes)++;
          if (lido.nota < Linf) {
            fseek(arq, EscritaEsq * sizeof(Item), SEEK_SET);
            fwrite(&lido, sizeof(Item), 1, arq);
            (*transfEscrita)++;
            EscritaEsq++;
            } 
            else {
              // Inserção ordenada na área de memória interna
                int k = N - 1;
                while (k >= 0) {
                  (*comparacoes)++;
                  if (pivo[k].nota > lido.nota) { //procura onde inserir no pivo
                    pivo[k + 1] = pivo[k];
                    k--;
                  } 
                  else {
                    break;
                  }
                }
                pivo[k + 1] = lido;
                N++;
                
                // Se a área encher (atingir LIMITE_MEMORIA), precisamos remover um registro
                if (N == LIMITE_MEMORIA) {
                  long T1 = EscritaEsq - Esq;
                  long T2 = Dir - EscritaDir;
                    
                  if (T1 < T2) {
                    // Remove o menor registro da memória e escreve em A1
                    fseek(arq, EscritaEsq * sizeof(Item), SEEK_SET);
                    fwrite(&pivo[0], sizeof(Item), 1, arq);
                    (*transfEscrita)++;
                    Linf = pivo[0].nota;
                    EscritaEsq++;
                        
                    // Desloca os elementos restantes para a esquerda
                    for (int i = 1; i < N; i++) {
                        pivo[i - 1] = pivo[i];
                    }
                    N--;
                  } 
                  else {
                    // Remove o maior registro da memória e escreve em A2
                    fseek(arq, EscritaDir * sizeof(Item), SEEK_SET);
                    fwrite(&pivo[N - 1], sizeof(Item), 1, arq);
                    (*transfEscrita)++;
                    Lsup = pivo[N - 1].nota;
                    EscritaDir--;
                    N--;
                  }
                }
            }
        }
    }
    

    long original_Ei = EscritaEsq;
    for (int k = 0; k < N; k++) {
      fseek(arq, EscritaEsq * sizeof(Item), SEEK_SET);
      fwrite(&pivo[k], sizeof(Item), 1, arq);
      (*transfEscrita)++;
      EscritaEsq++;
    }
    
    *i = original_Ei - 1;
    *j = EscritaDir + 1;
}


void quicksortRec(FILE *arq, long Esq, long Dir, int *tranfLeitura, int *transfEscrita, int *comparacoes) {
    if (Dir - Esq < 1) 
      return;
    
    long i, j;
    particiona(arq, Esq, Dir, &i, &j, tranfLeitura, transfEscrita, comparacoes);
    
    // Prioriza ordenar o subarquivo de menor tamanho primeiro
    if (i - Esq < Dir - j) {
        quicksortRec(arq, Esq, i, tranfLeitura, transfEscrita, comparacoes);
        quicksortRec(arq, j, Dir, tranfLeitura, transfEscrita, comparacoes);
    } else {
        quicksortRec(arq, j, Dir, tranfLeitura, transfEscrita, comparacoes);
        quicksortRec(arq, Esq, i, tranfLeitura, transfEscrita, comparacoes);
    }
}


void quicksort(FILE *arquivo, long quant, int *tranfLeitura, int *transfEscrita, int *comparacoes) {
    if (quant <= 1) return;

    quicksortRec(arquivo, 0, quant - 1, tranfLeitura, transfEscrita, comparacoes);
}