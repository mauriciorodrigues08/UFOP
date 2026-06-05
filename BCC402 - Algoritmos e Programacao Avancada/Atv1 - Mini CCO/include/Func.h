#ifndef _FUNC_H_
#define _FUNC_H_

#include "Ponto.h"
#include "Segmento.h"
#include "Arvore.h"

#include <iostream>
#include <cmath>

double distanciaEntreDoisPontos(Ponto a, Ponto b);
double distanciaPontoSegmento(Ponto p, Segmento s);

double orientacao(Ponto a, Ponto b, Ponto c);

bool intersecaoSegmentos(Segmento a, Segmento b);



#endif