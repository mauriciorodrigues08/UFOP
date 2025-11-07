#include <stdio.h>

#include "ponto.h"

int main(){
  double tempx, tempy;
  PONTO *p1, *p2;
  
  printf("Insira as coordenadas (x, y) de p1 e p2: ");

  scanf("%lf%lf", &tempx, &tempy);
  p1 = criaPonto(tempx, tempy);

  scanf("%lf%lf", &tempx, &tempy);
  p2 = criaPonto(tempx, tempy);


  printf("\nDistancia entre p1 e p2: %lf\n", pontoDistancia(p1, p2));

  printf("\nInsira as novas coordenadas (x, y) de p1 e p2: ");

  scanf("%lf%lf", &tempx, &tempy);
  pontoMove(p1, tempx, tempy);

  scanf("%lf%lf", &tempx, &tempy);
  pontoMove(p2, tempx, tempy);


  printf("\nDistancia entre p1 e p2: %lf\n", pontoDistancia(p1, p2));

  p1 = liberaPonto(p1);
  p2 = liberaPonto(p2);


  return 0;
}