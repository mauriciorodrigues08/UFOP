#include <stdlib.h>

#include "instrucao.h"

struct instruction {
	int add1;
	int add2;
	int add3;
	int opcode;
};

Instruction *setInstruction(int auxAdd1, int auxAdd2, int auxAdd3, int auxOpcode){
	Instruction *tempInstruction = (Instruction*) malloc(sizeof(Instruction));
	tempInstruction->add1 = auxAdd1;
	tempInstruction->add2 = auxAdd2;
	tempInstruction->add3 = auxAdd3;
	tempInstruction->opcode = auxOpcode;
	return tempInstruction;
}

Instruction *destroiInstruction(Instruction *inst){
	free(inst);
	return NULL;
}

Instruction **destroiTrecho(Instruction **trecho, int tamanho){
	free(trecho);
	return NULL;
}


int getOpcode(Instruction *instruction){
	return instruction->opcode;
}

int getAdd1(Instruction *instruction){
	return instruction->add1;
}

int getAdd2(Instruction *instruction){
	return instruction->add2;
}

int getAdd3(Instruction *instruction){
	return instruction->add3;
}
