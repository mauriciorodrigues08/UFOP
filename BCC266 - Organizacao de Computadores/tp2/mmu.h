#ifndef MMU_H
#define MMU_H

#include "ram.h"
#include "cache.h"
#include "instrucao.h"
#include "maquina.h"
#include <stdbool.h>

// Busca e gerenciamento
void busca_memoria(int endereco_bloco, Maquina *maquina, int *memoria, int *posicao);
bool atualiza_lru(Cache *cache, int bloco, int chave);
int verifica_lru(Cache *cache); 
int verifica_mru(Cache *cache);

// Movimentação entre níveis
bool cache2_to_cache1(Maquina *maquina, int bloco2);
bool cache3_to_cache1(Maquina *maquina, int bloco3);
bool ram_to_cache1(Maquina *maquina, int end_ram);

bool cache3_to_ram(Maquina *maquina);
bool cache2_to_ram(Maquina *maquina);
bool cache1_to_ram(Maquina *maquina);
bool esvaziarCache(Maquina *maquina);

#endif