/*
Nome: Maurício de Oliveira Santos Rodrigues
Matricula: 25.1.4020
*/

#include <stdio.h>
#include <math.h>
#define MAX 20

typedef struct {
  double x, y;
} Ponto;

int main() {
  Ponto pontos[MAX], menorDist, maiorDist;
  double dist[MAX], maior = -99999, menor = 99999;
  int n;

  printf("Digite o número de pontos (0 < n <= 20): ");
  scanf("%d", &n);
  do {
    if (n<1 || n>20) {
      printf("Valor inválido. Digite o número de pontos: ");
      scanf("%d", &n);
    }
  } while(n<1 || n>20);

  printf("\n");
  for (int i=0; i<n; i++) {
    //recebendo pontos
    printf("Digite as coordenadas x e y do ponto %d: ", i+1);
    scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
    
    //calculando distancia
    dist[i] = sqrt( pow(pontos[i].x, 2) + pow(pontos[i].y, 2));
    
    //verificando se é maior ou menor
    if (dist[i] > maior)
      maior = dist[i];
      maiorDist.x = pontos[i].x;
      maiorDist.y = pontos[i].y;

    if (dist[i] < menor)
      menor = dist[i];
      menorDist.x = pontos[i].x;
      menorDist.y = pontos[i].y;
  }

  //imprimindo resultado
  printf("\nDistâncias dos pontos até a origem: \n");
  for (int i=0; i<n; i++) {
    printf("P(%.1f, %.1f): %.1f\n", pontos[i].x, pontos[i].y, dist[i]);
  } 

  printf("\nMenor distância: P(%.1f, %.1f) = %.1f\n", menorDist.x, menorDist.y, menor);
  printf("Maior distância: P(%.1f, %.1f) = %.1f\n", maiorDist.x, maiorDist.y, maior);

  return 0;
}