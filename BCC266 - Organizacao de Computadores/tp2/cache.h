#ifndef CACHE_H
#define CACHE_H

#include "bloco.h"

typedef struct Cache{
  BlocoDeMemoria *blocos;
  int blocosUsados;
  int numBlocos;

  long int cacheHit;
  long int cacheMiss;
  
}Cache;

Cache *criarCache(int numBlocos, int numPalavras);
Cache *destroiCache(Cache *cache, int n);


#endif