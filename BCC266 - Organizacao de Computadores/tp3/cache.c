#include "cache.h"

Cache *criarCache(int numBlocos, int numPalavras){
  Cache *result = (Cache *) malloc(sizeof(Cache));

  result->blocos = (BlocoDeMemoria *) malloc(numBlocos * sizeof(BlocoDeMemoria));
  if(!result->blocos)
    return NULL;
  for(int i = 0; i < numBlocos; i++){
    criaBloco(&(result->blocos[i]), numPalavras, -1);
  }

  result->numBlocos = numBlocos;
  result->cacheHit = 0;
  result->cacheMiss = 0;
  result->blocosUsados = 0;

  return result;
}

Cache *destroiCache(Cache *cache, int n){
    for(int i = 0; i < n; i++){
    liberaBloco(&(cache->blocos[i]));
  }
  free(cache->blocos);
  free(cache);
  return NULL;
}


