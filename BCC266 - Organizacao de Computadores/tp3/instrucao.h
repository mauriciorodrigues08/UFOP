#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H


//Bibliotecas
#include <stdlib.h>

//TAD de dados de um endereço
typedef struct Endereco{
    int addBloco; //Endereço do bloco
    int addPalavra; //Endereço da palavra
}Endereco;

//TAD de dados de uma instrução
typedef struct Instrucao{
    struct Endereco end1;
    struct Endereco end2;
    struct Endereco end3;
    int opcode;
}Instrucao;

//Funçôes da TAD
Instrucao *criaInstrucoes(int n); //Aloca um vetor de instruções
Instrucao *destroiInstrucoes(Instrucao *inst); //Libera um vetor de instruções

#endif