#ifndef _REGISTRO_H_
#define _REGISTRO_H_

typedef struct Registro {
  int chave;
  long int dado1;
  char dado2[1000];
  char dado3[5000];
}Registro;

#define ITENSPAGINA 100
#define MAXTABELA 10050 // tamanho máximo para o vetor de índices

// estrutura da tabela de índices
typedef struct {
    int posicao; // número de página
    int chave; // primeira chave da página
} TipoIndice;

#endif