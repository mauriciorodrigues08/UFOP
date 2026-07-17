#ifndef _SEGMENTO_H_
#define _SEGMENTO_H_

#include "Ponto.h"


class Segmento{

  public:
    Ponto a;
    Ponto b;

    Segmento():
    a(Ponto()), b(Ponto()){}

    Segmento(Ponto _a, Ponto _b):
      a(_a), b(_b){}

    Segmento(double x1, double y1, double x2, double y2):
      a(Ponto(x1, y1)), b(Ponto(x2, y2)){}

    void alteraSegmento(Ponto _a, Ponto _b){
      a = _a;
      b = _b;
    }

    void alteraSegmento(double x1, double y1, double x2, double y2){
      a = Ponto(x1, y1);
      b = Ponto(x2, y2);
    }

};

#endif