#include <stdlib.h>
#include <stdio.h>

#include "hd.h"
#include "bloco.h"

HD* criarHD(int tamanho, int num_palavras) {
    HD* hd = (HD *) malloc(sizeof(HD));
    hd->tam = tamanho;
    hd->HDhit = 0;

    hd->arquivo = fopen("hd.bin", "rb+");
    if (!hd->arquivo) {
        hd->arquivo = fopen("hd.bin", "wb+");

        BlocoDeMemoria vazio;
        criaBloco(&vazio, num_palavras, -1);

        int *palavras_aleatorias = (int*) calloc(num_palavras, sizeof(int));

        // preenche o HD inteiro com blocos e palavras vazias
        for (int i = 0; i < tamanho; i++) {
            for(int j = 0; j < num_palavras; j++) 
                palavras_aleatorias[j] = rand() % 1000000;
            fwrite(&vazio, sizeof(BlocoDeMemoria), 1, hd->arquivo);
            fwrite(palavras_aleatorias, sizeof(int), num_palavras, hd->arquivo);
        }

        liberaBloco(&vazio);
        free(palavras_aleatorias);
    }

    fclose(hd->arquivo);
    return hd;
}

void destroiHD(HD* hd) {
    if (hd->arquivo){
        fclose(hd->arquivo);
        hd->arquivo = NULL;
    }

    free(hd);
}

long calcula_pulo_hd(int end_hd, int num_palavras) {
    return end_hd * (sizeof(BlocoDeMemoria) + (sizeof(int) * num_palavras));
}