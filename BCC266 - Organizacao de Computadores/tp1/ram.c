#include <stdio.h>
#include <stdlib.h>

#include "ram.h"

struct ram {
	int tamanho;
	int *memoria;
};

RAM* criarRAM(int tamanho) {
	RAM *ram = (RAM*) malloc(sizeof(RAM));
	ram->memoria = malloc(tamanho * sizeof(int));
	if (!ram->memoria) {
		printf("Erro de alocação.\n");
		return NULL;
	}
			
	ram->tamanho = tamanho;
	return ram;
}

RAM* criarRAM_vazia(int tamanho) {
	RAM *ram = criarRAM(tamanho);
	ram = zerarRAM(ram, 0, tamanho-1);

	return ram;
}

RAM* criarRAM_aleatoria(int tamanho) {
	
	RAM *ram = criarRAM(tamanho);
	for (int i = 0; i < tamanho; i++) 
		ram->memoria[i] = rand() % RAND_MAX;

	return ram;
}

RAM* liberarRAM(RAM *ram) {
	free(ram->memoria);
	ram->memoria = NULL;
	ram->tamanho = 0;
	free(ram);
	return NULL;
}

void setDado(int endereco, int conteudo, RAM *ram) {
	ram->memoria[endereco] = conteudo;
}

int getDado(int endereco, RAM *ram) {
	return ram->memoria[endereco];	
}

int getTamanho(RAM *ram){
	return ram->tamanho;
}

void imprimir(RAM *ram) {
	printf("Conteúdo da RAM: \n");
	for (int i = 0; i < ram->tamanho; i++)
		printf("%d ", ram->memoria[i]);
	
	printf("\n");
}

RAM *aumentarRam(RAM *ram, int novoTamanho){
	int *tempMemoria = (int*) realloc(ram->memoria, novoTamanho * sizeof(int));

	if(tempMemoria == NULL){
		printf("\nErro ao realocar ram\n");
	}
	else{ 
		ram->memoria = tempMemoria;
		for(int i = ram->tamanho; i < novoTamanho; i++){
			ram->memoria[i] = 0;
		}
		ram->tamanho = novoTamanho;
	}

	return ram;
}

RAM *zerarRAM(RAM *ram, int pontoDeInicio, int final){
	if(final >= ram->tamanho || pontoDeInicio < 0){
		printf("\nImpossível acessar ram no trecho dado\n");
		return ram;
	}
	for(int i = pontoDeInicio; i <= final; i++){
		setDado(i, 0, ram);
	}
	return ram;
}