#include "maquina.h"
#include "mmu.h"
#include <stdbool.h>

void interpretaInstrucao(Maquina *maquina, Instrucao *inst);

bool recebe_instrucoes(Instrucao *inst, int qtd_inst) {
  FILE *arq = fopen("instrucoes.txt", "r");
  if (!arq) {
    printf("Arquivo não encontrado!\n");
    return false;
  }
  
  for (int i=0; i<qtd_inst; i++) {
    if (fscanf(arq, "%d %d %d %d %d %d %d", 
        &(inst[i].opcode), 
        &(inst[i].end1.addBloco), &(inst[i].end1.addPalavra), 
        &(inst[i].end2.addBloco), &(inst[i].end2.addPalavra), 
        &(inst[i].end3.addBloco), &(inst[i].end3.addPalavra)) == EOF) break;
  }

  fclose(arq);
  return true;
}

Maquina *criaMaquina(){
  Maquina *result = (Maquina*) malloc(sizeof(Maquina));
  result->ciclos = 0;
  result->custo = 0;
  result->PC = 0;
  
  result->ram = criarRam(TAM_RAM, NUM_PALAVRAS);
  result->cache1 = criarCache(TAM_CACHE_1, NUM_PALAVRAS);
  result->cache2 = criarCache(TAM_CACHE_2, NUM_PALAVRAS);
  result->cache3 = criarCache(TAM_CACHE_3, NUM_PALAVRAS);

  preencheRamAleatoria(result->ram, TAM_RAM, NUM_PALAVRAS);
  return result;
}

Maquina *destroiMaquina(Maquina *maquina){
  destroiRam(maquina->ram, TAM_RAM);
  destroiCache(maquina->cache1, TAM_CACHE_1);
  destroiCache(maquina->cache2, TAM_CACHE_2);
  destroiCache(maquina->cache3, TAM_CACHE_3);
  free(maquina);
  return NULL;
}

void iniciar(Maquina *maquina, Instrucao *inst){
  long int custoAtual;
  while(inst[maquina->PC].opcode != -1){
    custoAtual = maquina->custo;
    interpretaInstrucao(maquina, &(inst[maquina->PC]));
    
    printf("\nPC: %ld | Opcode: %d", maquina->PC, inst[maquina->PC].opcode);
    printf("\nCiclos estimados da maquina: %ld\n", maquina->ciclos);
    printf("Custo da operação: %ld\n", maquina->custo - custoAtual);
    printf("Custo total: %ld\n", maquina->custo);
    printf("Cache 1 -> Hit: %ld | Miss: %ld\nCache 2 -> Hit: %ld | Miss: %ld\nCache 3 -> Hit: %ld | Miss: %ld\nRAM -> Hit: %ld\n", 
           maquina->cache1->cacheHit, maquina->cache1->cacheMiss,
           maquina->cache2->cacheHit, maquina->cache2->cacheMiss,
           maquina->cache3->cacheHit, maquina->cache3->cacheMiss,
           maquina->ram->ramHit);

    maquina->PC++;
  }

  esvaziarCache(maquina);
}

void interpretaInstrucao(Maquina *maquina, Instrucao *inst){
  if (inst->opcode == 0) return;

  // Busca os operandos (isso traz os blocos para a Cache 1)
  set_registradores(maquina, inst);

  if (inst->opcode == 1) 
    maquina->reg1 += maquina->reg2;
  else if (inst->opcode == 2) 
    maquina->reg1 -= maquina->reg2;

  //escreve o resultado diretamente na cache 1 (garantido pela função set_registradores())
  int memoria, posicao;
  busca_memoria(inst->end3.addBloco, maquina, &memoria, &posicao);
  maquina->cache1->blocos[posicao].palavras[inst->end3.addPalavra] = maquina->reg1;
  maquina->cache1->blocos[posicao].atualizado = true;

  printf("\nValor: %d armazenado na cache1", maquina->reg1);
}

void set_registradores(Maquina *maquina, Instrucao *inst) {
  int memoria1, posicao1, memoria2, posicao2, memoria3, posicao3;

  busca_memoria(inst->end1.addBloco, maquina, &memoria1, &posicao1); 
  maquina->reg1 = maquina->cache1->blocos[posicao1].palavras[inst->end1.addPalavra];

  busca_memoria(inst->end2.addBloco, maquina, &memoria2, &posicao2);
  maquina->reg2 = maquina->cache1->blocos[posicao2].palavras[inst->end2.addPalavra];

  //coloca o endereco 3 (resultado) na cache 1, preparando para receber o resultado
  busca_memoria(inst->end3.addBloco, maquina, &memoria3, &posicao3);
}