#include "ram.h"

RAM *criarRam(int numBlocos, int numPalavras){
  RAM *result = (RAM*) malloc(sizeof(RAM));

  result->blocos = (BlocoDeMemoria *) malloc(numBlocos * sizeof(BlocoDeMemoria));
  if(!result->blocos)
    return NULL;
  for(int i = 0; i < numBlocos; i++){
    criaBloco(&(result->blocos[i]), numPalavras, i);
  }

  result->numBlocos = numBlocos;
  result->ramHit = 0;
  result->custo = 0;

  return result;
}

RAM *destroiRam(RAM *ram, int n){
  for(int i = 0; i < n; i++){
    liberaBloco(&(ram->blocos[i]));
  }
  free(ram->blocos);
  free(ram);
  return NULL;
}

void preencheRamAleatoria(RAM *ram, int tamanhoRam, int numPalavras){
    for(int i = 0; i < tamanhoRam; i++){
        ram->blocos[i].addBloco = i; //Add endereço
        for(int j = 0; j < numPalavras; j++) 
            ram->blocos[i].palavras[j] = rand() % 1000000; //Add palavras
    }
}
