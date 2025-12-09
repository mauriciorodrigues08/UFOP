/*
Você foi contratado para desenvolver um módulo de um sistema acadêmico. O sistema armazena informações de alunos em um vetor. A estrutura de dados (struct) já foi definida da seguinte forma:
typedef struct{
  char nome [50];
  int matricula;
  int idade;
}Aluno;
*/

#include <stdio.h>
#include <string.h>

typedef struct {
  char nome [50];
  int matricula;
  int idade;
} Aluno;

//(a) Implemente a função void ordenaPorMatricula(Aluno *vet, int n) que ordene o vetor de alunos de forma crescente baseada na matrícula usando um algoritmo estável e in situ.
void ordenaPorMatricula(Aluno *vet, int n) {
  //algoritmo utilizado ->  insertion sort

  for (int i = 1; i < n; i++) {
    Aluno chave = vet[i];
    int j = i - 1;

    // Move elementos maiores para frente
    while (j >= 0 && vet[j].matricula > chave.matricula) {
      vet[j + 1] = vet[j];
      j--;
    }

    vet[j + 1] = chave;
  }
}

//(b) Implemente a função void ordenaPorNomeSelection(Aluno *vet, int n) que ordene o vetor em ordem alfabética baseada no nome usando  usando um algoritmo não estável e in situ.
void ordenaPorNomeSelection(Aluno *vet, int n) {
  //algoritmo utilizado -> selection sort

  for (int i = 0; i < n - 1; i++) {
    int min = i;

    // Encontra o menor nome no restante do vetor
    for (int j = i + 1; j < n; j++) {
      if (strcmp(vet[j].nome, vet[min].nome) < 0) {
        min = j;
      }
    }

    // Troca a posição atual com o mínimo encontrado
    if (min != i) {
      Aluno temp = vet[i];
      vet[i] = vet[min];
      vet[min] = temp;
    }
  }
}

void imprimeVetor(Aluno *vet, int n) {
  for (int i = 0; i < n; i++)
    printf("Nome: %-12s | Matricula: %d | Idade: %d\n", vet[i].nome, vet[i].matricula, vet[i].idade);
  printf("\n");
}

//testes das funções
int main() {
  // Caso que garante a inversão com Selection Sort (não-estável)
  Aluno alunos[] = {
    {"Joao",   50, 19},
    {"Carlos", 35, 20},
    {"Joao",   10, 21},
    {"Ana",    65, 27},
    {"Ana",    15, 27},
    {"Daniel", 30, 19},
    {"Joao",   80, 19},
    {"Bruno",  29, 23}
  };

  int n = 7;

  printf("======================= Vetor Original =======================\n");
  imprimeVetor(alunos, n);

  printf("===== Ordenando por Matricula (Insertion Sort - Estável) =====\n");
  ordenaPorMatricula(alunos, n);
  imprimeVetor(alunos, n);

  // Recria o vetor original para testar ordenação por nome
  Aluno alunos2[] = {
    {"Joao",   50, 19},
    {"Carlos", 35, 20},
    {"Joao",   10, 21},
    {"Ana",    65, 27},
    {"Ana",    15, 27},
    {"Daniel", 30, 19},
    {"Joao",   80, 19},
    {"Bruno",  29, 23}
  };

  printf("===== Ordenando por Nome (Selection Sort - Não Estável) =====\n");
  ordenaPorNomeSelection(alunos2, n);
  imprimeVetor(alunos2, n);

  return 0;
}
