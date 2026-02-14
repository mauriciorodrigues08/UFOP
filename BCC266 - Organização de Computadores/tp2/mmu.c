#include "mmu.h"

#define ZERAR 0
#define INCREMENTAR 1

void swap(BlocoDeMemoria *b1, BlocoDeMemoria *b2) {
  BlocoDeMemoria temp = *b1;
  *b1 = *b2;
  *b2 = temp;
}

void busca_memoria(int endereco_bloco, Maquina *maquina, int *memoria, int *posicao) {
  // Atualiza LRU
  for(int i=0; i < maquina->cache1->numBlocos; i++) 
    atualiza_lru(maquina->cache1, i, INCREMENTAR);

  for(int i=0; i < maquina->cache2->numBlocos; i++) 
    atualiza_lru(maquina->cache2, i, INCREMENTAR);

  for(int i=0; i < maquina->cache3->numBlocos; i++) 
    atualiza_lru(maquina->cache3, i, INCREMENTAR);

  // Cache 1
  for(int i = 0; i < maquina->cache1->numBlocos; i++) {
    if (maquina->cache1->blocos[i].addBloco == endereco_bloco) {
      *memoria = 1; 
      *posicao = i;
      maquina->cache1->cacheHit++;
      maquina->custo += 10;
      maquina->ciclos += 1;
      atualiza_lru(maquina->cache1, i, ZERAR);
      return;
    }
  }
  
  // Cache 2
  maquina->cache1->cacheMiss++;
  for(int i = 0; i < maquina->cache2->numBlocos; i++) {
    if (maquina->cache2->blocos[i].addBloco == endereco_bloco) {
      cache2_to_cache1(maquina, i);
      *memoria = 1; 
      *posicao = verifica_mru(maquina->cache1);
      maquina->cache2->cacheHit++;
      maquina->custo += 110;
      maquina->ciclos += 10;
      return;
    }
  }
  
  // Cache 3
  maquina->cache2->cacheMiss++;
  for(int i = 0; i < maquina->cache3->numBlocos; i++) {
    if (maquina->cache3->blocos[i].addBloco == endereco_bloco) {
      cache3_to_cache1(maquina, i);
      *memoria = 1; 
      *posicao = verifica_mru(maquina->cache1);
      maquina->cache3->cacheHit++;
      maquina->custo += 1110;
      maquina->ciclos += 100;
      return;
    }
  }
  
  // RAM
  maquina->cache3->cacheMiss++;
  ram_to_cache1(maquina, endereco_bloco);
  *memoria = 1; 
  *posicao = verifica_mru(maquina->cache1);
  maquina->ram->ramHit++;
  maquina->custo += 11110;
  maquina->ciclos += 1000;
}

bool atualiza_lru(Cache *cache, int bloco, int chave) {
  if (chave == ZERAR) cache->blocos[bloco].lru = 0;
  else cache->blocos[bloco].lru++;
  return true;
}

int verifica_lru(Cache *cache) { 
  int posMaior = 0;
  for(int i = 0; i < cache->numBlocos; i++) {
    if(cache->blocos[i].addBloco == -1) 
      return i;
    if(cache->blocos[i].lru > cache->blocos[posMaior].lru) 
      posMaior = i;
  }
  return posMaior;
}

int verifica_mru(Cache *cache) { 
  int posMenor = 0;
  for(int i = 0; i < cache->numBlocos; i++) {
    if(cache->blocos[i].lru < cache->blocos[posMenor].lru && cache->blocos[i].addBloco != -1) 
      posMenor = i;
  }
  return posMenor;
}

bool cache2_to_cache1(Maquina *maquina, int blocoAlvo) {
  int lruCache1 = verifica_lru(maquina->cache1);
  swap(&(maquina->cache1->blocos[lruCache1]), &(maquina->cache2->blocos[blocoAlvo]));
  atualiza_lru(maquina->cache1, lruCache1, ZERAR);
  return true;
}

bool cache3_to_cache1(Maquina *maquina, int blocoAlvo) {
  int lruCache2 = verifica_lru(maquina->cache2);  
  swap(&(maquina->cache2->blocos[lruCache2]), &(maquina->cache3->blocos[blocoAlvo]));
  cache2_to_cache1(maquina, lruCache2); // Sobe o bloco para C1
  lruCache2 = verifica_lru(maquina->cache2);

  if(maquina->cache2->blocos[lruCache2].addBloco == -1){
    int p3 = verifica_mru(maquina->cache3);
    swap(&(maquina->cache2->blocos[lruCache2]), &(maquina->cache3->blocos[p3]));
  }

  return true;
}

bool ram_to_cache1(Maquina *maquina, int blocoAlvo) {
  int lruCache3 = verifica_lru(maquina->cache3);
  // Se o bloco que vai sair da C3 estiver atualizado, salva na RAM
  if(maquina->cache3->blocos[lruCache3].atualizado && maquina->cache3->blocos[lruCache3].addBloco != -1) {
    copiarBloco(&(maquina->cache3->blocos[lruCache3]), &(maquina->ram->blocos[maquina->cache3->blocos[lruCache3].addBloco]));
  }
  copiarBloco(&(maquina->ram->blocos[blocoAlvo]), &(maquina->cache3->blocos[lruCache3]));
  maquina->cache3->blocos[lruCache3].atualizado = false;
  cache3_to_cache1(maquina, lruCache3);
  return true;
}

bool esvaziarCache(Maquina *maquina){
  cache3_to_ram(maquina);
  cache2_to_ram(maquina);
  cache1_to_ram(maquina);

  return true;
}

bool cache3_to_ram(Maquina *maquina){
  int endereco;
  int tam = maquina->cache3->numBlocos;

  for(int i = 0; i < tam; i++){
    endereco = maquina->cache3->blocos[i].addBloco;
    if(endereco != -1 ){
      copiarBloco(&(maquina->cache3->blocos[i]), &(maquina->ram->blocos[endereco]));
      maquina->cache3->blocos[i].atualizado = false;
      maquina->cache3->blocos[i].addBloco = -1;
    }
  }

  return true;
}

bool cache2_to_ram(Maquina *maquina){
  int endereco, lruCache3;
  int tam = maquina->cache2->numBlocos;
  for(int i = 0; i < tam; i++){
    endereco = maquina->cache2->blocos[i].addBloco;
    lruCache3 = verifica_lru(maquina->cache3);
    if(endereco != -1 ){
      copiarBloco(&(maquina->cache2->blocos[i]), &(maquina->cache3->blocos[lruCache3]));
      maquina->cache3->blocos[i].atualizado = false;
      maquina->cache3->blocos[i].addBloco = -1;
    }
  }

  cache3_to_ram(maquina);

  return true;
}

bool cache1_to_ram(Maquina *maquina){
  int endereco, lruCache2;
  int tam = maquina->cache1->numBlocos;
  for(int i = 0; i < tam; i++){
    endereco = maquina->cache1->blocos[i].addBloco;
    lruCache2 = verifica_lru(maquina->cache2);
    if(endereco != -1 ){
      copiarBloco(&(maquina->cache1->blocos[i]), &(maquina->cache2->blocos[lruCache2]));
      maquina->cache3->blocos[i].atualizado = false;
      maquina->cache3->blocos[i].addBloco = -1;
    }
  }

  cache2_to_ram(maquina);

  return true;
}
