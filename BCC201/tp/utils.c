// Maurício de Oliveira Santos Rodrigues
// 25.1.4020

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

void game() {
  //declaração de variáveis
  Player player = {0}, lastMove = {0}; //controle do jogador inicializado com 0
  char op[20], moveOp[20], p1[3], p2[3], opContinue[10]; //strings utilizadas
  int opResult, moveCount, posValidate, winContinue; 

  do {
    //rodando menu
    menu(&player, op, &lastMove);

    //verifica se há jogo ativo antes de rodar do jogo
    if (op[0] == 'C' && !player.isActive) {
      limpa_terminal();
      printf("Nenhum arquivo encontrado com esse nome!\n\n");
      continue;
    }

    //verifica se foi escolhida opção apenas de texto
    if (op[0] == 'M' || op[0] == 'S' || op[0] == 'A' || op[0] == 'R')
      continue;

    //verifica se existe jogo ativo
    if (!player.isActive) {
      limpa_terminal();
      printf("Nenhum jogo em andamento!\n\n");
      continue;
    }

    //rodando jogo
    do {
      //printando tabela
      printTable(player.size, player.tab, player.undo, player.change, player.score, player.name);

      //verificando vitória
      if (player.isWin == 0) {
        winContinue = winVerify(&player);
        
        //verifica se jogador quer sair após ganhar e libera memórias alocadas
        if (winContinue == 1) {
          do {
            printf("Deseja salvar o jogo? (sim/nao): ");
            fgets(opContinue, 9, stdin);
            retiraN(opContinue);
            upper(opContinue);
          } while(strcmp(opContinue, "SIM") && strcmp(opContinue, "NAO"));

          if (!strcmp(opContinue, "SIM"))
            saveGame(&player, &lastMove);

          matFree(player.tab, player.size);
          
          if (lastMove.tab != NULL) {
            matFree(lastMove.tab, lastMove.size);
            lastMove.tab = NULL;
          }
          
          player.isActive = 0;
          break;
        }
      }

      //verifica derrota
      failVerify(&player, &lastMove);

      //escolhendo prox movimento
      printMoves();
      moveChoose(moveOp);

      if( !(strcmp(moveOp, "VOLTAR")) ) {
        printf("\n");
        break;
      }
      //verifica se o comando de troca foi utilizado corretamente
      else if (moveOp[0] == 'T' && moveOp[1] == ' ' && strlen(moveOp) == 7) { 
        if (player.change == 0) {
          limpa_terminal();
          printf("Você não possui jogadas 'troca'!\n\n");
        }
        else {
          posValidate = getPositions(moveOp, p1, p2, player.size, player.tab);
          if (posValidate == 0)  {
            limpa_terminal();
            change(p1, p2, &player, &lastMove);
            player.change--;
          }
          else {
            limpa_terminal();
            printf("Posições inválidas! Tente novamente...\n\n");
          }
        }
      }
      else {
        opResult = opCmp(moveOp);
        switch (opResult) {
        case 1:
          moveCount = 0;
          moveUp(&player, &lastMove, &moveCount);
          moveVerify(moveCount, &player);
          break;
                    
        case 2:
          moveCount = 0;
          moveLeft(&player, &lastMove, &moveCount);
          moveVerify(moveCount, &player);
          break;

        case 3:
          moveCount = 0;
          moveDown(&player, &lastMove, &moveCount);
          moveVerify(moveCount, &player);
          break;

        case 4:
          moveCount = 0;
          moveRight(&player, &lastMove, &moveCount);
          moveVerify(moveCount, &player);
          break;
        
        case 5:
          undo(&player, &lastMove);
          break;

        default:
          limpa_terminal();
          printf("Movimento inválido! Tente novamente...\n\n");
        }
      }
      
      //quando o movimento for "voltar" sai do loop
      if (!strcmp(moveOp, "VOLTAR")) break;
    } while (1);
    
    //sai do loop somente pela função exit()
  } while(1);
}

//printa o menu na tela
void printMenu() {
  printf("================ MENU - 2048 ================");
  printf("\n(R) Sair");
  printf("\n(N) Novo Jogo");
  printf("\n(J) Continuar Jogo Atual");
  printf("\n(C) Carregar Jogo Salvo");
  printf("\n(S) Salvar Jogo Atual");
  printf("\n(M) Mostrar Ranking");
  printf("\n(A) Ajuda com as Instruções de Como Jogar");
  printf("\n=============================================");
  printf("\n");
}

//recebe a opção escolhida pelo usuário
void opChoose(char *op) {
  printf("Digite sua escolha: ");
  fgets(op, 10, stdin);
  retiraN(op);  //remove o '\n' final (se existir)

  //se a entrada for maior que 1 caractere, marca como inválida
  if (strlen(op) > 1) {
    op[0] = '\0';
  }
}

//seleciona qual função do jogo será utilizada
void menu(Player *player, char *op, Player *lastMove) {
  do {
    printMenu();
    opChoose(op);
    upper(op);

    if (strlen(op) != 1) {
      limpa_terminal();
      printf("\nOpção inválida! Escolha novamente...\n\n");
      continue;
    }

    switch(op[0]) {
      case 'R':
        exitGame(player); 
        break;
      
      case 'N':
        newGame(player, lastMove);
        break;
      
      case 'J':
        continueCurrentGame(player);
        break;
      
      case 'C':
        loadGame(player, lastMove);
        break;
        
      case 'S':
        saveGame(player, lastMove);
        break;
        
      case 'M':
        printRanking();
        break;
      
      case 'A':
        help();
        break;
        
      default:
        limpa_terminal();
        printf("\nOpção inválida! Escolha novamente...\n");
        continue;
      }
      
      break;  //sai do loop se a opção for validada
    } while (1); //loop "infinito"
}

//printa o texto de ajuda na tela
void help() {
  limpa_terminal();
  printf("\nCOMO JOGAR 2048\n");

  printf("\nO JOGO:\nO 2048 clássico é jogado em um tabuleiro de 4x4, com peças numéricas que deslizam suavemente quando o jogador as move em um dos quatro sentidos disponíveis: para cima, para baixo, à esquerda e à direita. A cada movimento, um novo número aparece aleatoriamente em um local vazio no tabuleiro (com um valor de 2 ou 4). As peças (blocos) deslizam o mais longe possível na direção escolhida até que eles sejam interrompidos por qualquer outro bloco ou a borda do tabuleiro. Se duas peças do mesmo número colidem durante a movimentação, elas irão se fundir e a posição terá o valor total das duas peças que colidiram. A peça resultante não pode se fundir com outra peça novamente na mesma jogada. Blocos com pontuação maior possuem cores diferentes.\n");

  printf("\nREGRAS:\n1. O jogo começa com duas posições aleatórias do tabuleiro preenchidas.\n2. A cada jogada, o jogador deve escolher uma direção (para cima, para baixo, para a esquerda ou para a direita).\n3. Todas as peças se movem o máximo possível nessa direção, algumas se movem mais do que outras. Duas peças adjacentes (somente nessa direção) com números iguais se combinam em uma contendo a soma desses números.\n4. Um movimento é válido quando pelo menos uma peça pode ser movida, inclusive por combinação.\n5. Uma nova peça é gerada ao final de cada jogada em uma posição vazia escolhida aleatoriamente (se houver)\n6. Na maioria das vezes, um novo 2 deve ser adicionado, mas ocasionalmente, um 4.\n7. Para vencer, o jogador deve criar uma peça com o número 2048.\n8. O jogador perde se não houver movimentos válidos possíveis.\n9. A cada peça no valor de 256 construída o jogador recebe um movimento 'Desfazer'\n10. A cada peça no valor de 512 construída o jogador recebe um movimento 'Trocar de Posição'");

  printf("\n\nPressione enter para voltar ao menu...");
  limpa_buffer();
  limpa_terminal();
}

//criação de um novo jogo
void newGame(Player *player, Player *lastMove) {
  limpa_terminal();
  printf("NOVO JOGO\n");

  //verifica se já existe jogo ativo e libera a meória alocada
  if (player->tab != NULL) {
    matFree(player->tab, player->size);
    player->tab = NULL;
  }

  if (lastMove->tab != NULL) {
    matFree(lastMove->tab, lastMove->size);
    lastMove->tab = NULL;
  }

  
  //inicializa valores da struct Player
  int  s = sizeChoose();
  player->size = s;
  player->score = 0;
  player->undo = 0;
  player->change = 0;
  player->isWin = 0;
  player->isActive = 1;

  //alocação do tabuleiro
  player->tab = matMalloc(s);
  lastMove->tab = matMalloc(s);
  lastMove->size = s;

  //inicializa tabuleiro com 0
  matInitiate(player->tab, s);  

  //cadastra jogador
  playerRegister(player);
  
  //gera dois blocos aleatórios
  addBlock(player->tab, player->size);
  addBlock(player->tab, player->size);

  //limpa terminal
  limpa_terminal();
}

void playerRegister(Player *player) {
  printf("Digite seu nome: ");
  fgets(player->name, 26, stdin);
  retiraN(player->name);
}

//escolha do tamanho do tabuleiro
int sizeChoose() {
  int op;

  do {
    printf("\n(4) Jogo padrão 4x4\n(5) Jogo 5x5\n(6) Jogo 6x6.\nEscolha sua opção: ");
    if (scanf("%d", &op) != 1) { //analisando caso for digitado caracteres (scanf retorna 1 como um código de verificação correta)
      limpa_buffer();
      op = 0; //força repetição
    }
    if (op < 4 || op > 6) {
      limpa_terminal();
      printf("Opção inválida! Escolha novamente...\n");
    }
  } while (op < 4 || op > 6);

  limpa_buffer();
  return op;
}

//printa na tela os movimentos possíveis
void printMoves() {
  printf("\n(a) Mover para esquerda\n(d) Mover para direita\n(s) Mover para baixo\n(w) Mover para cima\n(u) Desfazer último movimento\n(t <pos1> <pos2>) Trocar de posição\n(voltar) Voltar para o menu\n");
}

//confirma saída do jogador
void exitGame(Player *player) {
  char aux[10];
  
  while (1) {
    printf("Deseja realmente sair do jogo (sim/nao)? ");
    fgets(aux, 10, stdin);
    retiraN(aux);
    upper(aux);
    
    if ( !(strcmp(aux, "SIM")) ) {
      if (player->isActive) {
        player->isActive = 0;
        matFree(player->tab, player->size);
      }
      
      printf("Saindo do jogo...\n");
      exit(0);
    } 
    else if ( !(strcmp(aux, "NAO")) ) {
      limpa_terminal();
      printf("Voltando ao menu principal...\n\n");
      break;
    } else {
      printf("Resposta inválida. Por favor, digite 'sim' ou 'não'.\n");
    }
  }
}

//retira o \n da string
void retiraN(char *string) {
  int tam = strlen(string);
  if (tam > 0 && string[tam - 1] == '\n')
    string[tam - 1] = '\0';
  else {
    limpa_buffer();
  }
}

//limpa o terminal
void limpa_terminal() {
  system("clear");
}

//limpa o buffer
void limpa_buffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF); 
}

//alocação de matrizes inteiras
int **matMalloc(int size) {
  int **mat = malloc(size * sizeof(int *));

  for (int i = 0; i < size; i++) {
    mat[i] = malloc(size * sizeof(int));
  }
  
  return mat;
}

//inicializa matriz de inteiros com 0
void matInitiate(int **mat, int size) {
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      mat[i][j] = 0;
}

//libera a memória alocada pela matriz
void matFree(int **mat, int size) {
  for (int i = 0; i < size; i++)
    free(mat[i]);
  free(mat);
}

//printa o tabuleiro atual do jogador
void printTable(int size, int **tab, int undo, int change, int score, char *name) {
  //printando trocas, desfazer e pontuação
  printf("Nome: %s\n", name);
  printf("Pontuação: %d\n", score);
  printf("Desfazer: %d\n", undo);
  printf("Trocas: %d\n\n", change);

  //printando coordenadas horizontais
  printf("   ");
  for (int i=1; i<=size; i++) {
    printf("%4d   ", i);
  }

  //printando primeira linha
  printf("\n  " TAB_TL);
  for (int i=0; i<size-1; i++)
    printf(TAB_HOR TAB_TJ);
  printf(TAB_HOR TAB_TR "\n");

  //printando meio
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
      
      if (j==0)
        printf("%c ", 'A'+i);
      
      printf(TAB_VER);
      if (tab[i][j] == 0)
        printf("      ");
      else if (tab[i][j] == 2) 
        printf(BG_WHITE(BLACK(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 4) 
        printf(BG_GREY(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 8) 
        printf(BG_CYAN(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 16) 
        printf(BG_GREEN(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 32) 
        printf(BG_YELLOW(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 64) 
        printf(BG_ORANGE(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 128) 
        printf(BG_BLUE(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 256) 
        printf(BG_MAGENTA(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 512) 
        printf(BG_PURPLE(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] == 1024) 
        printf(BG_RED(WHITE(BOLD("%6d"))), tab[i][j]);

      else if (tab[i][j] >= 2048) 
        printf(BG_BROWN(WHITE(BOLD("%6d"))), tab[i][j]);
    }
    printf(TAB_VER);

    //verificando se ultima linha e printando
    if (i < size-1) {
      printf("\n  " TAB_ML);
      for (int j=0; j<size - 1; j++)
        printf(TAB_HOR TAB_MJ);
      printf(TAB_HOR TAB_MR "\n");
    } else {
      printf("\n  " TAB_BL);
      for (int j=0; j<size-1; j++)
        printf(TAB_HOR TAB_BJ);
      printf(TAB_HOR TAB_BR "\n");
    }
  }
}

//pega o movimento escolhido
void moveChoose(char moveOp[20]) {
  printf("Escolha seu movimento: ");
  fgets(moveOp, 20, stdin);
  retiraN(moveOp);
  upper(moveOp);
  retira_espacos(moveOp);
}

//adiciona um bloco ao tabuleiro
void addBlock(int **tab, int size) {
  int p1, p2, n, res;
  
  do {
    p1 = rand() % size;
    p2 = rand() % size;
  } while (tab[p1][p2] != 0); //evita posições que já esteja ocupadas

  if (size == 4) {
    res = rand() % 10;
    if (res<9) n = 2; //90% de chance
    else n = 4; //10% de chance
  }

  if (size == 5) {
    res = rand() % 100;
    if (res<85) n = 2; //85% de chance
    else n = 4; //15% de chance
  }

  if (size == 6) {
    res = rand() % 10;
    if (res<8) n = 2; //80% de chance
    else n = 4; //20% de chance
  }

  tab[p1][p2] = n;
}

//move os números para cima
void moveUp(Player *player, Player *lastMove, int *moveCount) {
  //salva tabuleiro atual antes de realizar movimento
  saveLastMove(player, lastMove);

  int size = player->size;
  
  for (int j = 0; j < size; j++) { // percorre as colunas

    //compacta os valores (desloca para cima)
    int target = 0; //índice onde o próximo número != 0 deve ser colocado
    for (int i = 0; i < size; i++) {
      if (player->tab[i][j] != 0) { // verifica se existe um número
        if (target != i) { // verifica se ele já está na posição correta
          player->tab[target][j] = player->tab[i][j]; // move o número para o índice desejado
          player->tab[i][j] = 0; // zera a posição antiga
          (*moveCount)++; //incrementa o contador de movimentos
        }
        target++; //incrementa o índice desejado, para evitar sobreposição
      }
    }
    
    //soma valores iguais
    for (int i = 0; i < size-1; i++) {
      if (player->tab[i][j] != 0 && player->tab[i][j] == player->tab[i + 1][j]) { //verifica se dois valores seguidos são iguais
        player->tab[i][j] *= 2; //dobra o valor
        (*moveCount)++;
        player->score += player->tab[i][j];
        player->tab[i + 1][j] = 0; //apaga número somado

        if (player->tab[i][j] == 256)
          (player->undo)++;
        
        if (player->tab[i][j] == 512)
          (player->change)++;
      }
    }
    
    //compacta novamente os valores (mesma lógica)
    target = 0;
    for (int i = 0; i < size; i++) {
      if (player->tab[i][j] != 0) {
        if (target != i) {
          player->tab[target][j] = player->tab[i][j];
          player->tab[i][j] = 0;
        }
        target++;
      }
    }
  }
}

//move os números para baixo
void moveDown(Player *player, Player *lastMove, int *moveCount) {
  //salva tabuleiro atual antes de realizar movimento
  saveLastMove(player, lastMove);

  int size = player->size;
  
  for (int j = 0; j < size; j++) { //percorre as colunas

    //compacta os valores (desloca para baixo)
    int target = size-1; //índice onde o próximo número != 0 deve ser colocado
    for (int i = size-1; i >= 0; i--) {
      if (player->tab[i][j] != 0) { //verifica se existe um número
        if (target != i) { //verifica se ele já está na posição correta
          player->tab[target][j] = player->tab[i][j]; //move o número para o índice desejado
          player->tab[i][j] = 0; //zera o antigo índice
          (*moveCount)++;
        }
        target--; //decrementa o índice desejado, para evitar sobreposição
      }
    }
    
    //soma valores iguais
    for (int i = size-1; i > 0; i--) {
      if (player->tab[i][j] != 0 && player->tab[i][j] == player->tab[i-1][j]) { //verifica se dois números seguidos são iguais
        player->tab[i][j] *= 2; //dobra o valor
        (*moveCount)++;
        player->score += player->tab[i][j];
        player->tab[i-1][j] = 0; //zera valor somado

        if (player->tab[i][j] == 256)
          (player->undo)++;
        
        if (player->tab[i][j] == 512)
          (player->change)++;
      }
    }

    //compacta novamente (mesma lógica)
    target = size-1;
    for (int i = size-1; i >= 0; i--) {
      if (player->tab[i][j] != 0) {
        if (target != i) {
          player->tab[target][j] = player->tab[i][j];
          player->tab[i][j] = 0;
        }
        target--;
      }
    }
  }
}

//move os números para a esquerda
void moveLeft(Player *player, Player *lastMove, int *moveCount) {
  //salva tabuleiro atual antes de realizar movimento
  saveLastMove(player, lastMove);
  
  int size = player->size;
  
  for (int i = 0; i < size; i++) { //percorre as linhas

    //compacta os valores (desloca para esquerda)
    int target = 0; //índice onde o próximo número != 0 deve ser colocado
    for (int j = 0; j < size; j++) { 
      if (player->tab[i][j] != 0) { //verifica se existe um número
        if (target != j) { //verifica se ele já está na posição correta
          player->tab[i][target] = player->tab[i][j]; //move para o índice desejado
          player->tab[i][j] = 0; //zera posição antiga
          (*moveCount)++;
        }
        target++; //incrementa o índice desejado para evitar sobreposição
      }
    }
    
    //soma valores iguais
    for (int j = 0; j < size-1; j++) {
      if (player->tab[i][j] != 0 && player->tab[i][j] == player->tab[i][j+1]) { //verifica se dois valores seguidos são iguais
        player->tab[i][j] *= 2; //dobra o valor
        (*moveCount)++;
        player->score += player->tab[i][j];
        player->tab[i][j+1] = 0; //zera número somado

        if (player->tab[i][j] == 256)
          (player->undo)++;
        
        if (player->tab[i][j] == 512)
          (player->change)++;
      }
    }

    //compacta novamente (mesma lógica)
    target = 0;
    for (int j = 0; j < size; j++) {
      if (player->tab[i][j] != 0) {
        if (target != j) {
          player->tab[i][target] = player->tab[i][j];
          player->tab[i][j] = 0;
        }
        target++;
      }
    }
  }
}

//move os números para a direita
void moveRight(Player *player, Player *lastMove, int *moveCount) {
  //salva tabuleiro atual antes de realizar movimento
  saveLastMove(player, lastMove);

  int size = player->size;
  
  for (int i = 0; i<size; i++) { //percorre as linhas
    
    //compacta os valores (desloca para direita)
    int target = size-1; //índice onde o próximo número != 0 deve ser colocado
    for (int j = size-1; j>=0; j--) {
      if (player->tab[i][j] != 0) { //verifica se eciste um número
        if (target != j) { //verifica se já não está no índice desejado
          player->tab[i][target] = player->tab[i][j]; //move valor pro índice desejado
          player->tab[i][j] = 0; //zera índice antigo
          (*moveCount)++;
        }
        target--; //decrementa contador para evitar sobreposição
      }
    }

    //soma valores iguais
    for (int j = size-1; j>0; j--) {
      if (player->tab[i][j] != 0 && player->tab[i][j] == player->tab[i][j-1]) { //verifica se dois valores seguidos são iguais 
        player->tab[i][j] *= 2; //dobra o valor
        (*moveCount)++;
        player->score += player->tab[i][j];
        player->tab[i][j-1] = 0; //zera o antigo valor
        
        if (player->tab[i][j] == 256)
          (player->undo)++;
        
        if (player->tab[i][j] == 512)
          (player->change)++;
      }
    }
    
    //compacta novamente (mesma lógica)
    target = size-1;
    for (int j = size-1; j>=0; j--) {
      if (player->tab[i][j] != 0) {
        if (target != j) {
          player->tab[i][target] = player->tab[i][j];
          player->tab[i][j] = 0;
        }
        target--;
      }
    }
  }
}

//compara opção recebida e retorna um valor inteiro
int opCmp(char *moveOp) {
  if ( strlen(moveOp) > 1)
    return -1; 
  else if (moveOp[0] == 'W')
    return 1;
  else if (moveOp[0] == 'A')
    return 2;
  else if (moveOp[0] == 'S')
    return 3;
  else if (moveOp[0] == 'D')
    return 4;
  else if (moveOp[0] == 'U')
    return 5;
  
  return -1;
}

//verifica se o movimento é válido
void moveVerify(int moveCount, Player *player) {
  if (moveCount > 0) {
    addBlock(player->tab, player->size);

    if (player->size == 6) 
      addBlock(player->tab, player->size);
    
    limpa_terminal();
  }
  else {
      limpa_terminal();
      printf("Movimento inválido! Tente novamente...\n\n");
  }
}

//pega as posições dos valores a serem trocados e retorna -1 se falhou ou 0 se verificou
int getPositions(char *moveOp, char *p1, char *p2, int size, int **tab) {
  int aux, i, j;

  //verificando primeira posição
  if ( moveOp[2] >= 'A' && moveOp[2] <= 'A' + (size - 1) ) { //verifica se a letra é válida
    p1[0] = moveOp[2];
    
    aux = moveOp[3] - '1'; //transforma o algarismo em int
    if (moveOp[3] >= '1' && aux <= size) { //verifica se o número é válido
      p1[1] = moveOp[3];
      p1[2] = '\0';
    }
    else return -1; //número inválido
  }
  else return -1; //letra inválida

  //verificando espaço entre posições
  if (moveOp[4] != ' ') return -1;

  //verificando segunda posição
  if ( moveOp[5] >= 'A' && moveOp[5] <= 'A' + (size + 1) ) { //verifica se a letra é válida
    p2[0] = moveOp[5];
    
    aux = moveOp[6] - '1'; //transforma o algarismo em int
    if (moveOp[6] >= '1' && aux <= size) {  //verifica se o número é válido
      p2[1] = moveOp[6];
      p2[2] = '\0';
    }
    else return -1; //número inválido
  }
  else return -1; //letra inválida

  //verificando se as posições escolhidas não são 0
  //posição 1
  i = p1[0] - 'A';
  j = p1[1] - '1';
  if (tab[i][j] == 0) return -1; //primeira posição = 0
  
  //posição 2
  i = p2[0] - 'A';
  j = p2[1] - '1';
  if (tab[i][j] == 0) return -1; //segunda posição = 0

  return 0; //todas as validações corretas
}

//realiza a troca de posições
void change(char *p1, char *p2, Player *player, Player *lastMove) {
  //salvando ultima jogada
  saveLastMove(player, lastMove);

  //trnsformando char em int
  int i1 = p1[0] - 'A';
  int j1 = p1[1] - '1';
  int i2 = p2[0] - 'A';
  int j2 = p2[1] - '1';
  
  //trocando posições
  int aux = player->tab[i1][j1];
  player->tab[i1][j1] = player->tab[i2][j2];
  player->tab[i2][j2] = aux;
}

//verifica se o jogo foi vencido
int winVerify (Player *player) {
  int winContinue = 0;
  int s = player->size;

  if (player->isWin == 1)
    return -1;
  else {
    for (int i=0; i<s; i++)
      for (int j=0; j<s; j++) 
        if (player->tab[i][j] == 2048) {
          player->isWin = 1;
          winContinue = win();
        }
  }

  return winContinue;
}

//informa vitória
int win() {
  char op[5];

  printf("\n\nVOCÊ VENCEU!!!\nDeseja continuar o jogo? (sim/nao): ");
  
  do {
    fgets(op, 5, stdin);    
    retiraN(op);
    upper(op);
    
    if (strcmp(op, "SIM") != 0 && strcmp(op, "NAO") != 0)
      printf("Opção inválida! Digite novamente: ");
  } while (strcmp(op, "SIM") != 0 && strcmp(op, "NAO") != 0);

  if ( !(strcmp(op, "NAO")) ) return 1;
  else return 0;
}

//verifica se há jogadas possíveis
void failVerify(Player *player, Player *lastMove) {
  int size = player->size;
  int **t = player->tab;
  int failContinue;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int valor = t[i][j];

      //verifica se existe espaço vazio
      if (valor == 0)
        return;

      //verifica peça da direita
      if (j < size - 1 && valor == t[i][j + 1]) //verifica se o índice não está na borda da direita
        return;

      //verifica peça de baixo
      if (i < size - 1 && valor == t[i + 1][j]) //verifica se o índice não está na borda de baixo
        return;
    }
  }

  //jogador perde se nenhum if for verdadeiro
  failContinue = fail(player);

  if (failContinue == 1) { 
    matFree(player->tab, player->size);
    
    if (lastMove->tab != NULL) {
      matFree(lastMove->tab, player->size);
      lastMove->tab = NULL;
    }
    
    player->isActive = 0;
    return;
  }
}

int fail(Player *player) {
  char op[10];

  if (player->undo > 0 || player->change > 0) {
    printf("\nVOCÊ PERDEU!!!\nPorém, você possui jogadas especiais...\nDeseja continuar? (sim/nao): ");

    do {
      fgets(op, 5, stdin);    
      retiraN(op);
      upper(op);
      
      if (strcmp(op, "SIM") != 0 && strcmp(op, "NAO") != 0)
        printf("Opção inválida! Digite novamente: ");
    } while (strcmp(op, "SIM") != 0 && strcmp(op, "NAO") != 0);

    if ( !(strcmp(op, "NAO")) ) return 1;
    else return 0;
  }
  else {
    printf("\n\nVOCÊ PERDEU!!!\nPressione enter para voltar ao menu...\n");
    limpa_buffer();
    return 1;
  }
}

void upper(char *str) {
  for (int i = 0; str[i] != '\0'; i++)
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] = toupper(str[i]);
}

void continueCurrentGame(Player *player) {
  limpa_terminal();
    
  //verifica se existe jogo em andamento
  if (!player->isActive) {
    printf("Nenhum jogo em andamento!\n");
    printf("Escolha 'Novo Jogo' no menu.\n\n");
    return;
  }
    
  //continua jogo
  printf("CONTINUANDO JOGO ATUAL...\n\n");
}

void saveLastMove(Player *player, Player *lastMove) {
  lastMove->size = player->size;

  // garante tab alocado e do tamanho correto
  if (lastMove->tab == NULL) {
    lastMove->tab = matMalloc(lastMove->size);
  }

  lastMove->change = player->change;
  lastMove->isActive = player->isActive;
  lastMove->isWin = player->isWin;
  lastMove->score = player->score;
  lastMove->undo = player->undo;
  
  for (int i=0; i<lastMove->size; i++)
    for (int j=0; j<lastMove->size; j++)
      lastMove->tab[i][j] = player->tab[i][j];

  strcpy(lastMove->name, player->name);
}

void undo(Player *player, Player *lastMove) {  
  if (player->undo > 0) {
    //salvando jogada atual

    //desfaz movimento
    for (int i=0; i<player->size; i++)
      for (int j=0; j<player->size; j++)
        player->tab[i][j] = lastMove->tab[i][j];
    
    //refaz stats do último movimento
    player->change = lastMove->change;
    player->isActive = lastMove->isActive;
    player->isWin = lastMove->isWin;
    player->score = lastMove->score;

    //decremento da qtd de desfazer
    player->undo--;
    limpa_terminal();
  }
  else {  
    limpa_terminal();
    printf("Você não possui jogadas 'desfazer'!\n\n");
  }
}

void saveGame(Player *player, Player *lastMove) {
  if (player->isActive) { //verificando se existe jogo ativo
    char arqName[50];
    limpa_terminal();

    //mostra tabuleiro atual
    printf("SEU PROGRESSO ATUAL:\n\n");
    printTable(player->size, player->tab, player->undo, player->change, player->score, player->name);

    printf("\n\nATENÇÃO! SE UM NOME JÁ EXISTENTE FOR DIGITADO O ARQUIVO SERÁ SOBRESCRITO!\n");
    printf("Digite o nome do arquivo de salvamento (adicione extensão .txt): ");
    fgets(arqName, 49, stdin);
    retiraN(arqName);

    FILE* arquivo = fopen(arqName, "w");

    //salvando tamanho desfazer e trocas
    fprintf(arquivo, "%d %d %d\n", player->size, player->undo, player->change);
    
    //salvando pontuação e nome
    fprintf(arquivo, "%d %s\n", player->score, player->name);

    //salvando tabuleiro
    for (int i=0; i<player->size; i++) {
      for (int j=0; j<player->size; j++) {
        fprintf(arquivo, "%d", player->tab[i][j]);
        if (j != player->size-1)
          fprintf(arquivo, " ");
      }
      fprintf(arquivo, "\n");
    }

    //salvando ultimo movimento
    for (int i=0; i<lastMove->size; i++) {
      for (int j=0; j<lastMove->size; j++) {
        fprintf(arquivo, "%d", lastMove->tab[i][j]);
        if (j != player->size-1)
          fprintf(arquivo, " ");
      }
      fprintf(arquivo, "\n");
    }
    
    //fechando arquivo
    fclose(arquivo);

    //atualizando ranking
    updateRanking(player);

    //confirmando salvamento
    limpa_terminal();
    printf("Arquivo salvo com sucesso!\n\n");
  }
  else { //se nenhum jogo ativo
    limpa_terminal();
    printf("Nenhum jogo em andamento! Impossível salvar!\n\n");
  }
}

void loadGame(Player *player, Player *lastMove) {
  char arqName[50];

  //liberando espaço alocado caso exista jogo em andamento
  if (player->isActive) { 
    matFree(player->tab, player->size);
    matFree(lastMove->tab, lastMove->size);
    player->isActive = 0;
  }

  //recebendo nome do arquivo
  printf("Digite o nome do arquivo a ser carregado (adicione extensão): ");
  fgets(arqName, 49, stdin);
  retiraN(arqName);

  //abrindo arquivo
  FILE* arquivo = fopen(arqName, "r");

  //verificando se existe arquivo com nome digitado
  if (arquivo == NULL)
    return;
  else {
    //recebendo tamanho desfazer e trocas
    fscanf(arquivo, "%d %d %d", &player->size, &player->undo, &player->change);

    //alocando tabuleiros
    player->tab = matMalloc(player->size);
    lastMove->tab = matMalloc(player->size);
    lastMove->size = player->size;

    //verificando valores recebidos
    if (player->size < 4 || player->size > 6 || player->undo < 0 || player->change < 0) {
      limpa_terminal();
      printf("Valores do arquivo inválidos!");
      fclose(arquivo);
      return;
    }

    //recebendo pontuação e nome
    fscanf(arquivo, "%d ", &player->score);
    fgets(player->name, 26, arquivo);
    retiraN(player->name);

    //recebendo tabuleiro atual
    for (int i=0; i<player->size; i++)
      for (int j=0; j<player->size; j++)
        fscanf(arquivo, "%d", &player->tab[i][j]);

    //recebendo tabuleiro da ultima jogada
    for (int i=0; i<lastMove->size; i++)
      for (int j=0; j<lastMove->size; j++)
        fscanf(arquivo, "%d", &lastMove->tab[i][j]);

    //fechando arquivo
    fclose(arquivo);
    
    //confirmando carregamento
    limpa_terminal();
    player->isActive = 1;
    printf("Arquivo carregado com sucesso!\n\n");
  }
}

//carrega o ranking em uma struct
void loadRanking(Ranking *ranking) {
  FILE *file = fopen("ranking.dat", "rb");

  //se o arquivo não existe, inicializa o ranking como vazio
  if (file == NULL) {
    ranking->qtd4x4 = 0;
    ranking->qtd5x5 = 0;
    ranking->qtd6x6 = 0;
    return;
  }

  //se o arquivo existe, lê os dados campo por campo
  fread(&ranking->qtd4x4, sizeof(int), 1, file);
  fread(&ranking->qtd5x5, sizeof(int), 1, file);
  fread(&ranking->qtd6x6, sizeof(int), 1, file);

  //lê os arrays de posições se houver dados para ler
  if (ranking->qtd4x4 > 0) {
    fread(ranking->positions4x4, sizeof(RankPosition), ranking->qtd4x4, file);
  }
  if (ranking->qtd5x5 > 0) {
    fread(ranking->positions5x5, sizeof(RankPosition), ranking->qtd5x5, file);
  }
  if (ranking->qtd6x6 > 0) {
    fread(ranking->positions6x6, sizeof(RankPosition), ranking->qtd6x6, file);
  }

  fclose(file);
}

//salva o ranking no arquivo .dat
void saveRanking(Ranking *ranking) {
  //abre o arquivo
  FILE *arquivo = fopen("ranking.dat", "wb");
  if (arquivo == NULL) return;

  //gravando quantidade de jogos
  fwrite(&ranking->qtd4x4, sizeof(int), 1, arquivo);
  fwrite(&ranking->qtd5x5, sizeof(int), 1, arquivo);
  fwrite(&ranking->qtd6x6, sizeof(int), 1, arquivo);

  //gravando as posições de cada tipo de jogo
  fwrite(&ranking->positions4x4, sizeof(RankPosition), ranking->qtd4x4, arquivo);
  fwrite(&ranking->positions5x5, sizeof(RankPosition), ranking->qtd5x5, arquivo);
  fwrite(&ranking->positions6x6, sizeof(RankPosition), ranking->qtd6x6, arquivo);
  
  //fecha arquivo
  fclose(arquivo);
}

//atualiza o ranking
void updateRanking(Player *player) {
  //carrega o ranking atual
  Ranking ranking;
  loadRanking(&ranking);

  //cria uma nova posição
  RankPosition new;
  strcpy(new.name, player->name);
  new.score = player->score;

  //atualização do ranking
  switch(player->size) {
    //jogos 4x4
    case 4:
      // Passa o array de posições e o ENDEREÇO da quantidade
      att(ranking.positions4x4, &ranking.qtd4x4, new);
      break;

    //jogos 5x5
    case 5:
      att(ranking.positions5x5, &ranking.qtd5x5, new);
      break;

    //jogos 6x6
    case 6:
      att(ranking.positions6x6, &ranking.qtd6x6, new);
      break;
  }

  //grava o novo ranking
  saveRanking(&ranking);
}

//atualiza as posições do ranking se necessário
void att(RankPosition *positions, int *qtd, RankPosition new) {
  //se o ranking tem espaço livre, adiciona pontuação atual
  if (*qtd < 10) {
    positions[*qtd] = new;
    (*qtd)++;
  }
  //se o ranking está cheio, verifica se o novo score é maior que o último
  else if (new.score > positions[9].score) {
    positions[9] = new; //substitui o pior score
  }

  //ordenação do ranking
  order(positions, *qtd);
}

//ordena o ranking de forma decrescente
void order(RankPosition *positions, int qtd) {
  for (int i = 0; i < qtd - 1; i++) {
    for (int j = 0; j < qtd - 1 - i; j++) {
      if (positions[j].score < positions[j+1].score) {
        RankPosition tmp = positions[j];
        positions[j] = positions[j+1];
        positions[j+1] = tmp;
      }
    }
  }
}

//printa o ranking na tela
void printRanking() {
  Ranking ranking;
  loadRanking(&ranking);
  limpa_terminal();

  if (ranking.qtd4x4 == 0 && ranking.qtd5x5 == 0 && ranking.qtd6x6 == 0) {
    printf("Nenhuma pontuação registrada!\n\n");
    return;
  }
  else {
    printf("=========== TOP PONTUAÇÕES ===========\n");

    //4x4
    printf("Tabuleiro 4x4:\n");
    if (ranking.qtd4x4 == 0){
      printf("Nenhum jogo realizado neste modo!\n");
    }
    else {
      for (int i = 0; i < ranking.qtd4x4; i++)
      printf("%2d. %-27s %6d\n", i+1, ranking.positions4x4[i].name, ranking.positions4x4[i].score);
    }

    //5x5
    printf("\nTabuleiro 5x5:\n");
    if (ranking.qtd5x5 == 0) {
      printf("Nenhum jogo realizado neste modo!\n");
    }
    else {
      for (int i = 0; i < ranking.qtd5x5; i++)
        printf("%2d. %-27s %6d\n", i+1, ranking.positions5x5[i].name, ranking.positions5x5[i].score);
    }

    //6x6
    printf("\nTabuleiro 6x6:\n");
    if (ranking.qtd6x6 == 0) {
      printf("Nenhum jogo realizado neste modo!\n");  
    }
    else {
      for (int i = 0; i < ranking.qtd6x6; i++)
        printf("%2d. %-27s %6d\n", i+1, ranking.positions6x6[i].name, ranking.positions6x6[i].score);
    }
  }

  printf("======================================\n");
    
  printf("\nPressione enter para voltar ao menu...");
  limpa_buffer();
  limpa_terminal();
}

void retira_espacos(char *str) {
  //verifica se a string é nula
  if (str == NULL) {
    return;
  }
  
  //recebe o tamanho da string
  int t = strlen(str);

  //remove os espaços duplicados
  for (int i = 0; i < t; i++) {
    if (str[i] == ' ' && (i == 0 || str[i-1] == ' ')) {
      for (int j = i; j < t; j++) {
        str[j] = str[j+1];
      }

      t--;
      i--;
    }
  }

  //calcula o tamanho após as remoções e retira espaço do final
  t = strlen(str); 
  if (t > 0 && str[t-1] == ' ') {
    str[t-1] = '\0';
  }
}