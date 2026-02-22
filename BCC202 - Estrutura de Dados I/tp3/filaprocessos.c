//modulos
#include "filaprocessos.h"

//structs
typedef struct Celula {
  Arvore *raiz;
  struct Celula *prox;
} Celula;

struct No {
  Variavel valor;
  struct No *pEsq;
  struct No *pDir;
};

struct Pilha {
  struct Celula *topo;
  struct Celula *ultimo;
};

//declaracao de funcoes locais
void destroiEscopoAux(Arvore *raiz);

//implementacao das funcoes

//cria o escopo
Arvore *criarEscopo(){
  //inicializa uma arvore vazia
  Arvore *raiz = (Arvore *) malloc(sizeof(Arvore));

  //verifica se a alocacao funcionou
  if (raiz != NULL) {
    *raiz = NULL;
  }

  return raiz;
}

//adiciona uma variavel ao escopo atual
bool adicionaVar(Arvore *raiz, Variavel *var){
  //caso a arvore nao existe retorna false
  if(!raiz)
    return false;

  //caso a arvore ou sub-arvore esteja vazia, inicializa o No raiz
  if(!(*raiz)){
    No *novo = (No*) malloc(sizeof(No));
    if(!novo)
      return false;
    
    novo->valor = *var;
    novo->pDir = NULL;
    novo->pEsq = NULL;

    *raiz = novo;
    return true;
  }

  //determina se a incersao deve ocorrer na sub-arvore da esquerda ou da direita
  int result = strcmp((*raiz)->valor.nome, var->nome);

  if(result > 0) 
    return adicionaVar(&(*raiz)->pEsq, var);

  if(result < 0)
    return adicionaVar(&(*raiz)->pDir, var);
  
  //sobrescreve o valor da variavel caso ela ja exista  
  (*raiz)->valor = *var;

  return true;
}

//busca o valor de uma variavel na pilha
bool arvoreBusca(Arvore *raiz, char *chave, Variavel *var){
  //verifica se a arvore nao existe
  if(!raiz)
    return false;

  //verifica se o no raiz eh invalido
  if(!(*raiz))
    return false;
  
  //recebe o resultado da comparacao
  int compara = strcmp((*raiz)->valor.nome, chave);
  
  //se nome eh maior que a chave, segue para a esquerda
  if(compara > 0)
    return arvoreBusca(&(*raiz)->pEsq, chave, var);
  
  //se nome eh menor que a chave, segue para a direita
  if(compara < 0)
    return arvoreBusca(&(*raiz)->pDir, chave, var);
  
  //atualiza o valor da variavel ao encontrar na arvore
  *var = (*raiz)->valor;

  return true;
}

//destroi o escopo
Arvore *destroiEscopo(Arvore *raiz){
  //verifica se o escopo eh invalido
  if(raiz == NULL)
    return NULL;
    
  //libera cada no da arvore antes de destruir a raiz
  destroiEscopoAux(raiz);

  //libera a arvore de fato
  free(raiz);

  return NULL;
}

//realiza o caminhamento pos ordem para destruir todos os filhos
void destroiEscopoAux(Arvore *raiz){  
  //se a raiz eh nula, chegou a uma posicao invalida da arvore
  if(!raiz)
    return;

  //se o conteudo da raiz eh nulo, retorna
  if(*raiz == NULL)
    return;
    
  //destroi os filhos (esquerda e direita)
  destroiEscopoAux(&(*raiz)->pEsq);
  destroiEscopoAux(&(*raiz)->pDir);
  
  //com todos os filhos destruidos, libera a memoria da arvore de fato
  free(*raiz);
}

//cria a pilha de excecucao
Pilha *criarPilha(){
  Pilha *result;
  result = (Pilha*) malloc(sizeof(Pilha));

  //caso a alocacao tenha funcionado, inicializa os valores
  if(result){
    result->topo = NULL;
    result->ultimo = NULL;
  }

  return result;
}

//adiciona um novo escopo na pilha
bool adicionaPilha(Pilha *pilha){
  //verifica se a pilha eh invalida
  if(!pilha)
    return false;
  
  //cria a nova celula
  Celula *nova = (Celula*) malloc(sizeof(Celula));
  
  //verifica se a alocacao falhou
  if(!nova)
    return false;
  
  //adiciona um escopo vazio no topo da pilha
  Arvore *raiz;
  raiz = criarEscopo();
  nova->raiz = raiz;
  nova->prox = pilha->topo;
  pilha->topo = nova;

  return true;
}

//libera a celula topo e devolve seu escopo
bool desempilha(Pilha *pilha, Arvore **raiz){
  //verifica se a pilha eh invalida
  if(!pilha)
    return false;
  
  //se o topo for invalido, retorna
  Celula *aux = pilha->topo;
  if(!aux)
    return false;

  //salva as informacoes na variavel
  *raiz = aux->raiz;
  pilha->topo = aux->prox;

  //libera o escopo
  free(aux);

  return true;
}

Arvore *getTopo(Pilha *pilha){
  if(!pilha)
    return NULL;
  if(!pilha->topo)
    return NULL;
  return pilha->topo->raiz; //devolve o escopo da celula no topo da pilha sem liberar ela
}

//busca o valor em todos os escopos da pilha
bool buscaEmEscopos(Pilha *pilha, char *chave, Variavel *var){
  //verifica se a pilha eh invalida
  if(!pilha)
    return false;

  //verifica se o topo eh invalido
  if(!pilha->topo)
    return false;

  
  //realiza a busca binaria em cada escopo anterior ao atual
  Celula *aux = pilha->topo;
  while(aux){
    if(arvoreBusca(aux->raiz, chave, var))
      return true;

    aux = aux->prox;
  }

  return false;
}

//destroi a pilha de execucao
Pilha *destroiPilha(Pilha *pilha){
  //verifica se a pilha eh invalida
  if(!pilha)
    return NULL;
  
  //destroi cada escopo da pilha
  Celula *aux, *temp;
  aux = pilha->topo;
  while(aux){
    temp = aux->prox;
    destroiEscopo((aux->raiz)); 
    free(aux);
    aux = temp;
  }

  return NULL;
}

//executa a sequencia de comandos
void executar(Pilha *pilha, Erro *erro){
  char comando[15];

  //recebe os comandos ate o scanf chegar ao final do arquivo de entrada (EOF)
  while(scanf("%s", comando) != EOF) {
    //o comando begin cria um novo escopo no topo da pilha
    if(strcmp(comando, "begin") == 0)
      adicionaPilha(pilha);

    //o comando end desemplilha o escopo do topo da pilha
    else if(strcmp(comando, "end") == 0){
      Arvore *raiz = NULL;

      //se falhar libera a pilha e retorna mensagem de erro
      if (!desempilha(pilha, &raiz)){
        erro->tipo = 1;
        strcpy(erro->mensagemErro, "Escopo nao aberto");
        destroiPilha(pilha);
        return;
      }

      //libera o escopo desempilhado
      raiz = destroiEscopo(raiz);
    }

    //o comando print procura a variavel ligada a chave passada e imprime seu valor
    else if(strcmp(comando, "print") == 0){
      Variavel var;
      char nome[MAX_NOME];

      //recebe o nome da variavel que sera printada
      scanf("%s", nome);
      
      //procura pela variavel no escopo atual e nos anteriores
      if(buscaEmEscopos(pilha, nome, &var))
        printf("%s\n", var.conteudo); //caso encontre imprime seu valor
      
      else{
        //erro de variavel nao encontrada
        erro->tipo = 2;

        //funcao para adicionar o nome da variavel na mensagem de erro
        sprintf(erro->mensagemErro, "Variavel %s nao declarada", nome);
        
        //detroi a pilha
        destroiPilha(pilha);
        
        return;
      }
    }

    //o comando var inicializa uma variavel ou atribui um novo valor caso ja tenha sido declarada no escopo
    else if(strcmp(comando, "var") == 0){
      char nome[MAX_NOME];
      char conteudo[MAX_CONTEUDO];
      char lixo[5]; //usado como filtro no scanf

      //recebe o nome e valor da variavel (mascara: "<nome> = <valor>")
      scanf("%s %s %s", nome, lixo, conteudo); 

      Variavel novaVar;
      strcpy(novaVar.nome, nome);
      strcpy(novaVar.conteudo, conteudo);

      Arvore *temp;
      temp = getTopo(pilha); //pega o escopo no topo da pilha (sem liberar a celula)

      if(temp){ //caso o escopo tenha sido inicializado
        adicionaVar(temp, &novaVar); //adiciona a variavel
      }
      else{
        erro->tipo = 1; //erro de escopo nao aberto
        strcpy(erro->mensagemErro, "Escopo nao aberto");
        destroiPilha(pilha); //libera a pilha
        return;
      }
      
    }
  }

  if(getTopo(pilha)){ //caso ainda tenha um escopo aberto no topo da pilha
    erro->tipo = 3; //erro de escopo nao fechado
    strcpy(erro->mensagemErro, "Escopo não fechado"); 
    destroiPilha(pilha);
  }

}
