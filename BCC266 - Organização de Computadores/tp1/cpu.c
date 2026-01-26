#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "instrucao.h"
#include "ram.h"

struct cpu {
	int reg1;
	int reg2;
	int PC;
	Instruction **programa;
};

CPU *criarCPU(){
	CPU *result;
	result = (CPU *) malloc(sizeof(CPU));
	if(result != NULL){
		result->PC = 0;
		result->programa = NULL;
		result->reg1 = 0;
		result->reg2 = 0;
	}
	else
		printf("\nErro ao criar CPU\n");
	
	return result;
}


void setPrograma(CPU *cpu, Instruction **programa, int tamanhoPrograma){
	cpu->programa = (Instruction**) malloc(tamanhoPrograma * sizeof(Instruction*));
	for(int i = 0; i < tamanhoPrograma; i++){
		cpu->programa[i] = programa[i];
	}
}

void iniciar(CPU *cpu, RAM *ram){
	cpu->PC = 0;
	int tempOpcode = 0;
	Instruction *tempInst;

	while(tempOpcode != -1){
		
		tempInst = cpu->programa[cpu->PC];
		tempOpcode = getOpcode(tempInst);

		switch (tempOpcode){
		case -1:
			break;
		case 0:
			cpu->reg1 = getDado(getAdd1(tempInst), ram);
			cpu->reg2 = getDado(getAdd2(tempInst), ram);

			cpu->reg1 += cpu->reg2;
			setDado(getAdd3(tempInst), cpu->reg1, ram);

			break;
		case 1:
			cpu->reg1 = getDado(getAdd1(tempInst), ram);
			cpu->reg2 = getDado(getAdd2(tempInst), ram);

			cpu->reg1 -= cpu->reg2;
			setDado(getAdd3(tempInst), cpu->reg1, ram);

			break;
		case 2:
			if(getAdd1(tempInst) == 1){
				setDado(getAdd2(tempInst), cpu->reg1, ram);
			}
			else if(getAdd1(tempInst) == 2){
				setDado(getAdd2(tempInst), cpu->reg2, ram);
			}
			break;
		case 3:
			if(getAdd1(tempInst) == 1){
				cpu->reg1 = getDado(getAdd2(tempInst), ram);
			}
			else if(getAdd1(tempInst) == 2){
				cpu->reg2 = getDado(getAdd2(tempInst), ram);
			}
			break;
		case 4:
			if(getAdd1(tempInst) == 1){
				cpu->reg1 = getAdd2(tempInst);
			}
			else if(getAdd1(tempInst) == 2){
				cpu->reg2 = getAdd2(tempInst);
			}
			break;
		case 5:
			if(getAdd1(tempInst) == 1){
				setDado(getAdd2(tempInst), cpu->reg1, ram);
			}
			else if(getAdd1(tempInst) == 2){
				setDado(getAdd2(tempInst), cpu->reg2, ram);
			}
			break;

		default:
			printf("\nOpcode nao encontrado\n");
			break;
		}

		cpu->PC++;

	}

}

void destroiPrograma(CPU *cpu, int tamanhoPrograma){
	for(int i = 0; i < tamanhoPrograma; i++){
		cpu->programa[i] = destroiInstruction(cpu->programa[i]);
	}
	
	free(cpu->programa);
}