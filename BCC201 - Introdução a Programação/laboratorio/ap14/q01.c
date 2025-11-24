/*
Nome: Maurício de Oliveira Santos Rodrigues
Matrícula: 25.1.4020
*/

#include <stdio.h>

typedef struct {
  char ident;
  float coordX, coordY;
} Ponto;

void limpar_buffer();

int main() {
  Ponto pontos[5];
  int n;
  char nomeArq[50];
  
  //recebendo dados dos pontos
  printf("Digite o número de pontos:");
  scanf("%d", &n);
  
  for (int i=0; i<n; i++) {
    printf("Ponto %d\nDigite o identificador, a coord. x e coord. y:", i+1 );
    limpar_buffer();
    scanf("%c %f%f", &pontos[i].ident, &pontos[i].coordX, &pontos[i].coordY);
  }
  
  //recebendo nome para salvamento
  printf("Digite o nome do arquivo para salvamento:");
  limpar_buffer();
  scanf("%s", nomeArq);
  
  //passando valores para o arquivo
  FILE *file = fopen(nomeArq, "w");
  fprintf(file, "%d\n", n);
  for (int i=0; i<n; i++)
    fprintf(file, "%c %.1f %.1f\n", pontos[i].ident, pontos[i].coordX, pontos[i].coordY);
  
  fclose(file);

  return 0;
}

void limpar_buffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);  
}