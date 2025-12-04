// Considere uma lista encadeada simples destinada a armazenar registros de pessoas, contendo nome e idade. Implemente uma função de inserção ordenada, que adiciona uma nova pessoa à lista mantendo-a organizada de forma crescente pela idade. Implemente uma função de impressão que percorra a lista e exiba o nome e a idade de todos os registros. Analise e indique a complexidade das duas funções implementadas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct pessoa {
  char nome[21];
  int idade;
  struct pessoa *prox;
} Pessoa;

typedef struct lista {
  Pessoa *cabeca;
} Lista;

Lista* ListaCria() {
  Lista *lista = (Lista *) malloc(sizeof(Lista));
  if (!lista)
    return NULL;

  lista->cabeca = (Pessoa *) malloc(sizeof(Pessoa));
  if (!lista->cabeca) {
    free(lista);
    return NULL;
  }

  lista->cabeca->prox = NULL;
  return lista;
}

Pessoa* PessoaCria(char *nome, int idade) {
  Pessoa *nova = (Pessoa *) malloc(sizeof(Pessoa));
  if (!nova)
    return NULL;

  strcpy(nova->nome, nome);
  nova->idade = idade;
  nova->prox = NULL;
  return nova;
}

//inserção ordenada por idade
bool ListaInsereOrdenado(Lista *lista, char *nome, int idade) {
  if (!lista)
    return false;

  Pessoa *nova = PessoaCria(nome, idade);
  if (!nova)
    return false;

  Pessoa *atual = lista->cabeca;

  //procurar posição mantendo ordem crescente
  while (atual->prox != NULL && atual->prox->idade <= idade) {
    atual = atual->prox;
  }

  nova->prox = atual->prox;
  atual->prox = nova;

  return true;
}

void ListaPrint(Lista *lista) {
  if (!lista)
    return;

  Pessoa *atual = lista->cabeca->prox;

  printf("\nLista de pessoas:\n");
  while (atual != NULL) {
    printf("%s | %d\n", atual->nome, atual->idade);
    atual = atual->prox;
  }
}

void ListaDestroi(Lista *lista) {
  if (!lista)
    return;

  Pessoa *atual = lista->cabeca;
  while (atual != NULL) {
    Pessoa *proxPessoa = atual->prox;
    free(atual);
    atual = proxPessoa;
  }

  free(lista);
}

int main() {
  Lista *lista = ListaCria();
  if (!lista)
    return 0;

  printf("\n--- Inserindo pessoas na lista ---\n");

  ListaInsereOrdenado(lista, "Mauricio", 22) ? printf("Mauricio adicionado\n") : printf("Mauricio nao adicionado\n");

  ListaInsereOrdenado(lista, "Joao", 19) ? printf("Joao adicionado\n") : printf("Joao nao adicionado\n");

  ListaInsereOrdenado(lista, "Ana", 30) ? printf("Ana adicionada\n") : printf("Ana nao adicionada\n");

  ListaInsereOrdenado(lista, "Pedro", 25) ? printf("Pedro adicionado\n") : printf("Pedro nao adicionado\n");

  ListaInsereOrdenado(lista, "Lucas", 19) ? printf("Lucas adicionado\n") : printf("Lucas nao adicionado\n");

  printf("\n--- Lista atual (ordenada por idade) ---\n"); 
  ListaPrint(lista);

  printf("\n--- Inserindo mais pessoas ---\n");

  ListaInsereOrdenado(lista, "Camila", 20) ? printf("Camila adicionada\n") : printf("Camila nao adicionada\n");

  ListaInsereOrdenado(lista, "Viviane", 27) ? printf("Viviane adicionado\n") : printf("Viviane nao adicionado\n");

  printf("\n--- Lista atual (ordenada por idade) ---\n");
  ListaPrint(lista);

  ListaDestroi(lista);

  return 0;
}
