//imports
#include <stdio.h>
#include <stdlib.h>

//modulos
#include "fila.h"

//defines
#define MAX_CICLOS 100

//structs
struct celula {
  Processo conteudo;
  struct celula *prox;
};

struct fila {
  Celula *topo;
  Celula *ultimo;
  bool foiOrdenada;
};

//declaracao de funcoes locais
void sort(FilaProcessos *pFila);
FilaProcessos *insertionSort(FilaProcessos *pFila);
Celula *mergeSort(Celula *pTopo);
Celula *merge(Celula *p1, Celula *p2);
int comparaProcessos(Processo *p1, Processo *p2, bool verificador);
void executa(Processo *p);


//funcao para criar e inicializar uma fila de procesos
FilaProcessos* criarFila(Processo *processos, int n) {
  //aloca a fila
  FilaProcessos *fila = (FilaProcessos*) malloc(sizeof(FilaProcessos));
  
  //verifica se a alocacao falhou
  if (!fila)
    return NULL;

  //cria primeira posicao
  fila->topo = (Celula *) malloc(sizeof(Celula));
  fila->foiOrdenada = false;
  
  //inicializa o conteudo da primeira posicao
  fila->topo->conteudo = processos[0];
  fila->topo->prox = NULL;
  fila->ultimo = fila->topo;

  //auxiliar que aponta para a ultima celula modificada
  Celula *aux = fila->topo;

  //inicializa os valores passados no vetor auxiliar
  for (int i=1; i<n; i++) {
    //cria a nova celula e inicializa seu conteudo
    Celula *nova = (Celula *) malloc(sizeof(Celula));
    nova->conteudo = processos[i];

    //prox da ultima celula adicionada passa a ser a nova
    aux->prox = nova;  
    aux = nova;  

    //atualiza ponteiro pra ultima posicao
    fila->ultimo = nova;
  }

  //ordenacao inicial
  sort(fila);
  fila->foiOrdenada = true;

  //retorna a fila
  return fila;
}

//funcao para destuir uma fila de processos
FilaProcessos* destroiFila(FilaProcessos *pFila) {
  //verifica se a fila nao existe
  if (!pFila)
    return NULL;

  //destroi todos os processos um a um
  Celula *aux = pFila->topo;

  while(aux) {
    Celula *prox = aux->prox;
    free(aux);
    aux = prox;
  }

  //libera a fila de fato
  free(pFila);

  return NULL;
}

//funcao para adicionar e ordenar um novo item na fila
bool adicionaFila(FilaProcessos *pFila, Processo *novoProcesso) {
  //verifica se a fila nao existe
  if(!pFila)
    return false;

  //aloca o novo processo
  Celula *novo = (Celula*) malloc(sizeof(Celula));
  if (!novo) //verifica falha de alocacao
    return false;

  //adiciona o conteudo ao novo processo
  novo->conteudo = *novoProcesso;
  
  //adiciona o novo processo no final da fila
  pFila->ultimo->prox = novo; //antigo ultimo processo agora tem um prox
  pFila->ultimo = novo; //novo processo passa a ser o ultimo

  //ordenacao da fila
  sort(pFila);
  
  return true;
}

//funcao que atende os pedidos e analisa se o maximo de ciclos foi excedido para cada processo
void escalonador(FilaProcessos *pFila) {
  //verifica se a fila nao existe
  if (!pFila)
    return;
    
  //reorganiza os processos, respeitando o limite maximo de ciclos
  Celula *aux = pFila->topo;  
  while (aux) {
    //se o processo atual demorar mais de 100 ciclos, o valor de seus ciclos passa a ser MAX_CICLOS (100)
    //adiciona a sobra novamente na fila com prioridade incrementada em 1
    if (aux->conteudo.ciclos > MAX_CICLOS) {

      Processo tempProcesso = aux->conteudo;
      tempProcesso.ciclos -= MAX_CICLOS;
      tempProcesso.prioridade += 1;

      adicionaFila(pFila, &tempProcesso);
      aux->conteudo.ciclos = MAX_CICLOS;
    }

    aux = aux->prox;
  }

  //Funcao para simular execucao de cada log:
  aux = pFila->topo;
  while(aux){
    executa(&aux->conteudo);
    aux = aux->prox;
  }


  return;  
}

void imprimeLog(FilaProcessos *pFila) {
  //verifica se fila nao existe
  if (!pFila)
    return;

  printf("Log CPU:\n");
  
  //imprime os valores
  Celula *aux = pFila->topo;
  while(aux) {
    printf("%d %d %d\n", aux->conteudo.id, aux->conteudo.prioridade, aux->conteudo.ciclos);
    aux = aux->prox;
  }

  return;
}

void sort(FilaProcessos *pFila) {
  if(!pFila->foiOrdenada){ //merge sort para a primeira ordenacao
    pFila->topo = mergeSort(pFila->topo);
  }
  else{ //insertion sort para as demais
    pFila = insertionSort(pFila);
  }
  
  //atualiza o ultimo
  Celula *cauda = pFila->topo;
  while (cauda->prox) {
    cauda = cauda->prox;
  }
  pFila->ultimo = cauda;
    
}

FilaProcessos *insertionSort(FilaProcessos *pFila){
  //verifica se a fila tem apenas 1 elemento
    if(pFila->topo == pFila->ultimo)
      return pFila;

  //salva o novo processo em uma variavel separada
  Celula *novo = pFila->ultimo;
  
  //encontra a penultima posicao (que vai passar a ser a ultima)
  Celula *penultimo = pFila->topo;
  
  while (penultimo && penultimo->prox != novo) {
    penultimo = penultimo->prox;
  }
  
  //penultimo passa a ser o ultimo
  penultimo->prox = NULL;
  pFila->ultimo = penultimo;

  //verifica se novo vai entrar na primeira posicao (topo)
  if (comparaProcessos(&(novo->conteudo), &(pFila->topo->conteudo), false) == 1) {
    novo->prox = pFila->topo;
    pFila->topo = novo;
  }
  else {
    //encontra a posicao correta para novo (desconsiderando o tempo)
    Celula *aux = pFila->topo;

    while (aux->prox && comparaProcessos(&(aux->prox->conteudo), &(novo->conteudo), false) != 2) {
      aux = aux->prox;
    }

    //insere novo apos aux
    novo->prox = aux->prox;
    aux->prox = novo;
  }

  return pFila;
}

Celula *mergeSort(Celula *pTopo){
  //Caso base: ultima Celula da fila
  if(!pTopo)
    return NULL;
  if(!pTopo->prox)
    return pTopo;

  Celula *l = pTopo; //primeiro elemento da sub lista
  Celula *r = pTopo->prox; //segundo elemento da sub lista

  while(r && r->prox){
    //move r ate o ultimo elemento
    r = r->prox->prox;
    //move l ate o elemento do meio
    l = l->prox;
  }

  Celula *meio = l->prox; 
  l->prox = NULL; //Coloca um fim na lista

  Celula *esquerda = mergeSort(pTopo);//passo recursivo para subdividir a lista do primeiro ate o meio
  Celula *direita = mergeSort(meio);//passo recursivo para subdividir a lista do meio ate o final

  return merge(esquerda, direita); //merge nas listas
}

Celula *merge(Celula *p1, Celula *p2){
  //Caso base: algum dos ponteiros eh nulo
  if(!p1)
    return p2;
  if(!p2)
    return p1;

  int comparacao = comparaProcessos(&(p1->conteudo), &(p2->conteudo), true);  
  if(comparacao == 0 || comparacao == 1 || comparacao == 3){ //caso sejam iguais ou p1 tenha maior prioridade ou menor tempo
    p1->prox = merge(p1->prox, p2); //passo recursivo
    return p1;
  }
  else{ //caso p2 tenha maior prioridade ou menor tempo
    p2->prox = merge(p1, p2->prox); //passo recursivo
    return p2;
  }
}

//funcao que compara a prioridade de dois processos
int comparaProcessos(Processo *p1, Processo *p2, bool verificador) {
  //processos iguais -> retorna 0
  //primeiro eh maior por prioridade -> retorna 1
  //segundo eh maior por prioridade -> retorna 2
  //primeiro eh maior por tempo -> retorna 3
  //segundo eh maior por tempo -> retorna 4
  //se o verificador eh verdadeiro, o tempo eh levado em consideracao

  if (p1->prioridade < p2->prioridade)
    return 1;
  
  if (p1->prioridade > p2->prioridade)
    return 2;

  if ( (p1->tempo < p2->tempo) && verificador)
    return 3;

  if ( (p1->tempo > p2->tempo) && verificador)
    return 4;

  return 0;
}

void executa(Processo *p){
  for(int i = 0; i < p->ciclos; i++){
    //loop vazio representando execucao de um processo
  }
}