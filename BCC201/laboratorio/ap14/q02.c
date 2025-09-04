/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>
#include <math.h>

typedef struct {
  char ident;
  float coordX, coordY;
}Ponto;

void limpar_buffer();
float dist2Pontos(Ponto a, Ponto b);

int main() {
  Ponto pontos[3];
  char nomeArq[50], lixo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", nomeArq);
  
  //abrindo arquivo e lendo dados
  FILE *file = fopen(nomeArq, "r");
  int n;
  fscanf(file, "%d%c", &n, &lixo);

  for(int i = 0; i < 3; i++){
    fscanf(file, "%c%f%f%c", &pontos[i].ident, &pontos[i].coordX, &pontos[i].coordY, &lixo);
  }
  fclose(file);


  float aux;
  for (int i=1; i<3; i++) {
    aux = dist2Pontos(pontos[0], pontos[i]);
    printf("Distância entre %c e %c: %.2f\n", pontos[0].ident, pontos[i].ident, aux);
  }

  return 0;
}

float dist2Pontos(Ponto a, Ponto b) {
  float temp;
  temp = sqrt(pow(a.coordX - b.coordX, 2) + pow(a.coordY - b.coordY, 2));
  return  temp;

}