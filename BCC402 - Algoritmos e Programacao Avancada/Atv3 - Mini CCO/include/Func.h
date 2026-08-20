#ifndef _FUNC_H_
#define _FUNC_H_

#include "Ponto.h"
#include "Segmento.h"
#include "Arvore.h"
#include "Vetor.h"

#include <iostream>
#include <cmath>

typedef enum TipoCusto{
  J1 = 0, J2, J3, J4
}TipoCusto;


inline std::ostream &operator<<(std::ostream& os, const TipoCusto& modo){
  if(modo == J2){
    os<<"J2";
    return os;
  }
  if(modo == J3){
    os<<"J3";
    return os;
  }
  if(modo == J4){
    os<<"J4";
    return os;
  }

  os<<"J1";
  return os;
}

double distanciaEntreDoisPontos(Ponto& a, Ponto& b);
double distanciaPontoSegmento(Ponto& p, Segmento& s);

double orientacao(Ponto& a, Ponto& b, Ponto& c);

bool intersecaoSegmentos(Segmento& a, Segmento& b);


//comprimento, resistência e volume (lei de Poiseuille)
double calculaComprimento(No *seg);
double calculaComprimentoTotal(No *raiz);
double calculaResistencia(double mu, double comprimento, double raio);
double calculaVolume(double comprimento, double raio);
double calculaVolumeTotal(No *raiz);

//quantidade de terminais distais (pós-ordem)
int atualizaQtdTerminaisDistais(No *no);

//fluxo em cada segmento, assumindo terminais iguais
void atualizaFluxos(No *no, double Qterm);

//lei de bifurcação / escala dos raios: rj = C*Qj^(1/gamma), C=1, normalizado pelo tronco
void atualizaComprimentos(No *no);
void atualizaResistencias(No *no, double mu);
void atualizaVolumes(No *no);
void atualizaRaiosPorFluxo(No *no, double gamma);
void atualizaGeometriaFisica(No *raiz, double Qterm, double gamma, double mu);

/*calcula o custo de inserção de acordo com o modo escolhido
  J1 = volume total
  J2 = comprimento total
  J3 = a * volume total + b * comprimento total
  J4 = a * volume total + b * penalização angular*/
double funcaoCustoComposta(No *raiz, Segmento segsNovos[3], double alpha, double beta, TipoCusto modo);

//otimização geométrica da bifurcação (busca em grade, coordenadas baricêntricas)
Ponto pontoBaricentrico(Ponto &A, Ponto &B, Ponto &C, double alpha, double beta, double lambda);
int pontoDentroTriangulo(Ponto &A, Ponto &B, Ponto &C, Ponto &P);

//assinatura estendida em relação ao enunciado (recebe também os nós temporários e os
//parâmetros físicos), pois cada ponto candidato exige recalcular a árvore inteira
Ponto otimizaBifurcacaoPorGrade(No *raizArvore, No *novaBifurcacao, No *alvo, No *novoTerminal,
                                 Ponto &A, Ponto &B, Ponto &C, int M,
                                 double Qterm, double gamma, double mu,
                                 double *melhorCusto, TipoCusto modo, double alpha, double beta);

bool intersectaComArvore(No *raiz, Segmento segsNovos[3], No *ignorar1, No *ignorar2, No *ignorar3);

#endif