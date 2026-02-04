#include <stdio.h>

#define MAX 100 // Tamanho máximo do vetor

// Estrutura simples para controle do vetor
typedef struct {
  int A[MAX];
  int n; // Quantidade atual de elementos
} Lista;

// Retorna o índice do elemento ou -1 se não encontrado
int buscaSequencial(Lista *l, int chave) {
  int i;
  for (i = 0; i < l->n; i++) {
    if (l->A[i] == chave) {
      return i; // Elemento encontrado
    }
  }
  
  return -1; // Elemento não encontrado
}

// Insere no final do vetor se houver espaço
int inserir(Lista *l, int valor) {
  if (l->n >= MAX) {
    printf("Erro: Lista cheia!\n");
    return 0; // Falha na inserção
  }
  
  l->A[l->n] = valor;
  l->n++; // Incrementa o contador de elementos
  return 1; // Sucesso
}

// Main para testes
int main() {
  Lista lista;
  lista.n = 0; // Inicializa lista vazia

  inserir(&lista, 10);
  inserir(&lista, 45);
  inserir(&lista, 23);

  int posicao = buscaSequencial(&lista, 45);
  
  if (posicao != -1) {
    printf("Valor encontrado no indice: %d\n", posicao);
  } else {
    printf("Valor nao encontrado.\n");
  }

  return 0;
}