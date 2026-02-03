#ifndef FILA_H
#define FILA_H

//imports
#include <stdbool.h>

struct processo {
  int id;
  float tempo;
  int prioridade;
  int ciclos;
};

//definicao de apelidos para structs
typedef struct processo Processo;
typedef struct fila FilaProcessos;
typedef struct celula Celula;

//declaracao de funcoes de fila
FilaProcessos* criarFila(Processo *processos, int n);
FilaProcessos* destroiFila(FilaProcessos *pFila);
bool adicionaFila(FilaProcessos *pFila, Processo *novoProcesso);
void escalonador(FilaProcessos *pFila);
void imprimeLog(FilaProcessos *pFila);

#endif //FILA_H