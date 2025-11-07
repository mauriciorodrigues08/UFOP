#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ponto.h"

struct PONTO{
  double x;
  double y;
};

PONTO *criaPonto(double x, double y){
  PONTO *tempPonto = (PONTO *) malloc(sizeof(PONTO));
  tempPonto->x = x;
  tempPonto->y = y;
  return tempPonto;
}

PONTO *liberaPonto(PONTO *p){
  free(p);
  return NULL;
}


double pontoDistancia(PONTO *p1, PONTO *p2){
  double result;
  result = sqrt(pow((p2->x - p1->x), 2) + pow((p2->y - p1->y), 2));
  return result;
}

void pontoMove(PONTO *p, double novoX, double novoY){
  p->x = novoX;
  p->y = novoY;
}