#ifndef CPU_H
#define CPU_H

#include "instrucao.h"
#include "ram.h"

typedef struct reg Reg;
typedef struct cpu CPU;


CPU *criarCPU();
void iniciar(CPU *cpu, RAM *ram);
void setPrograma(CPU *cpu, Instruction **programa, int tamanhoPrograma);
void destroiPrograma(CPU *cpu, int tamanhoPrograma);

#endif
