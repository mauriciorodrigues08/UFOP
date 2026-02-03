//imports
#include <stdio.h>
#include <stdlib.h>

//modulos
#include "fila.h"

int main() {
  int n; //qtd de processos
  
  //recebendo quantidade de processos
  scanf("%d", &n);
  
  //alocando vetor auxiliar de processos
  Processo *auxVet = (Processo *) malloc(n * sizeof(Processo));
  
  //recebendo processos
  for (int i=0; i<n; i++) {
    //adicionando processo ao vetor auxiliar
    scanf("%d %f %d %d", &auxVet[i].id, &auxVet[i].tempo, &auxVet[i].prioridade, &auxVet[i].ciclos);
  }
  
  //criando fila
  FilaProcessos *fila = criarFila(auxVet, n); 
  
  //desalocando vetor auxiliar
  free(auxVet);
  
  //escalonando processos
  escalonador(fila);

  //printando resultado
  imprimeLog(fila);

  //destruindo fila criada
  fila = destroiFila(fila);
  
  return 0;
}