#ifndef _ARVORE_H_
#define _ARVORE_H_

#include <iostream>
#include <fstream>
#include "Ponto.h"


class No{
  public:
    Ponto p;
    int chave;

    No *esq;
    No *dir;
    No *pai;

    No(Ponto pRaiz, int chaveRaiz):
      p(pRaiz), chave(chaveRaiz), esq(nullptr), dir(nullptr), pai(nullptr){}
    
    ~No(){
      if(esq != nullptr) delete esq;
      if(dir != nullptr) delete dir;
    }


    friend std::ostream& operator<<(std::ostream& os, No &no){
      os <<no.chave<<"-> "<<no.p<<"\n";
      return os;
    }
    
};

int numeroNos(No *raiz);
int numeroFolhas(No *raiz);


#endif