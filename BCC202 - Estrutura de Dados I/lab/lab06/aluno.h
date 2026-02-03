#ifndef ALUNO_H
#define ALUNO_H

#define MAX_PALAVRA 50
#define MAX_DESC 300

typedef struct {
  char palavra[MAX_PALAVRA];
  char descricao[MAX_DESC];
} Registro;

void getRegistros(Registro *dicionario, int qtd);
int comparaPalavras(const void *a, const void *b);
int buscaBinaria(Registro *dicionario, char *busca, int esq, int dir);

void lower(char *palavra);

#endif