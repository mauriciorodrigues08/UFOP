#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct instruction Instruction;

Instruction *setInstruction(int add1, int add2, int add3, int opcode);
Instruction *destroiInstruction(Instruction *inst);
Instruction **setTrecho(int tamanho);
Instruction **destroiTrecho(Instruction **trecho, int tamanho);
int getOpcode(Instruction *instruction);
int getAdd1(Instruction *instruction);
int getAdd2(Instruction *instruction);
int getAdd3(Instruction *instruction);

#endif
