#ifndef ALUNO_H
#define ALUNO_H

//bibliotecas
#include <stdlib.h>
#include <stdbool.h>

//defines
#define MAX_PALAVRA 50

//structs
typedef struct no No;

//funcoes
No* iniciaArvore(char *palavra);
No* destroiArvore(No *raiz);
No* adicionaNo(No *raiz, char *palavra);
void printResultado(No *raiz);

#endif