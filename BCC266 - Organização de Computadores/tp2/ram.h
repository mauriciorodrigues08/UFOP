#ifndef RAM_H
#define RAM_H

//Bibliotecas
#include <stdlib.h>
#include "bloco.h"

//TAD de dados de um bloco de memoria
typedef struct RAM{
    BlocoDeMemoria *blocos;
    int numBlocos;

    long int custo; //Preço de uso do bloco
    long int ramHit; //Quantas vezes foi encontrado
}RAM;

//Funçôes da TAD
RAM *criarRam(int numBlocos, int numPalavras); //Cria um vetor de blocos de memoria
RAM *destroiRam(RAM *ram, int n); //Libera um vetor de blocos de memoria

void preencheRamAleatoria(RAM *ram, int tamanhoRam, int numPalavras);

#endif