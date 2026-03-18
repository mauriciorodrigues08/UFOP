#ifndef MMU_H
#define MMU_H

#include "ram.h"
#include "cache.h"
#include "instrucao.h"
#include "maquina.h"
#include <stdbool.h>

// Busca e gerenciamento
void busca_memoria(int endereco_bloco, Maquina *maquina, int *memoria, int *posicao);

bool esvaziarCache(Maquina *maquina);

#endif