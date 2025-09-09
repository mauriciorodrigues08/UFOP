// Maurício de Oliveira Santos Rodrigues

#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main() {
  //definição da semente random
  srand(time(NULL));
  
  //execução do jogo
  limpa_terminal();
  game();
  
  return 0;
}
