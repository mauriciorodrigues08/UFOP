// Crie uma fila onde cada elemento possui um id (int) e uma prioridade que varia entre 0 e 100. A função inserir pode colocar o elemento no final da estrutura (como numa lista ou array simples). A função remover deve retirar o primeiro elemento da estrutura e imprimir sua prioridade se tiver valor maior que 50.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item {
  int id;
  int prioridade;
  struct item *prox;
} Item;

typedef struct fila {
  Item *topo;
  Item *ultimo;
} Fila;

Fila* FilaCria() {
  Fila *fila = (Fila *) malloc(sizeof(Fila));
  if (!fila)
    return NULL;

  fila->topo = NULL;
  fila->ultimo = NULL;
  return fila;
}

bool FilaEhVazia(Fila *pFila) {
  if (!pFila)
    return true;

  if (pFila->topo == NULL)
    return true;

  return false;
}

void FilaPrint(Fila *fila) {
  Item *aux = fila->topo;

  printf("Lista atual:\n[ ");
  
  while (aux != NULL) {
    printf("{%d | %d} ", aux->id, aux->prioridade);
    aux = aux->prox;
  }

  printf("]\n\n");
}

bool FilaPush(Fila *pFila, int id, int prioridade) {
  if (!pFila)
    return false;

  if (prioridade >= 0 && prioridade <= 100) { //verifica se a prioridade é válida
    //cria o novo item
    Item *novo = (Item *) malloc(sizeof(Item));
    if (!novo)
      return false;

    novo->id = id;
    novo->prioridade = prioridade;
    novo->prox = NULL;

    if (FilaEhVazia(pFila)) {
      //inicializa a lista com o valor a ser adicionado
      pFila->topo = novo;
      pFila->ultimo = novo;

      return true;
    }
    
    //atribui os valores
    pFila->ultimo->prox = novo; //antigo ultimo passa a ter um prox
    pFila->ultimo = novo; //novo é o novo último  
    
    return true;
  }  

  return false;
}

bool FilaPop(Fila *pFila, Item *poped) {
  if (!pFila)
    return false;

  if (FilaEhVazia(pFila))
    return false;

  Item *aux = pFila->topo;
  pFila->topo = pFila->topo->prox;

  if (!pFila->topo)
    pFila->ultimo = NULL;
  
  poped->id = aux->id;
  poped->prioridade = aux->prioridade;

  free(aux);
  return true;
}

Fila* FilaDestroi(Fila *pFila) {
  if (!pFila)
    return NULL;

  Item *aux = pFila->topo;
  while (aux != NULL) {
    Item *prox = aux->prox;
    free(aux);
    aux = prox;
  }

  free(pFila);

  return NULL;
}

int main() {
  Fila *fila = FilaCria();
  if (!fila)
    return 0;

  Item poped;
  
  //testando fila vazia
  printf("\nA fila eh vazia? %s", FilaEhVazia(fila) ? "sim\n\n" : "não\n\n");

  //adicionando valores
  FilaPush(fila, 1, 54) ? printf("ID 1 adicionado\n") : printf("ID 1 não adicionado\n");
  FilaPush(fila, 2, 70) ? printf("ID 2 adicionado\n\n") : printf("ID 2 não adicionado\n\n");

  //printando fila
  printf("A fila eh vazia? %s", FilaEhVazia(fila) ? "sim\n\n" : "não\n\n");
  FilaPrint(fila);

  //adicionando valores
  FilaPush(fila, 3, 102) ? printf("ID 3 adicionado\n") : printf("ID 3 não adicionado\n"); //falha
  FilaPush(fila, 4, -20) ? printf("ID 4 adicionado\n") : printf("ID 4 não adicionado\n"); //falha
  FilaPush(fila, 5, 0) ? printf("ID 5 adicionado\n") : printf("ID 5 não adicionado\n");
  FilaPush(fila, 6, 100) ? printf("ID 6 adicionado\n\n") : printf("ID 6 não adicionado\n\n");
  
  //printando fila
  FilaPrint(fila);
  
  //removendo valores
  FilaPop(fila, &poped) ? printf("Item removido\n") : printf("Item não removido\n\n");
  if (poped.prioridade > 50)
    printf("Prioridade removida: %d\n\n", poped.prioridade);
  else
    printf("\n");
  FilaPrint(fila);

  //adicionando valores
  FilaPush(fila, 1, 54) ? printf("ID 1 adicionado\n") : printf("ID 1 não adicionado\n");
  
  //removendo valores
  FilaPop(fila, &poped) ? printf("Item removido\n") : printf("Item não removido\n\n");

  if (poped.prioridade > 50)
    printf("Prioridade removida: %d\n\n", poped.prioridade);
  else
    printf("\n");
  
  FilaPrint(fila);


  FilaPop(fila, &poped) ? printf("Item removido\n") : printf("Item não removido\n\n");

  if (poped.prioridade > 50)
    printf("Prioridade removida: %d\n\n", poped.prioridade);
  else
    printf("\n");
  
  FilaPrint(fila);


  FilaPop(fila, &poped) ? printf("Item removido\n") : printf("Item não removido\n\n");
  
  if (poped.prioridade > 50)
    printf("Prioridade removida: %d\n\n", poped.prioridade);
  else
    printf("\n");
  
  FilaPrint(fila);
  
  
  FilaPop(fila, &poped) ? printf("Item removido\n") : printf("Item não removido\n\n");
  
  if (poped.prioridade > 50)
    printf("Prioridade removida: %d\n\n", poped.prioridade);
  else
    printf("\n");
  
  FilaPrint(fila);

  //testando fila vazia
  printf("A fila eh vazia? %s", FilaEhVazia(fila) ? "sim\n\n" : "não\n\n");

  //destruindo fila
  fila = FilaDestroi(fila);
  
  return 0;
}