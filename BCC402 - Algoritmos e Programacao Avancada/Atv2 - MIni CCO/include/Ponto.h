#ifndef _PONTO_H_
#define _PONTO_H_

#include <iostream>

class Ponto{
  public:
    double x;
    double y;
    double z;
    
    Ponto(double _x = 0.0, double _y = 0.0, double _z = 0.0):
      x(_x), y(_y), z(_z){}

    void alteraPonto(double _x, double _y, double _z){
      x = _x;
      y = _y;
      z = _z;
    }


    void alteraPonto(double _x, double _y){
      x = _x;
      y = _y;
    }

    friend std::ostream &operator<<(std::ostream& os, const Ponto& p);

  };

  inline std::ostream &operator<<(std::ostream& os, const Ponto& p){
    os<<"("<<p.x<<", "<<p.y<<", "<<p.z<<")";
    return os;
  }
    
#endif