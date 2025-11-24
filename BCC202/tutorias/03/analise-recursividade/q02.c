#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Temos um TAD cidade que contém as seguintes informações: nome da cidade, número de habitantes(em milhões) e número de escolas.
typedef struct cidade {
    char nome[21];
    double milhoesHabit;
    int escolas;
} Cidade;

// (a) Implemente uma função para alocar memória para a estrutura a ser preenchida e outra para desalocar.
Cidade* alocarCidades(int n) {
  Cidade* vet = (Cidade*) malloc(n * sizeof(Cidade));
  return vet;
}

void desalocarCidades(Cidade* cidades) {
  free(cidades);
}

// (b) Implemente uma função recursiva chamada int cidadeComMaisEscolas(Cidade* cidades, int num) que encontra e retorna o índice da cidade com o maior número de escolas. Qual é a complexidade de tempo da função no pior caso?
int cidadeComMaisEscolas(Cidade* cidades, int num) {
  if (num == 1)
    return 0;

  int indiceAnterior = cidadeComMaisEscolas(cidades, num-1);

  if (cidades[num-1].escolas > cidades[indiceAnterior].escolas)
    return num-1;
  else
    return indiceAnterior;
}

// (c) Implemente uma função recursiva chamada double calcularHabitantes(Cidade* cidades, int num) que calcula e retorna a população total(em milhões)de todas as cidades no array.
double calcularHabitantes(Cidade* cidades, int num) {
  if (num == 1)
    return cidades[0].milhoesHabit;

  return cidades[num-1].milhoesHabit + calcularHabitantes(cidades, num-1);
}

// (d) Implemente uma função recursiva void imprimeCidadePequena(Cidade* cidades, int num, int populacao) que imprime todas as cidades que possuem uma população menor que determinado número. Após isso, indique a equação de recorrência e sua complexidade.
void imprimeCidadePequena(Cidade* cidades, int num, int populacao) {
  if (num == 0)
    return;

  imprimeCidadePequena(cidades, num-1, populacao);

  if (cidades[num-1].milhoesHabit < populacao) {
    printf("Cidade: %s | Habitantes: %.2f milhões | Escolas: %d\n", cidades[num - 1].nome, cidades[num - 1].milhoesHabit, cidades[num - 1].escolas);
  }
} 

// main para teste das funções
int main() {
  int n;

  // recebendo quantidade de cidades
  printf("Quantas cidades deseja cadastrar? ");
  scanf("%d", &n);
  
  // preenchendo cidades
  Cidade* cidades = alocarCidades(n);

  for (int i = 0; i < n; i++) {
      printf("\nCidade %d:\n", i + 1);
      printf("Nome: ");
      getchar();
      fgets(cidades[i].nome, 21, stdin);
      int tam = strlen(cidades[i].nome);
      cidades[i].nome[tam-1] = '\0';
      
      printf("Habitantes (em milhões): ");
      scanf("%lf", &cidades[i].milhoesHabit);
      
      printf("Número de escolas: ");
      scanf("%d", &cidades[i].escolas);
  }

  // print resultados
  int indice = cidadeComMaisEscolas(cidades, n);

  printf("\n===== RESULTADOS =====\n");
  
  printf("Cidade com mais escolas: %s (%d escolas)\n", cidades[indice].nome, cidades[indice].escolas);
  printf("População total: %.2f milhões\n", calcularHabitantes(cidades, n));
  
  printf("\nCidades com populacao menor que 2 milhões:\n");
  imprimeCidadePequena(cidades, n, 2);
  
  desalocarCidades(cidades);
  return 0;
}
