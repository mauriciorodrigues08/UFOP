#include <stdbool.h>

#include "maquina.h"
#include "mmu.h"
#include "hd.h"

void interpretaInstrucao(Maquina *maquina, Instrucao *inst);

bool recebe_instrucoes(Instrucao *inst, int qtd_inst, const char* filename) {
  FILE *arq = fopen(filename, "r");
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
  result->interrupcao = false;

  result->cache1 = criarCache(TAM_CACHE_1, NUM_PALAVRAS);
  result->cache2 = criarCache(TAM_CACHE_2, NUM_PALAVRAS);
  result->cache3 = criarCache(TAM_CACHE_3, NUM_PALAVRAS);
  result->ram = criarRam(TAM_RAM, NUM_PALAVRAS);
  result->hd = criarHD(TAM_HD, NUM_PALAVRAS);

  return result;
}

Maquina *destroiMaquina(Maquina *maquina){
  destroiRam(maquina->ram, TAM_RAM);
  destroiCache(maquina->cache1, TAM_CACHE_1);
  destroiCache(maquina->cache2, TAM_CACHE_2);
  destroiCache(maquina->cache3, TAM_CACHE_3);
  destroiHD(maquina->hd);
  free(maquina);
  return NULL;
}

void iniciar(Maquina *maquina, Instrucao *inst, Instrucao *tratador_interrupcao, int prob_interrupcao){
  long int custoAtual;
  Instrucao* atual = inst;

  while(atual[maquina->PC].opcode != -1){
    custoAtual = maquina->custo;
    interpretaInstrucao(maquina, &(atual[maquina->PC]));

    maquina->PC++;

    // se a maquina nao estiver em interrupcao, sorteamos um numero, se ele for menor ou igual q a probabilidade iniciamos a interrupcao
    if (!maquina->interrupcao) {
      int sorteio = (rand() % 100) + 1;
      if (sorteio <= prob_interrupcao) {
        printf("\nINICIANDO INTERRUPÇÃO\n");

        printf("\nPC: %ld | Opcode: %d", maquina->PC, atual[maquina->PC].opcode);
        printf("\nCiclos estimados da maquina: %ld\n", maquina->ciclos);
        printf("Custo da operação: %ld\n", maquina->custo - custoAtual);
        printf("Custo total: %ld\n", maquina->custo);

        printf("Cache 1 -> Hit: %6ld | Miss: %6ld\n", maquina->cache1->cacheHit, maquina->cache1->cacheMiss);
        printf("Cache 2 -> Hit: %6ld | Miss: %6ld\n", maquina->cache2->cacheHit, maquina->cache2->cacheMiss);
        printf("Cache 3 -> Hit: %6ld | Miss: %6ld\n", maquina->cache3->cacheHit, maquina->cache3->cacheMiss);
        printf("Ram     -> Hit: %6ld | Miss: %6ld\n", maquina->ram->ramHit, maquina->ram->ramMiss);
        printf("HD      -> Hit: %6ld\n", maquina->hd->HDhit);


        maquina->pc_salvo = maquina->PC;
        maquina->reg1_salvo = maquina->reg1;
        maquina->reg2_salvo = maquina->reg2;
        maquina->interrupcao = true;

        atual = tratador_interrupcao;
        maquina->PC = 0;
      }
    }

    // se estivermos em uma interrupção e for a ultima instrucao
    if (maquina->interrupcao && atual[maquina->PC].opcode == -1) {
      maquina->PC = maquina->pc_salvo;
      maquina->reg1 = maquina->reg1_salvo;
      maquina->reg2 = maquina->reg2_salvo;
      maquina->interrupcao = false;

      atual = inst;
      continue;
    }

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

  //printf("\nValor: %d armazenado na cache1", maquina->reg1);
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