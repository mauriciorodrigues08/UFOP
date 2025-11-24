#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_TAM 10

// structs
typedef struct{
	int chave;
}Registro;

typedef struct{
	Registro registro[MAX_TAM];
	int primeiro;
	int ultimo;
} Lista;

// prototipos
void listaCria(Lista list);
bool listaEhVazia(Lista list);
int listaTamanho(Lista list);
bool listaInsere(Lista list, int conteudo);
bool listaRetira(Lista list, int chave);

// implementacoes
void listaCria(Lista list){
  list.primeiro = 0;
  list.ultimo = 0;
}

bool listaEhVazia(Lista list){
  return (listaTamanho(list) == 0? true : false);
}

int listaTamanho(Lista list){
  return list.ultimo - list.primeiro;
}

bool listaInsere(Lista list, int conteudo){
  if(list.ultimo >= MAX_TAM)
    return false;
  
  list.registro[list.ultimo].chave = conteudo;
  list.ultimo++;

  return true;
}

bool listaRetira(Lista list, int chave){
  if(listaEhVazia(list))
    return false;

  bool chaveEncontrada = false;
  int pos;
  for(int i = list.primeiro; i < list.ultimo; i++){
    if(list.registro[i].chave == chave){
      chaveEncontrada = true;
      pos = i;
      break;
    }
  }

  if(!chaveEncontrada)
    return chaveEncontrada;
  
  for(int i = pos; i < list.ultimo - 1; i++)
    list.registro[i].chave = list.registro[i + 1].chave;

  list.registro[list.ultimo].chave = 0;
  list.ultimo -= 1;

  return true;
}