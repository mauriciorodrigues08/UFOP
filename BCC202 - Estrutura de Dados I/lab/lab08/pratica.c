#include <stdio.h>

#include "hash.h"


int main() {
  Hash hash;
  Chave chave;
  int n, tam_tabela, tam_pesos, num_chaves, ultima_pos;

  // Ler a quantidade de casos
  scanf("%d", &n);
  
  while (n-- > 0) {
    // Lendo tamanho da tabela e quantidade de pesos
    scanf("%d %d", &tam_tabela, &tam_pesos);
    
    // Iniciar Hash
    inicia(&hash, tam_tabela, tam_pesos);
    
    // Lendo pesos
    for (int i = 0; i < tam_pesos; i++) {
      scanf("%d", &hash.pesos[i]);
    }

    // Lendo quantidade de chaves
    scanf("%d", &num_chaves);
    ultima_pos = -1;
    
    // Lendo chaves
    for (int i = 0; i < num_chaves; i++) {
      scanf("%s", chave);
      ultima_pos = insere(&hash, chave);
    }
    
    // Imprimir resposta
    printf("%d\n", ultima_pos);
    
    // Liberar Hash
    libera(&hash);
  }
  
  return 0;
}