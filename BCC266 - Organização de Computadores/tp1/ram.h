#ifndef RAM_H
#define RAM_H

typedef struct instruction Instruction;
typedef struct ram RAM;

RAM* criarRAM(int tamanho);
RAM* criarRAM_vazia(int tamanho);
RAM* criarRAM_aleatoria(int tamanho);
RAM *aumentarRam(RAM *ram, int novoTamanho);
RAM* liberarRAM(RAM *ram);
void setDado(int endereco, int conteudo, RAM *ram);
int getDado(int endereco, RAM *ram);
int getTamanho(RAM *ram);
void imprimir(RAM *ram);
RAM *zerarRAM(RAM *ram, int pontoDeInicio, int final);

#endif
