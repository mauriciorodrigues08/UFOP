/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <string.h>

typedef struct {
  char modelo[25];
  float consumo;
} Carro;

void maisEconomico(Carro *carros);
void print(Carro *carros);

int main() {
  Carro carros[5];
  int tam;
  
  for (int i=0; i<5; i++) {
    printf("\nCarro %d", i);
    if (i>0)
      getchar();
    
    //modelo
    printf("\nModelo: ");
    fgets(carros[i].modelo, 25, stdin);
    tam = strlen(carros[i].modelo);
    if (tam < 25)
      carros[i].modelo[tam-1] = '\0';
      
    //consumo
    printf("Consumo (km/l): ");
    scanf("%f", &carros[i].consumo);
  }
  
  //verificando carro mais economico
  maisEconomico(carros);
  
  //printando resultado
  print(carros);
  
  printf("\n");
  return 0;
}

void maisEconomico(Carro *carros) {
  float maior = -99999;
  int n;
  
  for (int i=0; i<5; i++)
    if(carros[i].consumo > maior) {
      maior = carros[i].consumo;
      n = i;
  }
  printf("\nMais econômico: %s\n", carros[n].modelo); 
}

void print(Carro *carros) {
  float cons;
  printf("\nConsumo em 1000 km\n");
  for (int i=0; i<5; i++) {
    cons = 1000.0 / carros[i].consumo;
    printf("\n%s %.2f", carros[i].modelo, cons);
  }
}







