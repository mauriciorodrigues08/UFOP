#ifndef _ASI_H_
#define _ASI_H_

#include <stdio.h>
#include "registro.h"

// cria tabela de indices lendo o arquivo
int criaTabelaIndice(FILE* arq, TipoIndice tabela[], int* transferencias);

// faz a busca utilizando a tabela de indices e o arquivo
bool pesquisaASI(FILE* arq, TipoIndice tab[], int tamTab, int chaveBusca, Registro* item, int* transferencias, int* comparacoes);

#endif