#ifndef _VETOR_H_
#define _VETOR_H_

#include "Ponto.h"
#include "Segmento.h"
#include <cmath>

class Vetor{
  public:

  double x;
  double y;
  double z;


  Vetor(double _x = 0.0, double _y = 0.0, double _z = 0.0):
    x(_x), y(_y), z(_z){}

  Vetor(Ponto a, Ponto b){
    x = b.x - a.x;
    y = b.y - a.y;
    z = b.z - a.z;
  }

  Vetor(Segmento s) : Vetor(s.a, s.b){}


  double norma(){
    return sqrt((x * x) + (y * y) + (z * z));
  }

  double produtoEscalar(Vetor v){
    return (x * v.x) + (y * v.y) + (z * v.z);
  }


};

#endif