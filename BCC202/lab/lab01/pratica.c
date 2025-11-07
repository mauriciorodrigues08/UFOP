// ler "infinitas" entradas com "nome" "tipo" e pontos de poder
// entradas encerram ao ser digitado o valor 0
// separar por tipo
// avaliar maior pontos de poder por cada tipo
// avaliar todos os repetidos

#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
  // inicializando estoque
  Estoque pokemons;
  pokemons.estoque = NULL;
  pokemons.qtdEstoque = 0;

  //recebendo e manpulando valores
  recebePokemons(&pokemons);

  //printando resultados
  printf("\nMaior PC por tipo:\n");
  mostrarMaioresPorTipo(&pokemons);

  printf("\nRepetidos:\n");
  mostrarRepetidos(&pokemons);

  //liberando memoria alocada
  liberarEstoque(&pokemons);

  return 0;
}
