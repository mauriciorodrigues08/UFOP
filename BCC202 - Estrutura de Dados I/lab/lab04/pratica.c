#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
  //recebe quantidades
  int n, m;
  scanf("%d %d", &n, &m);

  //criacao do mapa
  MapaCidades mapa = criaMapa(n, m);

  //recebe valores de A e B
  int a, b;
  scanf("%d %d", &a, &b);

  //verifica se existe caminho de A para B
  bool *visitado = calloc(mapa.qtd, sizeof(bool));
  bool res = existeCaminho(&mapa, a, b, visitado);

  //print do resultado
  (res) ? printf("SIM\n") : printf("NAO\n");

  //libera memoria alocada
  free(visitado);
  liberaMapa(&mapa);
  return 0;
}
