#ifndef ALUNO_H
#define ALUNO_H

typedef struct No {
    int cidade;
    struct No *prox;
} No;

typedef struct {
    // pode adicionar mais informações
    No **vetor; 
    int qtd;
} MapaCidades;

/*
    Entradas e retornos de funções a cargo do aluno
*/

void criaMapa();
void liberaMapa();
void existeCaminho();

#endif
