// L1 {a^n b^n | n>=0} tem a mesma quantidade de a's e b's na ordem
// L2 {w|w} tem a mesma quantidade de a's e b's

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define TAM_MAX 300

// prototipo das funcoes utilizadas
bool reconheceL1(char *entrada, int *qtdA, int *qtdB, int indice, int tamanho);
bool reconheceL2(char *entrada, int *qtdA, int *qtdB, int tamanho);

// metodo main
int main() {
  // declaracao de variaveis
  char entrada[TAM_MAX];
  int qtdA = 0, qtdB = 0, indice = 0;
  bool pertenceL1, pertenceL2;

  // recebendo entrada
  scanf("%s", entrada);
  int tam = strlen(entrada);

  // verifica se pertence a L2
  pertenceL2 = reconheceL2(entrada, &qtdA, &qtdB, tam);

  // verifica se pertence a L1
  if (pertenceL2) pertenceL1 = reconheceL1(entrada, &qtdA, &qtdB, indice, tam);
  else pertenceL1 = false;

  // printando resultados
  pertenceL1 ? printf("\nPertence a linguagem L1") : printf("\nNão pertence a linguagem L1");
  pertenceL2 ? printf("\nPertence a linguagem L2") : printf("\nNão pertence a linguagem L2");
  
  printf("\n");
  return 0;
}

// funcao recursiva que verifica se a entrada pertence a L1
bool reconheceL1(char *entrada, int *qtdA, int *qtdB, int indice, int tamanho) {
  // casos base
  if (indice == tamanho) return true;
  
  // verifica ordem das letras
  if (entrada[indice] == 'b' && entrada[indice+1] == 'a') return false;
  //chamada recursiva
  return reconheceL1(entrada, qtdA, qtdB, indice+1, tamanho);
}

// funcao que verifica se a entrada pertence a L1
bool reconheceL2(char *entrada, int *qtdA, int *qtdB, int tamanho) {
  for (int i=0; i<tamanho; i++) {
    (entrada[i] == 'a') ? (*qtdA)++ : (*qtdB)++;
  }

  if (*qtdA == *qtdB) return true;
  else return false;
}
