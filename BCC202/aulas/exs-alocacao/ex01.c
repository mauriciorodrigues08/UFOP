/*Implemente uma função que recebe um vetor de números reais e tenha como valor de retorno um novo vetor, alocado dinamicamente, com os elementos do vetor original em ordem inversa. A função deve ter como retorno o valor do ponteiro alocado, conforme protótipo a seguir:
- float * reverso ( int n , float * v);
Faça uma função main() para testar sua função. Não esqueça de liberar a memória alocada em tempo de execução.*/

#include <stdio.h>
#include <stdlib.h>

// Protótipo da função
float *reverso(int n, const float *v);

int main() {
  int n;

  // Recebendo quantidade de valores do vetor
  printf("Digite a quantidade de valores do vetor: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Quantidade inválida.\n");
    return 1;
  }

  // Alocando vetor original
  float *vet = (float *) malloc(n * sizeof(float));
  if (vet == NULL) {
    printf("Erro ao alocar memória para o vetor original.\n");
    return 1;
  }

  // Recebendo valores
  printf("Digite os %d valores: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%f", &vet[i]) != 1) {
      printf("Entrada inválida.\n");
      free(vet);
      return 1;
    }
  }

  // Chamando a função reverso()
  float *vetReverso = reverso(n, vet);
  if (vetReverso == NULL) {
    printf("Erro ao alocar memória para o vetor reverso.\n");
    free(vet);
    return 1;
  }

  // Exibindo vetor invertido
  printf("Vetor invertido: ");
  for (int i = 0; i < n; i++) {
    printf("%f ", vetReverso[i]);
  }
  printf("\n");

  // Liberando memória
  free(vet);
  free(vetReverso);

  return 0;
}

// Função que cria um novo vetor com os elementos em ordem inversa
float *reverso(int n, const float *v) {
    float *r = (float *) malloc(n * sizeof(float));
    if (r == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        r[i] = v[n - 1 - i];
    }

    return r;
}
