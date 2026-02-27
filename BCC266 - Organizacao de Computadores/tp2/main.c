#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ram.h"
#include "maquina.h"


int instru_gener(int numPalavras, int tamRam);

void printResultado(Maquina *maquina);
void calculaPorcentagem(Maquina *maquina, double *pct1, double *pct2, double *pct3, double *pctRam);

int main(){
  //define a seed aleatória
  srand(time(NULL));

  //Pega o tempo inicial
  clock_t inicio = clock();

  //cria arquivo com as instruções
  int num_instrucoes = instru_gener(NUM_PALAVRAS, TAM_RAM);

  //cria e aloca o vetor de instruções
  Instrucao *instrucoes = criaInstrucoes(num_instrucoes);

  //cria a máquina
  Maquina *maquina = criaMaquina();

  //lê as instruções do arquivo gerado
  recebe_instrucoes(instrucoes, num_instrucoes);

  //roda a máquina
  iniciar(maquina, instrucoes);

  //printa resultado
  printResultado(maquina);

  //libera vetor de instruções e máquina
  destroiInstrucoes(instrucoes);
  destroiMaquina(maquina);

  //Pega o tempo final
  clock_t final = clock();

  //Calcula o tempo de execução
  double tempo = (double)(final - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %.2lf\n\n", tempo);

  return 0;
}

int instru_gener(int numPalavras, int tamRam){
  int qtd_inst = 10000;
  int qtd_for = 5;
  int qtd_wrds = numPalavras;
  int tam_ram = tamRam;
  int prob = 50;

  printf("\nInsira a quantidade de instruções (Padrão: 10000): ");
  scanf("%d", &qtd_inst);
  qtd_inst++;
  printf("\nInsira a quantidade de for (Padrão: 5): ");
  scanf("%d", &qtd_for);
  printf("\nInsira a probabilidade (Padrão: 50): ");
  scanf("%d", &prob);

  //Abre o arquivo
  FILE *arquivo = fopen("instrucoes.txt", "w");

  //Variaveis
  int inst[qtd_inst][7];
  int rep[qtd_for][7];
  int aux;
  
  //Gera as instruções que vão se repetir
  for(int i = 0; i < qtd_for; i++){
      rep[i][0] = rand() % 3;
      for(int j = 1; j < 7; j++){
          rep[i][j] = rand() % tam_ram;
          rep[i][++j] = rand() % qtd_wrds;
      }
  }

  for(int i = 0; i < qtd_inst;){
      aux = (rand() % 100) + 1;
      if(aux <= prob && i + qtd_for < qtd_inst){
          for(int j = 0; j < qtd_for; j++){
              for(int k = 0; k < 7; k++)
                  inst[i + j][k] = rep[j][k];
          }
          i += qtd_for;
      }
      else{
          inst[i][0] = rand() % 3;
          for(int j = 1; j < 7; j++){
              inst[i][j] = rand() % tam_ram;
              inst[i][++j] = rand() % qtd_wrds;
          }
          i++;
      } 
  }

  inst[qtd_inst - 1][0] = -1; 

  for(int i = 0; i < qtd_inst; i++){
      for(int j = 0; j < 6; j++)
          fprintf(arquivo, "%d ", inst[i][j]);
      fprintf(arquivo, "%d\n", inst[i][6]);
  }


  fclose(arquivo);
  return qtd_inst;
}

void printResultado(Maquina *maquina){
  long int hit_miss_cache1[2] = {maquina->cache1->cacheHit, maquina->cache1->cacheMiss};
  long int hit_miss_cache2[2] = {maquina->cache2->cacheHit, maquina->cache2->cacheMiss};
  long int hit_miss_cache3[2] = {maquina->cache3->cacheHit, maquina->cache3->cacheMiss};

  double porcentagem1, porcentagem2, porcentagem3, porcentagemRam;

  calculaPorcentagem(maquina, &porcentagem1, &porcentagem2, &porcentagem3, &porcentagemRam);

  printf("\n================ RESULTADOS ================\n");
  printf("Ciclos estimados da maquina: %ld\n", maquina->ciclos);
  printf("Custo total: %ld\n", maquina->custo);
  printf("============================================\n");
  printf("Cache 1 -> Hit: %5ld | Miss: %5ld | %.2lf%%\n", hit_miss_cache1[0], hit_miss_cache1[1], porcentagem1);
  printf("Cache 2 -> Hit: %5ld | Miss: %5ld | %.2lf%%\n", hit_miss_cache2[0], hit_miss_cache2[1], porcentagem2);
  printf("Cache 3 -> Hit: %5ld | Miss: %5ld | %.2lf%%\n", hit_miss_cache3[0], hit_miss_cache3[1], porcentagem3);
  printf("RAM     -> Hit: %5ld |      -      | %.2lf%%\n", maquina->ram->ramHit, porcentagemRam);
  printf("============================================\n");
}

void calculaPorcentagem(Maquina *maquina, double *pct1, double *pct2, double *pct3, double *pctRam){
  double result;
  double soma = 0;

  soma += maquina->cache1->cacheHit;
  soma += maquina->cache2->cacheHit;
  soma += maquina->cache3->cacheHit;
  soma += maquina->ram->ramHit;

  result = (double) maquina->cache1->cacheHit/soma;
  *pct1 = (double) (100 * result);

  result = (double) maquina->cache2->cacheHit/soma;
  *pct2 = (double) (100 * result);
  
  result = (double) maquina->cache3->cacheHit/soma;
  *pct3 = (double) (100 * result);

  result = (double) maquina->ram->ramHit/soma;
  *pctRam = (double) (100 * result);
}
