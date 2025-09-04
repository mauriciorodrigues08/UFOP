// Maurício de Oliveira Santos Rodrigues
// 25.1.4020

#ifndef UTILS_H
#define UTILS_H

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_COLOR_GREY       "\x1b[90m"
#define ANSI_COLOR_PURPLE     "\x1b[95m"
#define ANSI_COLOR_ORANGE     "\x1b[38;5;208m"
#define ANSI_COLOR_BROWN      "\x1b[38;5;130m"

#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"
#define ANSI_BG_COLOR_GREY    "\x1b[100m"
#define ANSI_BG_COLOR_PURPLE  "\x1b[105m"
#define ANSI_BG_COLOR_ORANGE  "\x1b[48;5;208m"
#define ANSI_BG_COLOR_BROWN   "\x1b[48;5;130m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define GREY(string)       ANSI_COLOR_GREY       string ANSI_RESET
#define PURPLE(string)     ANSI_COLOR_PURPLE     string ANSI_RESET
#define ORANGE(string)     ANSI_COLOR_ORANGE     string ANSI_RESET
#define BROWN(string)      ANSI_COLOR_BROWN      string ANSI_RESET

#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET
#define BG_GREY(string)    ANSI_BG_COLOR_GREY    string ANSI_RESET
#define BG_PURPLE(string)  ANSI_BG_COLOR_PURPLE  string ANSI_RESET
#define BG_ORANGE(string)  ANSI_BG_COLOR_ORANGE  string ANSI_RESET
#define BG_BROWN(string)   ANSI_BG_COLOR_BROWN   string ANSI_RESET

//defines para printar tabuleiro
#define TAB_HOR "━━━━━━"
#define TAB_VER "┃"
#define TAB_TL  "┏"
#define TAB_ML  "┣"
#define TAB_BL  "┗"
#define TAB_TJ  "┳"
#define TAB_MJ  "╋"
#define TAB_BJ  "┻"
#define TAB_TR  "┓"
#define TAB_MR  "┫"
#define TAB_BR  "┛"

//structs utilizadas
typedef struct {
  char name[27];
  int score;
  int undo;
  int change;
  int size;
  int **tab;
  int isWin;
  int isActive;
} Player;

typedef struct {
  char name[27];
  int score;
} RankPosition;

typedef struct {
  int qtd4x4;
  int qtd5x5;
  int qtd6x6;
  RankPosition positions4x4[10];
  RankPosition positions5x5[10];
  RankPosition positions6x6[10];
} Ranking;

//protótipos das funções utilizadas

//jogo
void game();
void printTable(int size, int **tab, int undo, int change, int score, char *name);
void addBlock(int **tab, int size);
void exitGame(Player *players);

//menu
void menu(Player *players, char *op, Player *lastMove);
void printMenu();
void opChoose(char *op);
void help();
void newGame(Player *players, Player *lastMove);
void playerRegister(Player *players);
int sizeChoose();
void matInitiate(int **mat, int size);
void continueCurrentGame(Player *players);
void saveGame(Player *player, Player *lastMove);
void loadGame(Player *player, Player *lastMove);

//movimentos
void moveUp(Player *player, Player *lastPlay, int *moveCount);
void moveLeft(Player *player, Player *lastPlay, int *moveCount);
void moveDown(Player *player, Player *lastPlay, int *moveCount);
void moveRight(Player *player, Player *lastPlay, int *moveCount);
void moveVerify(int moveCount, Player *player);
void printMoves();
void moveChoose(char moveOp[20]);
int opCmp(char *moveOp);

//movimentos especiais
int getPositions(char *moveOp, char *p1, char *p2, int size, int **tab);
void change(char *p1, char *p2, Player *player, Player *lastMove);
void saveLastMove(Player *player, Player *lastMove);
void undo(Player *player, Player *lastMove);

//verificação de vitória e derrota
int winVerify(Player *players);
int win();
void failVerify(Player *players, Player *lastMove);
int fail(Player *players);

//funções gerais
void retiraN(char *string);
void limpa_buffer();
void limpa_terminal();
void upper(char *op);
int **matMalloc(int size);
void matFree(int **mat, int size);
void retira_espacos(char *string);
void retira_espacos(char *str);

//funções do ranking
void loadRanking(Ranking *ranking);
void saveRanking(Ranking *ranking);
void updateRanking(Player *player);
void att(RankPosition *positions, int *qtd, RankPosition new);
void order(RankPosition *positions, int qtd);
void printRanking();

#endif