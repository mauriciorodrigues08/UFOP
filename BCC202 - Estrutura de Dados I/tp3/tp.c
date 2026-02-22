//imports
#include <stdio.h>
#include <stdlib.h>

//modulos
#include "filaprocessos.h"

//main
int main(){
  //cria variavel de erro
  Erro erro;
  erro.tipo = 0;
  
  //cria pilha de execucao
  Pilha *pilha;
  pilha = criarPilha();

  //executa o programa
  executar(pilha, &erro);

  //printa mensagem de erro, se necessario
  if(erro.tipo != 0)
    printf("%s\n", erro.mensagemErro);

  //libera memoria alocada para a pilha
  free(pilha);

  return 0;
}