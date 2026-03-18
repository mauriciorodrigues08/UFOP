#ifndef MAQUINA_H
#define MAQUINA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cache.h"
#include "ram.h"
#include "instrucao.h"
#include "hd.h"

#define TAM_HD 10000
#define TAM_RAM 1000
#define TAM_CACHE_1 16
#define TAM_CACHE_2 32
#define TAM_CACHE_3 64
#define NUM_PALAVRAS 4

typedef struct Maquina {
  long int custo; //custo total da maquina
  long int ciclos;
  long int PC;
  int reg1;
  int reg2;
  int reg3; // Usado para lógica de transferência se necessário

  Cache *cache1;
  Cache *cache2;
  Cache *cache3;
  RAM *ram; // A RAM age como uma cache4 para o HD. Permite também o reaproveitamento das funções já implementadas pra cache, como as de LRU.
  HD *hd;

  long int pc_salvo;
  int reg1_salvo;
  int reg2_salvo;
  bool interrupcao;
} Maquina;

Maquina *criaMaquina();
Maquina *destroiMaquina(Maquina *maquina);
void iniciar(Maquina *maquina, Instrucao *inst, Instrucao* tratador_interrupcao, int prob_interrupcao);
bool recebe_instrucoes(Instrucao *inst, int qtd_inst, const char* filename); //recebe instrucoes de um txt
void set_registradores(Maquina *maquina, Instrucao *inst);

#endif