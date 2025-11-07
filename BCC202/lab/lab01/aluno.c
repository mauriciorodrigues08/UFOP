//imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aluno.h"

//funcoes

//recebe pokemons recursivamente
void recebePokemons(Estoque *pokemons) {
  Pokemon pokemon;
  char nomeTemp[50], tipoTemp[50];

  scanf("%s", nomeTemp);

  // caso base (valor digitado == 0)
  if (!strcmp(nomeTemp, "0")) return;

  // caso nao seja 0, continua recebendo valores
  scanf("%s %d", tipoTemp, &pokemon.poder);

  // aloca memória e copia as strings
  pokemon.nome = malloc(strlen(nomeTemp) + 1);
  strcpy(pokemon.nome, nomeTemp);

  pokemon.tipo = malloc(strlen(tipoTemp) + 1);
  strcpy(pokemon.tipo, tipoTemp);

  pokemon.repetido = false;

  // adiciona ao estoque
  pokemons->estoque = realloc(pokemons->estoque, (pokemons->qtdEstoque + 1) * sizeof(Pokemon));
  pokemons->estoque[pokemons->qtdEstoque] = pokemon;
  pokemons->qtdEstoque++;

  // marca repetidos
  verificaRepeticao(pokemon, pokemons);

  // chamada recursiva
  recebePokemons(pokemons);
}

// marca se o pokemon e repetido
void verificaRepeticao(Pokemon pokemon, Estoque *pokemons) {
  for (int i = 0; i < pokemons->qtdEstoque - 1; i++) {
    if (!strcmp(pokemons->estoque[i].nome, pokemon.nome) && !strcmp(pokemons->estoque[i].tipo, pokemon.tipo)) {
      pokemons->estoque[i].repetido = true;
      pokemons->estoque[pokemons->qtdEstoque - 1].repetido = true;
    }
  }
}

// printa o pokemon com maior poder por tipo
void mostrarMaioresPorTipo(Estoque *pokemons) {
  for (int i = 0; i < pokemons->qtdEstoque; i++) {
    bool novoTipo = true;

    // verifica se este tipo já foi mostrado
    for (int j = 0; j < i; j++) {
      if (!strcmp(pokemons->estoque[i].tipo, pokemons->estoque[j].tipo)) {
        novoTipo = false;
        break;
      }
    }

    if (novoTipo) {
      int indiceMaior = i;
      for (int k = i + 1; k < pokemons->qtdEstoque; k++) {
        if (strcmp(pokemons->estoque[i].tipo, pokemons->estoque[k].tipo) == 0 && pokemons->estoque[k].poder > pokemons->estoque[indiceMaior].poder) {
          indiceMaior = k;
        }
      }
      printf("%s: %s\n", pokemons->estoque[i].tipo, pokemons->estoque[indiceMaior].nome);
    }
  }
}

// printa os pokemons repetidos
void mostrarRepetidos(Estoque *pokemons) {
  bool temRepetidos = false;

  for (int i = 0; i < pokemons->qtdEstoque; i++) {
    if (pokemons->estoque[i].repetido) {
      bool jaMostrado = false;

      // evita mostrar o mesmo nome duas vezes
      for (int j = 0; j < i; j++) {
        if (strcmp(pokemons->estoque[i].nome, pokemons->estoque[j].nome) == 0 && strcmp(pokemons->estoque[i].tipo, pokemons->estoque[j].tipo) == 0) {
          jaMostrado = true;
          break;
        }
      }
      if (!jaMostrado) {
        printf("%s\n", pokemons->estoque[i].nome);
        temRepetidos = true;
      }
    }
  }

  if (!temRepetidos)
    printf("Nenhum Pokémon repetido.\n");
}

// libera a memoria alocada
void liberarEstoque(Estoque *pokemons) {
  for (int i = 0; i < pokemons->qtdEstoque; i++) {
    free(pokemons->estoque[i].nome);
    free(pokemons->estoque[i].tipo);
  }
  free(pokemons->estoque);
  pokemons->estoque = NULL;
  pokemons->qtdEstoque = 0;
}
