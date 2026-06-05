#ifndef _DOMINIO_H_
#define _DOMINIO_H_

#include "Ponto.h"
#include <cmath>

class Dominio{
  public:
    double raio;
    Ponto centro;

    Dominio(double _raio = 0.0, Ponto _centro = Ponto(0.0, 0.0, 0.0)):
      raio(_raio), centro(_centro){}

    bool isInDominio(Ponto p){
      return pow(p.x, 2) + pow(p.y, 2) <= pow(raio, 2);
    }

};


#endif