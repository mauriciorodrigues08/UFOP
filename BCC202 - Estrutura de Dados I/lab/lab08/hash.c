#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Manter como especificado
void inicia (Hash *hash, int m, int p) {
  //aloca e inicializa os valores da hash
  hash->m = m;
  hash->p = p;
  hash->chaves = (Chave*) malloc(m * sizeof(Chave));
  hash->pesos = (int*) malloc(p * sizeof(int));
  
  for (int i = 0; i < m; i++) {
    hash->chaves[i][0] = '\0';
  }
}

// Manter como especificado
void libera(Hash *hash) {
  //libera a memoria alocada para a hash
  free(hash->chaves);
  free(hash->pesos);
}

// Função auxiliar para tratar a chave (alfabéticos e case insensitive)
void limpaChave(Chave destino, char* origem) {
  //se o caracter for alfanumerico transforma para minusculo
  int j = 0;
  int i = 0;
  while(origem[i] != '\0' && j < 10) {  
    if (isalpha(origem[i])) {
      destino[j++] = tolower(origem[i]);
    } 
    i++;
  }
  destino[j] = '\0';
}

int H(Hash* hash, Chave chave) {
  long long soma = 0;
  int tam = strlen(chave);

  //acumula o valor de cada letra da chave mult. por um peso do vetor circular
  for (int i = 0; i < tam; i++) {
    soma += (long long)chave[i] * hash->pesos[i % hash->p];
  }

  //retorna a posicao esperada na hash
  return (int)(soma % hash->m);
}

// Manter como especificado
int insere (Hash *hash, Chave chave) {
  Chave chave_limpa;
  limpaChave(chave_limpa, chave);
  
  //verifica se já existe (case insensitive)
  for (int i = 0; i < hash->m; i++) {
    if (hash->chaves[i][0] != '\0' && strcmp(hash->chaves[i], chave_limpa) == 0) {
      return -1; //chave repetida
    }
  }

  int pos_original = H(hash, chave);
  int pos;
  
  //endereçamento aberto
  for (int i = 0; i < hash->m; i++) {
    pos = (pos_original + i) % hash->m;

    if (hash->chaves[pos][0] == '\0') {
      strcpy(hash->chaves[pos], chave_limpa);
      return pos; //retorna a posição de inserção
    }
  }

  //caso nao encontre nenhuma posicao disponivel
  return -1;
}
