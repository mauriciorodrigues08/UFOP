/*Faça uma função que recebe uma lista encadeada que deve remover os 3 primeiros itens que apresentarem valores maiores que 10. Feita essa alteração, deve-se inverter a lista. Você deve fazer essa função tanto para lista encadeada com cabeça quanto para lista encadeada sem cabeça.
Ex: 	
  1 -> 13 -> 42 -> 8 -> 4 -> 10 -> 11 -> 32 -> 64
	1 -> 8 -> 4 -> 10 -> 32 -> 64
	64 -> 32 -> 10 -> 4 -> 8 -> 1
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
  int valor;
  struct celula *next;
} Celula;

Celula* criarNo(int valor) {
  Celula *novo = (Celula*)malloc(sizeof(Celula));
  novo->valor = valor;
  novo->next = NULL;
  return novo;
}

void inserirFim(Celula **head, int valor) {
  Celula *novo = criarNo(valor);
  if (*head == NULL) {
    *head = novo;
    return;
  }
  Celula *temp = *head;
  while (temp->next != NULL) temp = temp->next;
  temp->next = novo;
}

void imprimirLista(Celula *head, const char *msg) {
  printf("%s: ", msg);
  Celula *temp = head;
  while (temp != NULL) {
    printf("%d -> ", temp->valor);
    temp = temp->next;
  }
  printf("NULL\n");
}

void liberarLista(Celula *head) {
  while (head != NULL) {
    Celula *temp = head;
    head = head->next;
    free(temp);
  }
}

void processarListaSemCabeca(Celula **head) {
  if (head == NULL || *head == NULL) return;
  int removidos = 0;
  Celula *curr = *head, *prev = NULL;

  while (curr != NULL && removidos < 3) {
    if (curr->valor > 10) {
      Celula *temp = curr;
      if (prev == NULL) *head = curr->next;
      else prev->next = curr->next;
      curr = curr->next;
      free(temp);
      removidos++;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  Celula *anterior = NULL, *atual = *head, *proximo = NULL;
  while (atual != NULL) {
    proximo = atual->next;
    atual->next = anterior;
    anterior = atual;
    atual = proximo;
  }
  *head = anterior;
}

void processarListaComCabeca(Celula *head) {
  if (head == NULL || head->next == NULL) return;
  int removidos = 0;
  Celula *prev = head, *curr = head->next;

  while (curr != NULL && removidos < 3) {
    if (curr->valor > 10) {
      Celula *temp = curr;
      prev->next = curr->next;
      curr = curr->next;
      free(temp);
      removidos++;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  Celula *anterior = NULL, *atual = head->next, *proximo = NULL;
  while (atual != NULL) {
    proximo = atual->next;
    atual->next = anterior;
    anterior = atual;
    atual = proximo;
  }
  head->next = anterior;
}

int main() {
  int valores[] = {1, 13, 42, 8, 4, 10, 11, 32, 64};
  int n = 9;

  // Teste 1: Sem Cabeça
  Celula *listaSemCabeca = NULL;
  for (int i = 0; i < n; i++) inserirFim(&listaSemCabeca, valores[i]);

  printf("--- TESTE LISTA SEM CABEÇA ---\n");
  imprimirLista(listaSemCabeca, "Original");
  processarListaSemCabeca(&listaSemCabeca);
  imprimirLista(listaSemCabeca, "Resultado");

  // Teste 2: Com Cabeça
  Celula *headNo = criarNo(-1); //cabeça
  for (int i = 0; i < n; i++) inserirFim(&(headNo->next), valores[i]);

  printf("\n--- TESTE LISTA COM CABEÇA ---\n");
  imprimirLista(headNo->next, "Original");
  processarListaComCabeca(headNo);
  imprimirLista(headNo->next, "Resultado");

  // Limpeza
  liberarLista(listaSemCabeca);
  liberarLista(headNo);

  return 0;
}