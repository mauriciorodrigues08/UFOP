/*Faça um programa que preencha um vetor de inteiros 100 posições aleatoriamente com valores no intervalo [0,200). Leia um valor também inteiro. Mostre os valores separados menores e em maiores ou iguais do que o valor lido. Para gerar um número aleatório (randômico) em linguagem C podemos usar a função rand() pertencente à biblioteca stdlib.h. Muitas vezes necessitamos gerar valores dentro de determinada faixa. Para exemplificar, vamos supor que a faixa de valores desejada esteja entre o valor mínimo zero e o valor 100. Assim, para esse exemplo, utilizaremos o comandando "rand()%100", que gerará valores no intervalo [0,100). Além disso, a função srand() inicializa a função rand() com um valor “semente” para que se produza um valor aleatório na faixa determinada. A função srand() recebe um argumento do tipo inteiro sem sinal. Para a execução desse exercício, utilize a "semente" 10 - srand(10)*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 100

int main() {
  int v[TAM], mai[TAM], men[TAM], n;

  //gerando números aleatórios
  srand(10);
  for (int i=0; i<TAM; i++)
    v[i] = rand()%200;
  
  //recebendo valor de n
  printf("Digite um número: ");
  scanf("%d", &n);
  
  //analisando maiores e menores
  for (int i=0; i<TAM; i++) {
    if (v[i] >= n) {
      mai[i] = v[i];
      men[i] = 99999;
    }else {
      men[i] = v[i];
      mai[i] = 99999;
    }
  }

  //printando resultado
  //maiores
  printf("\nMaiores:\n");
  for (int i=0; i<TAM; i++) {
    if (mai[i] != 99999)
      printf("%d ", mai[i]);
  }
  printf("\n");
  
  //menores
  printf("\nMenores:\n");
  for (int i=0; i<TAM; i++) {
    if (men[i] != 99999)
      printf("%d ", men[i]);
  }
  printf("\n");
  
  return 0;
}