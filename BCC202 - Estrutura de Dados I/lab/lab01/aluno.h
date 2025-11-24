#ifndef ALUNO_H
#define ALUNO_H
#include <stdbool.h>

// structs
typedef struct {
  char *nome;
  char *tipo;
  int poder;
  bool repetido;
} Pokemon;

typedef struct {
  Pokemon *estoque;
  int qtdEstoque;
} Estoque;

// prototipos
void recebePokemons(Estoque *pokemons);
void verificaRepeticao(Pokemon pokemon, Estoque *pokemons);
void mostrarMaioresPorTipo(Estoque *pokemons);
void mostrarRepetidos(Estoque *pokemons);
void liberarEstoque(Estoque *pokemons);

#endif
