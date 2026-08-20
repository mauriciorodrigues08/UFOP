#ifndef _ARVORE_H_
#define _ARVORE_H_

#include <iostream>
#include <algorithm>
#include <fstream>
#include "Ponto.h"


class No{
  public:
    Ponto p;
    int chave;

    No *esq;
    No *dir;
    No *pai;

    //propriedades físicas do segmento entre este nó e seu pai (a raiz não representa segmento)
    double raio;
    double comprimento;
    double fluxo;
    double resistencia;
    double volume;
    int qtdTermDistal; //quantidade de terminais distais a este nó

    No(Ponto pRaiz, int chaveRaiz):
      p(pRaiz), chave(chaveRaiz), esq(nullptr), dir(nullptr), pai(nullptr),
      raio(0.0), comprimento(0.0), fluxo(0.0), resistencia(0.0), volume(0.0), qtdTermDistal(0){}
    
    ~No(){}


    friend std::ostream& operator<<(std::ostream& os, No &no){
      os <<no.chave<<"-> "<<no.p<<"\n";
      return os;
    }
    
};

void destroiArvore(No *raiz);

int numeroNos(No *raiz);
int numeroFolhas(No *raiz);

int profundidadeMax(No *raiz);
int numBifurcacoes(No *raiz);


#endif