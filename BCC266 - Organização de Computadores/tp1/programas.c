#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "programas.h"

int encontrarPosicaoMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int posInicial, int nLinhas, int mColunas, int i, int j);


int programaMulti(CPU *cpu, RAM *ram, int posInicial, int a, int b){
  int result;

  Instruction **trecho1;
  trecho1 = (Instruction**) malloc(3 * sizeof(Instruction*));

  bool eraNeg1 = false;
  bool eraNeg2 = false;
  if (a < 0) {
    a = -a;
    eraNeg1 = true;
  }

  if (b < 0) {
    b = -b;
    eraNeg2 = true;
  } 

  trecho1[0] = setInstruction(1, a, -1, 4); //reg1 <- a
  trecho1[1] = setInstruction(1, posInicial + 1, -1, 2); //ram[posInicial + 1] <- reg1
  trecho1[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho1 = destroiTrecho(trecho1, 3);

  Instruction **trecho2;
  trecho2 = (Instruction**) malloc(2 * sizeof(Instruction*));
  for(int i = 0; i < b; i++){ //ram[0] += ram[1](a); (b) vezes
    trecho2[0] = setInstruction(posInicial, posInicial + 1, posInicial, 0); //reg1 <- ram[0]; reg2 <- ram[1]; reg1 += reg2; ram[0] <- reg1
    trecho2[1] = setInstruction(-1, -1, -1, -1); //halt

    setPrograma(cpu, trecho2, 2);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 2);
  }

  trecho2 = destroiTrecho(trecho2, 2);

  result = getDado(posInicial, ram);
  ram = zerarRAM(ram, posInicial, posInicial + 1);

  if (eraNeg1 && eraNeg2) {
    return result;
  }
  else if (!eraNeg1 && !eraNeg2) {
    return result;
  }
  else {
    return -result;
  }
}

int programaDiv(CPU *cpu, RAM *ram, int posInicial, int dividendo, int divisor){
  
  bool eraNeg1 = false;
  bool eraNeg2 = false;

  if (divisor < 0) {
    divisor = -divisor;
    eraNeg1 = true;
  }

  if (dividendo < 0) {
    dividendo = -dividendo;
    eraNeg2 = true;
  }

  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));
  trecho1[0] = setInstruction(1, dividendo, -1, 4); //reg1 <- dividendo
  trecho1[1] = setInstruction(1, posInicial, -1, 2); //ram[0] <- reg1
  trecho1[2] = setInstruction(2, divisor, -1, 4); //reg 2 <- divisor
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 2); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction*));
  trecho2[0] = setInstruction(1, 1, -1, 4); //reg1 <- 1
  trecho2[1] = setInstruction(1, posInicial + 2, -1, 2); //ram[2] <- reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  trecho2 = destroiTrecho(trecho2, 3);

  Instruction **trecho3 = (Instruction **) malloc(5 * sizeof(Instruction*));
  Instruction **trecho4 = (Instruction **) malloc(5 * sizeof(Instruction*));
 
  while(dividendo >= divisor){

    trecho3[0] = setInstruction(posInicial, posInicial + 1, posInicial, 1); //reg1 <- ram[0]; reg2 <- ram[1]; reg1 -= reg2; ram[0] <- reg1;
    trecho3[1] = setInstruction(posInicial + 2, posInicial + 3, posInicial + 3, 0); //reg1 <- ram[2]; reg2 <- ram[3]; reg1 += reg2; ram[3] <- reg1;
    trecho3[2] = setInstruction(1, posInicial, -1, 3); //reg1 <- ram[0];
    trecho3[3] = setInstruction(1, posInicial + 4, -1, 5); //ram[4] <- reg1;
    trecho3[4] = setInstruction(-1, -1, -1, -1); //halt

    setPrograma(cpu, trecho3, 5);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 5);

    dividendo = getDado(posInicial + 4, ram);

  }

  trecho3 = destroiTrecho(trecho3, 5);
  trecho4 = destroiTrecho(trecho4, 5);

  Instruction **trecho5 = (Instruction **) malloc(3 * sizeof(Instruction*));
  trecho5[0] = setInstruction(1, posInicial + 3, -1, 3); //reg1 <- ram[3]
  trecho5[1] = setInstruction(1, posInicial + 4, -1, 5); //ram[4] <- reg1
  trecho5[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho5, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  int result = getDado(posInicial + 4, ram);

  trecho5 = destroiTrecho(trecho5, 3);

  ram = zerarRAM(ram, posInicial, posInicial + 4);

  if (eraNeg1 && eraNeg2) {
    return result;
  }
  else if (!eraNeg1 && !eraNeg2) {
    return result;
  }
  else {
    return -result;
  }
}

int programaRaizAproximada(CPU *cpu, RAM *ram, int posInicial, int valor) {
  //cria um vetor de instruções
  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));
  
  // multiplica i^2 até o resultado ser maior ou igual que o valor digitado
  int i = 1;
  while (getDado(posInicial, ram) <= valor/2) {
    
    trecho[0] = setInstruction(1, programaMulti(cpu, ram, posInicial + 1, i, i), -1, 4); // envia i*i para o registrador 1
    trecho[1] = setInstruction(1, posInicial, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado

    i++;
  }

  // libera memória alocada
  trecho = destroiTrecho(trecho, 3);
  ram = zerarRAM(ram, posInicial, posInicial);

  return i-2;
}

int encontrarPosicaoMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int posInicial, int nLinhas, int mColunas, int i, int j){
  int endereco;
  //endereco = (posInicial + programaMulti(cpu, ram, posInicialRAM + 1, i, mColunas) + j);
  endereco = posInicial + (i * mColunas) + j;
  return endereco;
}

RAM *criaMatriz(int n, int m, RAM *ram){
  ram = criarRAM_vazia(n * m);
  return ram;
}

RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int posInicial, int pontoDePartida, int n, int m){
  int temp, endereco;

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      endereco = encontrarPosicaoMatriz(cpu, ram, posInicial, pontoDePartida, n, m, i, j);
      printf("Insira o valor da matriz[%d][%d]: ", i, j);
      scanf("%d", &temp);

      trecho[0] = setInstruction(1, temp, -1, 4); //reg1 <- temp
      trecho[1] = setInstruction(1, endereco, -1, 5); //ram[endereco] <- reg1
      trecho[2] = setInstruction(-1, -1, -1, -1);

      setPrograma(cpu, trecho, 3);
      iniciar(cpu, ram);
      destroiPrograma(cpu, 3);
    }
  }

  printf("\nMatriz digitada:\n");
  imprimirMatriz(cpu, ram, posInicial, pontoDePartida, n, m);

  trecho = destroiTrecho(trecho, 3);

  return ram;
}

RAM *programaMultiplicaMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int posInicialMatriz, int n1, int m1, int n2, int m2){
  int addResult, addM1, addM2, tempMult, tamanhoM1, tamanhoM2, tamanhoM3;

  if (m2 != n1) {
    printf("Erro: número de colunas de A deve ser igual ao número de linhas de B.\n");
    return ram;
  }

  tamanhoM1 = programaMulti(cpu, ram, posInicialRAM + 3, n1, m1);
  tamanhoM2 = programaMulti(cpu, ram, posInicialRAM + 3, n2, m2);
  tamanhoM3 = programaMulti(cpu, ram, posInicialRAM + 3, n1, m2);

  int baseTemp = posInicialMatriz + tamanhoM1 + tamanhoM2 + tamanhoM3 + 10; //area livre na ram para calculos temporarios


  //ram = aumentarRam(ram, getTamanho(ram) + programaMulti(cpu, n1, m2));

  //RAM *tempSoma = criarRAM_vazia(2);
  Instruction **trecho1 = (Instruction **) malloc(6 * sizeof(Instruction *));
  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));

  for(int i = 0; i < n1; i++){
    for(int j = 0; j < m2; j++){
      addResult = encontrarPosicaoMatriz(cpu, ram, baseTemp, (tamanhoM1 + tamanhoM2), n1, m2, i, j);
      setDado(addResult, 0, ram);
      for(int k = 0; k < m1; k++){

        addM1 = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatriz, n1, m1, i, k);
        addM2 = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatriz + tamanhoM1, n2, m2, k, j);

        tempMult = programaMulti(cpu, ram, baseTemp, getDado(addM1, ram), getDado(addM2, ram));

        trecho1[0] = setInstruction(1, tempMult, -1, 4); //reg1 <- tempMult
        trecho1[1] = setInstruction(1, posInicialRAM, -1, 5); //tempSoma[0] <- reg1
        trecho1[2] = setInstruction(2, getDado(addResult, ram), -1, 4); //reg2 <- ram[addResult]
        trecho1[3] = setInstruction(2, posInicialRAM + 1, -1, 5); //tempSoma[1] <- reg2
        trecho1[4] = setInstruction(posInicialRAM, posInicialRAM + 1, posInicialRAM, 0); //tempSoma[0] <- tempSoma[0] + tempSoma[1]
        trecho1[5] = setInstruction(-1, -1, -1, -1);

        setPrograma(cpu, trecho1, 6);
        iniciar(cpu, ram);
        destroiPrograma(cpu, 6);

        trecho2[0] = setInstruction(1, posInicialRAM, -1, 3); //reg1 <- tempSoma[0]
        trecho2[1] = setInstruction(1, addResult, -1, 5); //ram[addResult] <- reg1
        trecho2[2] = setInstruction(-1, -1, -1, -1);

        setPrograma(cpu, trecho2, 3);
        iniciar(cpu, ram);
        destroiPrograma(cpu, 3);


      }
    }
  }

  trecho1 = destroiTrecho(trecho1, 6);
  trecho2 = destroiTrecho(trecho2, 3);

  
  imprimirMatriz(cpu, ram, posInicialRAM, (tamanhoM1 + tamanhoM2), n1, m2);
  ram = zerarRAM(ram, posInicialRAM, posInicialRAM + 3);

  return ram;
}

void imprimirMatriz(CPU *cpu, RAM *ram, int posInicialRAM, int pontoDePartida, int n, int m){
  int endereco;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      endereco = encontrarPosicaoMatriz(cpu, ram, posInicialRAM, pontoDePartida, n, m, i, j);
      ram = zerarRAM(ram, posInicialRAM, posInicialRAM + 1);
      printf("%d ", getDado(endereco, ram));
    }
    printf("\n");
  }
}


int programaFatorial(CPU *cpu, RAM *ram, int posInicial, int valor) {
  //RAM *ram = criarRAM_vazia(2);

  //cria um vetor de instruções
  Instruction **trecho1 = (Instruction **) malloc(3 * sizeof(Instruction *));

    trecho1[0] = setInstruction(1, valor, -1, 4); // envia res para o registrador 1
    trecho1[1] = setInstruction(1, posInicial, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho1[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho1, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado 

    trecho1 = destroiTrecho(trecho1, 3);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));
  int aux;
  for (int i = valor-1; i > 1; i--) {
    aux = programaMulti(cpu, ram,  posInicial + 2, getDado(posInicial, ram), i);

    trecho2[0] = setInstruction(1, aux, -1, 4);
    trecho2[1] = setInstruction(1, posInicial, -1, 5);
    trecho2[2] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado 
   
  }

  int result = getDado(posInicial, ram);

  // free nas memórias alocadas
  ram = zerarRAM(ram, posInicial, posInicial + 2);
  trecho2 = destroiTrecho(trecho2, 3);

  return result;
}

int programaBhaskara(CPU *cpu, RAM *ram, int posInicial, int a, int b, int c, int res) {
  ram = zerarRAM(ram, res, res + 1);

  // cria vetor de instruções
  Instruction **trecho = (Instruction **) malloc(5 * sizeof(Instruction *));
  
  // calculo de delta
  int delta = programaMulti(cpu, ram, posInicial + 2, b, b) - programaMulti(cpu, ram, posInicial + 2, 4, programaMulti(cpu, ram, posInicial + 2, a, c));

  if (delta<0) {
    return 0;
  }
  else {
    // calculo de x1 => x1 = (-b + sqrt(delta)) / 2a
    int x1 = programaDiv(cpu, ram, posInicial + 2, (-b + programaRaizAproximada(cpu, ram, posInicial + 2, delta) ), programaMulti(cpu, ram, posInicial + 2, 2, a)); 
    
    trecho[0] = setInstruction(1, x1, -1, 4); //envia x1 para o registrador 1
    trecho[1] = setInstruction(1, posInicial, -1, 5); //passa x1 para a ram[posInicial]
    trecho[2] = setInstruction(-1, -1, -1, -1); //halt
    
    //executando programa na cpu
    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);
    
    // calculo de x2 => x2 = (-b - sqrt(delta)) / 2a
    int x2 = programaDiv(cpu, ram, posInicial + 2, (-b - programaRaizAproximada(cpu, ram, posInicial + 2, delta) ), programaMulti(cpu, ram, posInicial + 2, 2, a)); 
    
    trecho[0] = setInstruction(1, x2, -1, 4); //envia x2 para o registrador 1
    trecho[1] = setInstruction(1, posInicial + 1, -1, 5); //passa x2 para a ram[posInicial + 1]
    trecho[2] = setInstruction(-1, -1, -1, -1); //halt

    // executando programa na cpu
    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    //zera a ram
    ram = zerarRAM(ram, posInicial, posInicial + 2);
    
    // atualiza resultados  
    trecho[0] = setInstruction(1, x1, -1, 4);
    trecho[1] = setInstruction(2, x2, -1, 4);
    trecho[2] = setInstruction(1, res, -1, 5);
    trecho[3] = setInstruction(2, res + 1, -1, 5);
    trecho[4] = setInstruction(-1, -1, -1, -1);
    
    setPrograma(cpu, trecho, 5); // aqui realmente usamos 5 instruções válidas
    iniciar(cpu, ram);
    destroiPrograma(cpu, 5);  

    // libera memorias alocadas
    trecho = destroiTrecho(trecho, 5);
    
    return 1;
  }
}


int programaExponencial(CPU *cpu, RAM *ram, int posInicial, int base, int expoente){
  int resultado, tempMult;

  //RAM *ram = criarRAM_vazia(2);
  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));
  trecho1[0] = setInstruction(1, 1, -1, 4); //reg1 <- 1
  trecho1[1] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
  trecho1[2] = setInstruction(2, base, -1, 4); //reg2 <- base
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);


  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction*));
  for(int i = 0; i < expoente; i++){
    tempMult = programaMulti(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram));
    
    trecho2[0] = setInstruction(1, tempMult, -1, 4); //reg1 <- tempMult
    trecho2[1] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
    trecho2[2] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

  }

  trecho2 = destroiTrecho(trecho2, 3);

  resultado = getDado(posInicial, ram);

  ram = zerarRAM(ram, posInicial, posInicial + 3);
 
  return resultado;
  
}

int programaLog(CPU *cpu, RAM *ram, int posInicial, int base, int logaritmando){
  //RAM *ram = criarRAM_vazia(1);

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));

  int aux = 0;
  int i = 0;

  while(aux <= logaritmando){
    aux = programaExponencial(cpu, ram, posInicial + 1, base, i);

    trecho[0] = setInstruction(1, aux, -1, 4); // envia aux para o registrador 1
    trecho[1] = setInstruction(1, posInicial, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    i++;

  }

  trecho = destroiTrecho(trecho, 3);
  ram = zerarRAM(ram, posInicial, posInicial + 1);

  return i-2;
}

int programaRaizCubicaAroximada(CPU *cpu, RAM *ram, int posInicial, int valor) {
  //RAM *ram = criarRAM_vazia(1);

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));
  int aux = 0;
  int i = 1;

  while (aux <= valor) {

    aux = programaExponencial(cpu, ram, posInicial + 1, i, 3);


    trecho[0] = setInstruction(1, aux, -1, 4); // reg1 recebe aux; reg1 = aux
    trecho[1] = setInstruction(1, posInicial, -1, 5); // ram[0] recebe o valor do reg1
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    i++;
  }

  trecho = destroiTrecho(trecho, 3);
  ram = zerarRAM(ram, posInicial, posInicial + 1);

  return i - 2;
}

// formula pa: an = a1 + (n - 1) * r 
int programaTermoPA(CPU *cpu, RAM *ram, int posInicial, int a1, int n, int r) { // calcula o n-esimo termo
  //RAM *ram = criarRAM_vazia(4);
  Instruction **trecho = (Instruction **)malloc(6 * sizeof(Instruction *));

  trecho[0] = setInstruction(1, n, -1, 4); // reg1 <- n
  trecho[1] = setInstruction(1, posInicial, -1, 5); // ram[0] <- reg1
  trecho[2] = setInstruction(2, 1, -1, 4); // reg2 <- 1;
  trecho[3] = setInstruction(2, posInicial + 1, -1, 5); // ram[1] recebe reg2
  trecho[4] = setInstruction(posInicial, posInicial + 1, posInicial, 1);  // salva o resultado de n - 1 na ram[0];
  trecho[5] = setInstruction(-1, -1, -1, -1); // halt

  setPrograma(cpu, trecho, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);

  trecho = destroiTrecho(trecho, 6);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, r, -1, 4); // reg1 <- r
  trecho2[1] = setInstruction(1, posInicial + 1, -1, 5); // ram[1] recebe reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho2 = destroiTrecho(trecho2, 3);

  int aux = programaMulti(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram));

  Instruction **trecho3 = (Instruction **)malloc(6 * sizeof(Instruction *));
  trecho3[0] = setInstruction(1, a1, -1, 4); // reg1 <- a1
  trecho3[1] = setInstruction(1, posInicial, -1, 5);  // ram[0] recebe reg1;
  trecho3[2] = setInstruction(2, aux, -1, 4); // reg2 recebe aux;
  trecho3[3] = setInstruction(2, posInicial + 1, -1, 5);   // ram[1] recebe reg2;
  trecho3[4] = setInstruction(posInicial, posInicial + 1, posInicial + 2, 0); // ram[2] <- ram[0] + ram[1]
  trecho3[5] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho3, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);
  trecho3 = destroiTrecho(trecho3, 6);

  int result = getDado(posInicial + 2, ram);

  ram = zerarRAM(ram, posInicial, posInicial + 3);
  return result;
}

RAM *programaFibonacci(CPU *cpu, RAM *ram, int posInicial, int n){
  if (n < 1) {
    printf("\nValor inválido!\n");

    return ram;
  }


  if(n == 1) {
    Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));
    trecho[0] = setInstruction(1, 0, -1, 4); // reg1 <- 0
    trecho[1] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
    trecho[2] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    trecho = destroiTrecho(trecho, 3);

    return ram;
  }

  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));

  trecho1[0] = setInstruction(1, 0, -1, 4); //reg1 <- 0
  trecho1[1] = setInstruction(2, 1, -1, 4); //reg2 <- 1
  trecho1[2] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5); 

  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(2 * sizeof(Instruction*));

  for (int i = posInicial + 2; i < posInicial + n; i++) {
    trecho2[0] = setInstruction(i-1, i-2, i, 0); //ram[i] <- ram[i-1] + ram[i-2]
    trecho2[1] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 2); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 2); // free no programa criado 
  }

  trecho2 = destroiTrecho(trecho2, 2);

  return ram;

}

int programaSomaTermosPA(CPU* cpu, RAM *ram, int posInicial, int a1, int n, int r) {
  //RAM *ram = criarRAM_vazia(3);
  int an = programaTermoPA(cpu, ram, posInicial + 3, a1, n, r);

  Instruction **trecho1 = (Instruction **) malloc(6 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, an, -1, 4); // reg1 <- an
  trecho1[1] = setInstruction(1, posInicial, -1, 5); // ram[0] <- reg1
  trecho1[2] = setInstruction(2, a1, -1, 4); // reg2 <- a1
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); // ram[1] <- reg2
  trecho1[4] = setInstruction(posInicial, posInicial + 1, posInicial, 0); // soma de an + a1 salva na ram[0]
  trecho1[5] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);

  trecho1 = destroiTrecho(trecho1, 6);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, n, -1, 4); // reg1 <- n
  trecho2[1] = setInstruction(1, posInicial + 1, -1, 5); // ram[1] <- reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho2 = destroiTrecho(trecho2, 3);

  int temp = programaMulti(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram)); // (a1 + an) x n

  Instruction **trecho3 = (Instruction **)malloc(5 * sizeof(Instruction *));
  trecho3[0] = setInstruction(1, temp, -1, 4); // reg1 <- temp
  trecho3[1] = setInstruction(1, posInicial, -1, 5); // ram[0] <- reg1
  trecho3[2] = setInstruction(2, 2, -1, 4); // reg2 <- 2
  trecho3[3] = setInstruction(2, posInicial + 1, -1, 5); // ram[1] <- reg2
  trecho3[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho3, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho3 = destroiTrecho(trecho3, 5);

  int result = programaDiv(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram));
  ram = zerarRAM(ram, posInicial, posInicial + 3);

  return result;
}

// A - (B x A/B)
int programaModulo(CPU* cpu, RAM *ram, int posInicial, int a, int b) {
  //RAM *ram = criarRAM_vazia(3);

  Instruction **trecho1 = (Instruction **)malloc(5 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, a, -1, 4); //reg1 <- a
  trecho1[1] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
  trecho1[2] = setInstruction(2, b, -1, 4); //reg2 <- b
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho1 = destroiTrecho(trecho1, 5);

  int div = programaDiv(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram)); // divisão entre a e b

  int mult = programaMulti(cpu, ram, posInicial + 3, div, getDado(posInicial + 1, ram));

  Instruction **trecho2 = (Instruction **)malloc(6 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, mult, -1, 4); //reg1 <- mult
  trecho2[1] = setInstruction(1, posInicial + 2, -1, 5); //ram[2] <- reg1
  trecho2[2] = setInstruction(posInicial, posInicial + 2, posInicial, 1); //ram[0] <- ram[0] - ram[2]
  trecho2[3] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho2, 4);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 4);

  int result = getDado(posInicial, ram);

  trecho2 = destroiTrecho(trecho2, 4);
  ram = zerarRAM(ram, posInicial, posInicial + 3);

  return result;
}

bool programaEhNumeroPrimo(CPU *cpu, RAM *ram, int posInicial, int valor) {
  if (valor <= 1)
    return false;

  if (valor == 2 || valor == 3)
    return true;

  int raiz = programaRaizAproximada(cpu, ram, posInicial, valor);

  for (int i = 2; i <= raiz; i++) {
    if (programaModulo(cpu, ram, posInicial + 2, valor, i) == 0)
      return false;
  }

  ram = zerarRAM(ram, posInicial, posInicial + 2);

  return true;
}

int programaMdc(CPU *cpu, RAM *ram, int posInicial, int a, int b){
  //RAM *ram = criarRAM_vazia(3);
  
  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, a, -1, 4); //reg1 <- a
  trecho1[1] = setInstruction(2, b, -1, 4); //reg2 <- b
  trecho1[2] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1 (a)
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2 (b)
  trecho1[4] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);
  
  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(7 * sizeof(Instruction *));
  int resto;
  
  while(getDado(posInicial + 1, ram) != 0){
  //(r)                            // (a)               //(b)
    resto = programaModulo(cpu, ram, posInicial + 3, getDado(posInicial, ram), getDado(posInicial + 1, ram));
    
    trecho2[0] = setInstruction(1, posInicial, -1, 3); //reg1 <- ram[0](a)
    trecho2[1] = setInstruction(1, posInicial + 2, -1, 5); //ram[2] <- reg1
    trecho2[2] = setInstruction(1, posInicial + 1, -1, 3); //reg1 <- ram[1](b)
    trecho2[3] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1(b)
    trecho2[4] = setInstruction(2, resto, -1, 4); //reg2 <- (r)
    trecho2[5] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2(r)
    trecho2[6] = setInstruction(-1, -1, -1, -1); //halt

    setPrograma(cpu, trecho2, 7);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 7);

  }

  trecho2 = destroiTrecho(trecho2, 7);

  int result = getDado(posInicial, ram);

  ram = zerarRAM(ram, posInicial, posInicial + 3);

  return result;
  
}

bool programaEhPar(CPU *cpu, RAM *ram, int posInicial, int a) {
  // calcula módulo da divisão de a por 2
  int res = programaModulo(cpu, ram, posInicial, a, 2);

  // se não tem modulo -> é par (true)
  if (!res) return true;
  // se tem módulo -> é ímpar (false)
  else return false;
}

int programaMmc(CPU *cpu, RAM *ram, int posInicial, int a, int b) {
  // calcular o MMC usando a fórmula: MMC(a, b) = (a * b) / MDC(a, b)
  return programaDiv(cpu, ram, posInicial, programaMulti(cpu, ram, posInicial, a, b), programaMdc(cpu, ram, posInicial, a, b));
}

int programaDistAproxEntrePontos(CPU *cpu, RAM *ram, int posInicial, int xa, int ya, int xb, int yb) {
  //instruções para o ponto A
  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, xa, -1, 4); //reg1 <- xa
  trecho1[1] = setInstruction(2, ya, -1, 4); //reg2 <- ya
  trecho1[2] = setInstruction(1, posInicial, -1, 5); //ram[0] <- reg1
  trecho1[3] = setInstruction(2, posInicial + 1, -1, 5); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);
  trecho1 = destroiTrecho(trecho1, 5);

  //instruções para o ponto B
  Instruction **trecho2 = (Instruction **) malloc(5 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, xb, -1, 4); //reg1 <- xb
  trecho2[1] = setInstruction(2, yb, -1, 4); //reg2 <- yb
  trecho2[2] = setInstruction(1, posInicial + 2, -1, 5); //ram[2] <- reg1 (xb)
  trecho2[3] = setInstruction(2, posInicial + 3, -1, 5); //ram[3] <- reg2 (yb)
  trecho2[4] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho2, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);
  trecho2 = destroiTrecho(trecho2, 5);

  //calcula distancia => dist = sqrt( (xb-xa)^2 + (yb-ya)^2 )
  int dx = getDado(posInicial + 2, ram) - getDado(posInicial, ram); //xb - xa
  int dy = getDado(posInicial + 3, ram) - getDado(posInicial + 1, ram); //yb - ya

  int aux1 = programaExponencial(cpu, ram, posInicial + 5, dx, 2); //(xb-xa)^2  //utiliza posInicial + 5 para não sobrescrever dados úteis
  int aux2 = programaExponencial(cpu, ram, posInicial + 5, dy, 2); //(yb-ya)^2 
  
  int dist = programaRaizAproximada(cpu, ram, posInicial + 5, aux1 + aux2); //sqrt(aux1 + aux2)

  //instruções para o resultado
  Instruction **trecho3 = (Instruction **) malloc(3 * sizeof(Instruction *));
  trecho3[0] = setInstruction(1, dist, -1, 4); //reg1 <- dist
  trecho3[1] = setInstruction(1, posInicial + 4, -1, 5); //ram[4] <- reg1
  trecho3[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho3, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);
  trecho3 = destroiTrecho(trecho3, 3);

  //retorna resultado e zera as posições utilizadas da ram
  int result = getDado(posInicial + 4, ram);
  ram = zerarRAM(ram, posInicial, posInicial + 5);

  return result;
}

int programaDeterminante2x2(CPU* cpu, RAM* ram, int posInicialRAM, int posInicialMatriz) {
  /*
  [a b] [00 01]
  [c d] [10 11]
  */
  
  int diagonalP, diagonalS;
  int enderecos[4]; // [a, b, c, d]
  int baseTemp = posInicialMatriz + 10;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      enderecos[(i * 2) + j] = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatriz, 2, 2, i, j);
    }
  }

  // Diagonal principal: a x d
  diagonalP = programaMulti(cpu, ram, baseTemp, getDado(enderecos[0], ram), getDado(enderecos[3], ram));

  // Diagonal secundária: b x c
  diagonalS = programaMulti(cpu, ram, baseTemp, getDado(enderecos[1], ram), getDado(enderecos[2], ram));

  Instruction **trecho1 = (Instruction **)malloc(6 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, diagonalP, -1, 4);
  trecho1[1] = setInstruction(1, posInicialRAM, -1, 5); // manda o valor do reg1 pra ram[posInicialRam]
  trecho1[2] = setInstruction(2, diagonalS, -1, 4);
  trecho1[3] = setInstruction(2, posInicialRAM + 1, -1, 5); 

  // faz a subtração da diagonal P e da diagonal S e salva na primeira posição da RAM
  trecho1[4] = setInstruction(posInicialRAM, posInicialRAM + 1, posInicialRAM, 1);
  trecho1[5] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);

  trecho1 = destroiTrecho(trecho1, 6);

  int det = getDado(posInicialRAM, ram);
  ram = zerarRAM(ram, posInicialMatriz, posInicialMatriz + 2);

  return det;
}

int programaDeterminante3x3(CPU* cpu, RAM *ram, int posInicialRAM, int posInicialMatriz) {
  /*
  [m00 m01 m02]
  [m10 m11 m12]
  [m20 m21 m22]
  */

  int enderecos_matriz[9]; // vai de posInicialMatriz ate posInicialMatriz + 8
  int baseTemp = posInicialMatriz + 10;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      enderecos_matriz[(i * 3) + j] = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatriz, 3, 3, i, j);
    }
  }

  int m00 = getDado(enderecos_matriz[0], ram);
  int m01 = getDado(enderecos_matriz[1], ram);
  int m02 = getDado(enderecos_matriz[2], ram);
  int m10 = getDado(enderecos_matriz[3], ram);
  int m11 = getDado(enderecos_matriz[4], ram);
  int m12 = getDado(enderecos_matriz[5], ram);
  int m20 = getDado(enderecos_matriz[6], ram);
  int m21 = getDado(enderecos_matriz[7], ram);
  int m22 = getDado(enderecos_matriz[8], ram);


  // Calcular as 3 diagonais principais e as 3 diagonais secundárias
  int p1, p2, p3, s1, s2, s3;
  int resultP = posInicialRAM; // onde a soma das diagonais principais será armazenado
  int resultS = posInicialRAM + 1;
  int determinante = posInicialRAM + 6;

  // p1 = m00 * m11 * m22
  p1 = programaMulti(cpu, ram, baseTemp, m00, m11);
  p1 = programaMulti(cpu, ram, baseTemp, p1, m22);

  // p2 = m01 * m12 * m20
  p2 = programaMulti(cpu, ram, baseTemp, m01, m12);
  p2 = programaMulti(cpu, ram, baseTemp, p2, m20);

  // p3 = m02 * m10 * m21
  p3 = programaMulti(cpu, ram, baseTemp, m02, m10);
  p3 = programaMulti(cpu, ram, baseTemp, p3, m21);

  // s1 = m02 * m11 * m20
  s1 = programaMulti(cpu, ram, baseTemp, m02, m11);
  s1 = programaMulti(cpu, ram, baseTemp, s1, m20);

  // s2 = m01 * m10 * m22
  s2 = programaMulti(cpu, ram, baseTemp, m01, m10);
  s2 = programaMulti(cpu, ram, baseTemp, s2, m22);

  // s3 = m00 * m12 * m21
  s3 = programaMulti(cpu, ram, baseTemp, m00, m12);
  s3 = programaMulti(cpu, ram, baseTemp, s3, m21);

  Instruction **trecho = (Instruction **)malloc(18 * sizeof(Instruction *));
  // trecho para diagonal principal
  trecho[0] = setInstruction(1, p1, -1, 4); // reg1 <- p1
  trecho[1] = setInstruction(1, resultP, -1, 5); // ram[resultP] <- reg1 (p1)
  trecho[2] = setInstruction(2, p2, -1, 4); // reg2 <- p2
  trecho[3] = setInstruction(2, resultP + 2, -1, 5); // ram[resultP + 2] <- reg2;
  trecho[4] = setInstruction(resultP, resultP + 2, resultP, 0); // ram[resultP] = ram[resultP] + ram[resultP + 2]
  trecho[5] = setInstruction(2, p3, -1, 4);
  trecho[6] = setInstruction(2, resultP + 3, -1, 5); // reg2 <- ram[resultP + 3]
  trecho[7] = setInstruction(resultP, resultP + 3, resultP, 0); // p1 + p2 + p3

  // trecho pra diagonal secundária
  trecho[8] = setInstruction(1, s1, -1, 4);
  trecho[9] = setInstruction(1, resultS, -1, 5); // ram[resultS] <- reg1 (s1)
  trecho[10] = setInstruction(2, s2, -1, 4);
  trecho[11] = setInstruction(2, resultS + 3, -1, 5); // ram[resultS + 3] <- reg2;
  trecho[12] = setInstruction(resultS, resultS + 3, resultS, 0); // ram[resultS] = ram[resultS] + ram[resultS + 3]
  trecho[13] = setInstruction(2, s3, -1, 4);
  trecho[14] = setInstruction(2, resultS + 3, -1, 5);
  trecho[15] = setInstruction(resultS, resultS + 3, resultS, 0);

  // cálculo do determinante
  trecho[16] = setInstruction(resultP, resultS, determinante, 1);
  trecho[17] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho, 18);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 18);
  trecho = destroiTrecho(trecho, 18);

  int result = getDado(determinante, ram);
  ram = zerarRAM(ram, posInicialRAM, posInicialRAM + 6);

  return result;
}

int programaMatrizTransposta(CPU *cpu, RAM *ram, int posInicialRAM, int posInicialMatrizA, int posInicialMatrizT, int n, int m) {
  // n -> n de linhas da matriz original
  // m -> n de colunas da matriz original

  int rowT = m; // n de linhas da matriz transposta é o n de colunas da original
  int colT = n;

  int baseTemp = posInicialRAM;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int endereco_memoria = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatrizA, n, m, i, j);

      int val = getDado(endereco_memoria, ram);

      int endereco_escrita = encontrarPosicaoMatriz(cpu, ram, baseTemp, posInicialMatrizT, rowT, colT, j, i);

      setDado(endereco_escrita, val, ram);
    }
  }

  return posInicialMatrizT;
}