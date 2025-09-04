/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <string.h>
#define TAM 4

typedef struct {
  char nome[15];
  float consumo; // em kW/h
  float tempo;   // em horas por dia
} Eletrod;

float consumoTotal(Eletrod *eletrodomesticos, int dias);
void porcentagem(Eletrod *eletrodomesticos, float consTotal, int dias);

int main() {
  Eletrod eletrodomesticos[TAM];
  int tam, dias;
  float consTotal;

  // recebendo dados dos eletrodomésticos
  for (int i = 0; i < TAM; i++) {
    if (i > 0)
      getchar();

    printf("\nEletrodoméstico %d\n", i);
    printf("Nome: ");
    fgets(eletrodomesticos[i].nome, 15, stdin);
    tam = strlen(eletrodomesticos[i].nome);
    if (tam < 15 && eletrodomesticos[i].nome[tam - 1] == '\n')
      eletrodomesticos[i].nome[tam - 1] = '\0';

    printf("Consumo (kW/h): ");
    scanf("%f", &eletrodomesticos[i].consumo);

    printf("Tempo ativo em horas: ");
    scanf("%f", &eletrodomesticos[i].tempo);
  }

  printf("\nNúmero de dias para cálculo: ");
  scanf("%d", &dias);

  consTotal = consumoTotal(eletrodomesticos, dias);
  printf("Consumo total: %.1f kW\n", consTotal);

  porcentagem(eletrodomesticos, consTotal, dias);

  printf("\n");
  return 0;
}

float consumoTotal(Eletrod *eletrodomesticos, int dias) {
  float total = 0;
  for (int i = 0; i < TAM; i++)
    total += eletrodomesticos[i].consumo * eletrodomesticos[i].tempo;

  return total * dias;
}

void porcentagem(Eletrod *eletrodomesticos, float consTotal, int dias) {
  float porcentagem;
  printf("\nPorcentagens:\n");

  for (int i = 0; i < TAM; i++) {
    float consumo_i = eletrodomesticos[i].consumo * eletrodomesticos[i].tempo * dias;
    porcentagem = (consumo_i * 100) / consTotal;
    printf("%s %.2f%%\n", eletrodomesticos[i].nome, porcentagem);
  }
}