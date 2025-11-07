#ifndef PONTO_H
#define PONTO_H

typedef struct PONTO PONTO;

PONTO *criaPonto(double x, double y);
PONTO *liberaPonto(PONTO *p);
double pontoDistancia(PONTO *p1, PONTO *p2);
void pontoMove(PONTO *p, double novoX, double novoY);


#endif