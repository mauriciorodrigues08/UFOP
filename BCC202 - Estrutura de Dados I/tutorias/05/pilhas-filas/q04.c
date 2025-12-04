// Suponha que você está trabalhando no restaurante universitário e possui as informações dos estudantes (nome e matrícula). Crie uma função que controle a entrada e a saída dos estudantes. Além disso, implemente uma função que imprime todos os estudantes que estão presentes no RU. Lembre-se de utilizar a estrutura de dados correta.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
  char nome[21];
  int matricula;
  struct item *prox;
} Item;

typedef struct fila {
  Item *topo;
  Item *ultimo;
} Fila;

Fila* FilaCria() {
  Fila *ru = (Fila *) malloc (sizeof(Fila));
  if (!ru)
    return NULL;

  ru->topo = NULL;
  ru->ultimo = NULL;
  
  return ru;
}

Fila* FilaDestroi(Fila *ru) {
  if (!ru)
    return NULL;

  Item *aux = ru->topo;
  while (aux != NULL) {
    Item *prox = aux->prox;
    free(aux);
    aux = prox;
  }

  free(ru);
  return NULL;
}

bool FilaEhVazia(Fila *ru) {
  if (!ru)
    return false;

  return !ru->topo;
}

bool FilaPush(Fila *ru, char *nome, int matricula) {
  if (!ru)
    return false;
    
  Item *aux = (Item *) malloc(sizeof(Item));  
  if (!aux)
    return false;

  aux->matricula = matricula;
  strcpy(aux->nome, nome);
  aux->prox = NULL;
    
  if (FilaEhVazia(ru)) {
    ru->topo = aux;
    ru->ultimo = aux;
    return true;
  }

  ru->ultimo->prox = aux; //antigo ultimo passa a ter um prox
  ru->ultimo = aux; //aux passa a ser o novo ultimo
  return true;
}

bool FilaPop(Fila *ru, Item *poped) {
  if (!ru)
    return false;

  if (FilaEhVazia(ru))
    return false;

  Item *aux = ru->topo;
  ru->topo = aux->prox;

  if (!ru->topo)
    ru->ultimo = NULL;
  
  strcpy(poped->nome, aux->nome); 
  poped->matricula = aux->matricula;
  
  free(aux);
  return true;
}

void FilaPrint(Fila *ru) {
  Item *aux = ru->topo;
  
  printf("\nPresentes no RU:\n[");
  
  while(aux != NULL) {
    printf(" {%s | %d } ", aux->nome, aux->matricula);
    aux = aux->prox;
  }

  printf("]\n");
}

int main() {
  Fila *ru = FilaCria();
  if (!ru)
    return 0;

  Item poped; 
  
  //verificando lista vazia
  printf("\nO RU está vazio? %s\n", FilaEhVazia(ru) ? "sim" : "não");
  
  //pessoas entrando
  printf("\nMauricio %sentrou no RU\n", FilaPush(ru, "Mauricio", 1000) ? "" : "não ");
  printf("\nO RU está vazio? %s\n", FilaEhVazia(ru) ? "sim" : "não");
  printf("\nJoao %sentrou no RU\n", FilaPush(ru, "Joao", 1001) ? "" : "não ");
  printf("\nPedro %sentrou no RU\n", FilaPush(ru, "Pedro", 1002) ? "" : "não ");
  FilaPrint(ru);
  printf("\nArthur %sentrou no RU\n", FilaPush(ru, "Arthur", 1003) ? "" : "não ");
  printf("\nMarcio %sentrou no RU\n", FilaPush(ru, "Marcio", 1004) ? "" : "não ");
  FilaPrint(ru);
  
  //pessoas saindo
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  FilaPrint(ru);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  FilaPrint(ru);
  
  //pessoas entrando
  printf("\nMauricio %sentrou no RU\n", FilaPush(ru, "Mauricio", 1000) ? "" : "não ");
  printf("\nCamile %sentrou no RU\n", FilaPush(ru, "Camile", 1005) ? "" : "não ");
  printf("\nViviane %sentrou no RU\n", FilaPush(ru, "Viviane", 1006) ? "" : "não ");
  FilaPrint(ru);

  //pessoas saindo
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  FilaPrint(ru);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  FilaPrint(ru);
  
  if (FilaPop(ru, &poped))
    printf("\n%s saiu do RU\n", poped.nome);
  FilaPrint(ru);

  printf("\nO RU está vazio? %s\n", FilaEhVazia(ru) ? "sim" : "não");

  FilaDestroi(ru);
  
  return 0;
}