#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include<stdbool.h>

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(CPU *cpu, RAM *ram, int posInicial, int a, int b);
int programaDiv(CPU *cpu, RAM *ram, int posInicial, int dividendo, int divisor);
int programaModulo(CPU* cpu, RAM *ram, int posInicial, int a, int b);
int programaRaizAproximada(CPU *cpu, RAM *ram, int posInicial, int valor);
int programaRaizCubicaAroximada(CPU *cpu, RAM *ram, int posInicial, int valor);
int programaFatorial(CPU *cpu, RAM *ram, int posInicial, int valor);
int programaExponencial(CPU *cpu, RAM *ram, int posInicial, int base, int expoente);
int programaLog(CPU *cpu, RAM *ram, int posInicial, int base, int logaritmando);
int programaMdc(CPU *cpu, RAM *ram, int posInicial, int a, int b);
int programaMmc(CPU *cpu, RAM *ram, int posInicial, int a, int b);
int programaBhaskara(CPU *cpu, RAM *ram, int posInicial, int a, int b, int c, int res);
int programaDistAproxEntrePontos(CPU *cpu, RAM *ram, int posInicial, int xa, int ya, int xb, int yb);
bool programaEhNumeroPrimo(CPU *cpu, RAM *ram, int posInicial, int valor);
bool programaEhPar(CPU *cpu, RAM *ram, int posInicial, int a);

// Funções matriciais
RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int posInicial, int pontoDePartida,int n, int m);
RAM *programaMultiplicaMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int posInicialMatriz, int n1, int m1, int n2, int m2);
void imprimirMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int pontoDePartida, int n, int m);
RAM *criaMatriz(int n, int m, RAM *ram);
int programaDeterminante2x2(CPU* cpu, RAM* ram, int posInicialRAM, int posInicialMatriz);
int programaDeterminante3x3(CPU *cpu, RAM *ram, int posInicialRAM, int posInicialMatriz);
int programaMatrizTransposta(CPU *cpu, RAM *ram, int posInicialRAM, int posInicialMatrizA, int posInicialMatrizT, int n, int m);

RAM *programaFibonacci(CPU *cpu, RAM *ram, int posInicial, int n);
int programaTermoPA(CPU *cpu, RAM *ram, int posInicial, int a1, int n, int r);
int programaSomaTermosPA(CPU* cpu, RAM *ram, int posInicial, int a1, int n, int r);

#endif