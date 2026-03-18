#ifndef HD_H
#define HD_H

#include <stdio.h>

typedef struct {
  FILE* arquivo;
  int tam; // qnt de blocos no disco
  long int HDhit;
} HD;

HD* criarHD(int tamanho, int num_palavras);
void destroiHD(HD* hd);
long calcula_pulo_hd(int end_hd, int num_palavras);

#endif