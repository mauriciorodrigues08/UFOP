#include "include/Func.h"

double distanciaEntreDoisPontos(Ponto a, Ponto b){
  return sqrt( pow((b.x - a.x), 2) + pow((b.y - a.y), 2) );
}

double distanciaPontoSegmento(Ponto p, Segmento s){
  //algoritmo para determinar distâncida entre um potno e segmento
  double dx = s.b.x - s.a.x;
  double dy = s.b.y - s.a.y;
  double len2 = dx*dx + dy*dy;

  if(len2 < 1e-12) //segmento pequeno demais
      return distanciaEntreDoisPontos(p, s.a);

  //t = (P-A)·(B-A) / ||B-A||²
  double t = ((p.x - s.a.x)*dx + (p.y - s.a.y)*dy) / len2;

  if(t < 0.0) // ponto mais próximo é A
    t = 0.0;   
  if(t > 1.0) // ponto mais próximo é B
    t = 1.0;   

  Ponto projecao(s.a.x + t*dx, s.a.y + t*dy); 
  //calcula a distância entre o ponto dado e seu ponto mais próximo no segmento
  return distanciaEntreDoisPontos(p, projecao);
}

double orientacao(Ponto a, Ponto b, Ponto c){
  return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
  //return > 0 ->  curva a esquerda
  //return < 0 -> curva a direita
  //return = 0 -> mesma reta
}

bool intersecaoSegmentos(Segmento a, Segmento b){
  Ponto pA, pB, pC, pD;
  pA = a.a;
  pB = a.b;
  pC = b.a;
  pD = b.b;

  double o1 = orientacao(pA, pB, pC); //orient (A, B, C);
  double o2 = orientacao(pA, pB, pD); //orient (A, B, D);
  double o3 = orientacao(pC, pD, pA); //orient (C, D, A);
  double o4 = orientacao(pC, pD, pB); //orient (C, D, B);
  return ( o1 * o2 < 0.0) && ( o3 * o4 < 0.0);
}
