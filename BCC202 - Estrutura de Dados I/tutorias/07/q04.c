//Implemente as funções CriaFila, DestroiFila, FilaEnfileira e FilaDesenfileira.

#include <stdio.h>
#include <stdlib.h>

// Definição da Celula da Fila
typedef struct celula {
  int item;
  struct celula *next;
} Celula;

// Definição da Estrutura da Fila
typedef struct {
  Celula *topo;
  Celula *ultimo;
} Fila;

// Cria uma fila vazia
Fila* CriaFila() {
  Fila *fila = (Fila*)malloc(sizeof(Fila));
  if (fila != NULL) {
    fila->topo = NULL;
    fila->ultimo = NULL;
  }
  return fila;
}

// Insere um elemento no fim da fila
void FilaEnfileira(Fila *fila, int x) {
  if (fila == NULL) return;

  Celula *novo = (Celula*)malloc(sizeof(Celula));
  if (novo == NULL) return;

  novo->item = x;
  novo->next = NULL;

  if (fila->ultimo == NULL) { // Fila estava vazia
    fila->topo = novo;
  } else {
    fila->ultimo->next = novo;
  }
  fila->ultimo = novo;
}

// Remove um elemento do início da fila 
int FilaDesenfileira(Fila *fila) {
  if (fila == NULL || fila->topo == NULL) {
    return -1; 
  }

  Celula *temp = fila->topo;
  int valor = temp->item;

  fila->topo = fila->topo->next;

  if (fila->topo == NULL) {
    fila->ultimo = NULL;
  }

  free(temp);
  return valor;
}

// Libera toda a memória ocupada pela fila
void DestroiFila(Fila *fila) {
  if (fila == NULL) return;
  
  Celula *atual = fila->topo;
  while (atual != NULL) {
    Celula *temp = atual;
    atual = atual->next;
    free(temp);
  }
  free(fila);
}

void ImprimeFila(Fila *fila) {
  if (fila == NULL || fila->topo == NULL) {
    printf("Fila atual: [ VAZIA ]\n");
    return;
  }
  
  printf("Fila atual: (TOPO) ");
  Celula *atual = fila->topo;
  while (atual != NULL) {
    printf("[%d] ", atual->item);
    if (atual->next != NULL) printf("-> ");
    atual = atual->next;
  }
  printf("(ULTIMO)\n");
}

int main() {
  Fila *fila = CriaFila();
  
  printf("=== TESTE DE FILA ===\n\n");

  // 1. Estado inicial
  ImprimeFila(fila);

  // 2. Testando Enfileiramento com prints
  printf("\nEnfileirando 10, 20 e 30...\n");
  FilaEnfileira(fila, 10);
  ImprimeFila(fila);
  
  FilaEnfileira(fila, 20);
  ImprimeFila(fila);
  
  FilaEnfileira(fila, 30);
  ImprimeFila(fila);

  // 3. Testando Desenfileiramento
  printf("\nDesenfileirando primeiro elemento...\n");
  int v = FilaDesenfileira(fila);
  printf("Valor removido do TOPO: %d\n", v);
  ImprimeFila(fila);

  // 4. Inserindo mais um para ver o movimento do ULTIMO
  printf("\nEnfileirando 40...\n");
  FilaEnfileira(fila, 40);
  ImprimeFila(fila);

  // 5. Esvaziando a fila
  printf("\nRemovendo todos os itens restantes...\n");
  while (fila->topo != NULL) {
    printf("Removido: %d\n", FilaDesenfileira(fila));
    ImprimeFila(fila);
  }

  return 0;
}