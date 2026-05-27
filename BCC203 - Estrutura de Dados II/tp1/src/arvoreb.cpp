#include "../headers/arvoreb.h"

bool getPagina(FILE *arquivo, int offset, int seek, Pagina *result, int *qtdTranferencias); //Recupera página no arquivo pelo offset

void printArvoreRec(FILE *arquivo, int offset, int *qtdTransferencias);
bool pesquisaRec(FILE *arquivo, int chave, int *offset, int *index, int *qtdTransferencias, int *qtdComparacoes); 

bool inserePagina(FILE *arquivo, int offsetPag, Registro *reg, int pDireita, int *qtdTransferencias, int *qtdComparacoes); //manipula página no arquivo
bool inserePagina(Pagina* pagina, Registro *reg, int pDireita, int *qtdComparacoes); //Manipula página na memória
void ins(FILE *arquivo, Registro *reg, int offset, bool *cresceu, Registro *regRetorno, int *offsetRetorno, int *qtdTransferencias, int *qtdComparacoes);

void printArvore(FILE *arquivo, int *qtdTransferencias){
  if(arquivo && !feof(arquivo))
    printArvoreRec(arquivo, 0, qtdTransferencias);
}

void printArvoreRec(FILE *arquivo, int offset, int *qtdTransferencias){
  if(!arquivo || offset == -1)
    return;
  Pagina paginaAtual;
  getPagina(arquivo, offset, SEEK_SET, &paginaAtual, qtdTransferencias);
  int i = 0;
  while(i <= paginaAtual.n){
    printArvoreRec(arquivo, paginaAtual.p[i], qtdTransferencias);
    if(i < paginaAtual.n){
      std::cout << "  Chave: " << paginaAtual.r[i].chave << "\n";
      std::cout << "  Dado 1: " << paginaAtual.r[i].dado1 << "\n";
      std::cout << "  Dado 2: " << paginaAtual.r[i].dado2 << "\n";
      std::cout << "  Dado 3: " << paginaAtual.r[i].dado3 << "\n\n";
    }

    i++;
  }
}


bool getPagina(FILE *arquivo, int offset, int seek, Pagina *result, int *qtdTransferencias){
  //Recupera página no arquivo pelo offset
  if(!arquivo)
    return false;
  
  fseek(arquivo, offset * sizeof(Pagina), seek);
  fread(result, sizeof(Pagina), 1, arquivo);

  (*qtdTransferencias)++;

  return true;
}


bool pesquisaChave(FILE *arquivo, int chave, Registro *reg, int *qtdTransferencias, int *qtdComparacoes){
  //Chama função recursiva de pesquisa

  Pagina resultPag;
  bool encontrou = false;
  int offset = 0;
  int index;

  encontrou = pesquisaRec(arquivo, chave, &offset, &index, qtdTransferencias, qtdComparacoes);
  
  
  if(!encontrou)
    return false;
  
  getPagina(arquivo, offset, SEEK_SET, &resultPag, qtdTransferencias);
  *reg = resultPag.r[index];

  return true;
}


bool pesquisaRec(FILE *arquivo, int chave, int *offset, int *index, int *qtdTransferencias, int *qtdComparacoes){
  Pagina tempPag;

  if(feof(arquivo) || *offset == -1) //offset -1 atua como null_ptr
    return false;


  getPagina(arquivo, *offset, SEEK_SET, &tempPag, qtdTransferencias); //recupera a página atual

  int i = 1;
  while(i < tempPag.n && chave > tempPag.r[i-1].chave){ //percorre a página procurando pela chave
    (*qtdComparacoes)++;
    i++;
  } 
  
  (*qtdComparacoes)++;
  if(chave == tempPag.r[i-1].chave){
    //encontrou a chave
    *index = i-1;
    return true;
  }

  (*qtdComparacoes)++;
  if(chave < tempPag.r[i-1].chave){
    //chave possivelmente no filho da esquerda
    *offset = tempPag.p[i-1];
    return pesquisaRec(arquivo, chave, offset, index, qtdTransferencias, qtdComparacoes);
  }
  else{
    //chave possivelmente no filho da direita
    *offset = tempPag.p[i];
    return pesquisaRec(arquivo, chave, offset, index, qtdTransferencias, qtdComparacoes);
  }
  return false;
}

bool inserePagina(FILE *arquivo, int offsetPag, Registro *reg, int pDireita, int *qtdTransferencias, int *qtdComparacoes){
  Pagina tempPag;
  bool naoAchouPosicao;
  int k;
  
  //trás a página que vai ser alterada para a memória
  getPagina(arquivo, offsetPag, SEEK_SET, &tempPag, qtdTransferencias);
  

  k = tempPag.n;
  naoAchouPosicao = (k > 0);
  while (naoAchouPosicao){ 
    //procura a posição para inserir o novo registro de trás para frente no vetor
    (*qtdComparacoes)++;
    if(reg->chave >= tempPag.r[k-1].chave){
      naoAchouPosicao = false;
      break;
    }

    tempPag.r[k] = tempPag.r[k-1];
    tempPag.p[k+1] = tempPag.p[k];
    k--;

    if(k < 1)
      naoAchouPosicao = false;
  }

  if(naoAchouPosicao) //página cheia
    return false;

  tempPag.r[k] = *reg; 
  tempPag.p[k + 1] = pDireita;
  tempPag.n++;

  fseek(arquivo, offsetPag * sizeof(Pagina), SEEK_SET);
  fwrite(&tempPag, sizeof(Pagina), 1, arquivo); //sobrescreve a página antiga no arquivo

  return true;
}

bool inserePagina(Pagina* pagina, Registro *reg, int pDireita, int *qtdComparacoes){
  //insere o registro em uma página que já está na memória
  bool naoAchouPosicao;
  int k;

  k = pagina->n;
  naoAchouPosicao = (k > 0);
  while (naoAchouPosicao){
    (*qtdComparacoes)++;
    if(reg->chave >= pagina->r[k-1].chave){
      naoAchouPosicao = false;
      break;
    }

    pagina->r[k] = pagina->r[k-1];
    pagina->p[k+1] = pagina->p[k];
    k--;

    if(k < 1)
      naoAchouPosicao = false;
  }

  if(naoAchouPosicao)
    return false;

  pagina->r[k] = *reg;
  pagina->p[k + 1] = pDireita;
  pagina->n++;

  return true;
}

void ins(FILE *arquivo, Registro *reg, int offset, bool *cresceu, Registro *regRetorno, int *offsetRetorno, int *qtdTransferencias, int *qtdComparacoes){
  Pagina *pagOverflow;
  Pagina pagAtual;

  if(offset < 0){ //offset < 0 atua como null_ptr
    *cresceu = true;
    *regRetorno = *reg;
    *offsetRetorno = -1;
    return;
  }

  getPagina(arquivo, offset, SEEK_SET, &pagAtual, qtdTransferencias);

  int i = 1;
  //busca onde o registro deve ser inserido
  while (i < pagAtual.n && reg->chave > pagAtual.r[i-1].chave){
    i++;
    (*qtdComparacoes)++;
  } 
  
  (*qtdComparacoes)++;
  if(reg->chave == pagAtual.r[i-1].chave){ //encontrou um registro de mesma chave
    printf("Registro repetido\n");
    *cresceu = false;
    return;
  }
  
  (*qtdComparacoes)++;
  if(reg->chave < pagAtual.r[i-1].chave){//registro deve ser inserido na esquerda
    i--;
  } 
  ins(arquivo, reg, pagAtual.p[i], cresceu, regRetorno, offsetRetorno, qtdTransferencias, qtdComparacoes); //chamada recursiva
  if(!*cresceu) //caso de não-overflow
    return;

  getPagina(arquivo, offset, SEEK_SET, &pagAtual, qtdTransferencias); 


  if(pagAtual.n < MM){ //confere se a página tem espaço sobrando
    //chama inserePagina para sobrescrever o arquivo
    inserePagina(arquivo, offset, regRetorno, *offsetRetorno, qtdTransferencias, qtdComparacoes);
    *cresceu = false;
    return;
  }

  //else -> caso overflow, uma nova página precisa ser criada
  pagOverflow = (Pagina *) malloc(sizeof(Pagina));
  pagOverflow->n = 0;
  for(int n = 0; n < MM+1; n++)
    pagOverflow->p[n] = -1; //preenche o vetor de ponteiros com null

  if(i < M + 1){ 
    //confere se o registro deve ser inserido na página à esquerda
    inserePagina(pagOverflow, &pagAtual.r[MM-1], pagAtual.p[MM], qtdComparacoes);
    pagAtual.n--;
    inserePagina(&pagAtual, regRetorno, *offsetRetorno, qtdComparacoes);
  }
  else //o registro deve ser inserido na nova página (direita)
    inserePagina(pagOverflow, regRetorno, *offsetRetorno, qtdComparacoes);
  
  for(int j = M + 2; j <= MM; j++){
    //transporta os maiores elementos da página antiga para a nova
    inserePagina(pagOverflow, &pagAtual.r[j-1], pagAtual.p[j], qtdComparacoes);
  }

  pagAtual.n = M; //atualiza o tamanho da página antiga

  //faz o filho da esquerda da nova página ser o filho mais à direita da página antiga
  pagOverflow->p[0] = pagAtual.p[M + 1]; 

  fseek(arquivo, 0, SEEK_END); //append
  long posOverflow = ftell(arquivo);
  fwrite(pagOverflow, sizeof(Pagina), 1, arquivo); //append da nova página ao arquivo
  
  fseek(arquivo, offset * sizeof(Pagina), SEEK_SET);
  fwrite(&pagAtual, sizeof(Pagina), 1, arquivo); //atualiza a página antiga dentro do arquivo
  

  *regRetorno = pagAtual.r[M]; //registro que deve subir
  *offsetRetorno = posOverflow / sizeof(Pagina); //posição da nova página no arquivo

  free(pagOverflow);
}

void insereNaArvore(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes) {
  // inicia os valores de inserção
  int offset = 0;
  bool cresceu = false;
  Registro regRetorno;
  int offsetRetorno;
  fseek(arq, 0, SEEK_SET);
  
  // chama a função de inserção
  ins(arq, reg, offset, &cresceu, &regRetorno, &offsetRetorno, qtdTransferencias, qtdComparacoes);

  // Se a flag 'cresceu' retornar verdadeira, a raiz sofreu split e a árvore precisa crescer
  if (cresceu) {
    Pagina paginaEsquerda;
    
    // 1. Lê a raiz antiga (que agora contém apenas a metade esquerda após o split)
    getPagina(arq, 0, SEEK_SET, &paginaEsquerda, qtdTransferencias);

    // 2. Move a página esquerda para o final do arquivo
    fseek(arq, 0, SEEK_END);
    int offsetEsquerda = ftell(arq) / sizeof(Pagina);
    fwrite(&paginaEsquerda, sizeof(Pagina), 1, arq);

    // 3. Cria a nova raiz
    Pagina novaRaiz;
    novaRaiz.n = 1;
    novaRaiz.r[0] = regRetorno; // Recebe a chave promovida
    
    for (int i = 0; i < MM + 1; i++) {
      novaRaiz.p[i] = -1;
    }
    
    novaRaiz.p[0] = offsetEsquerda;   // Ponteiro esquerdo aponta para a antiga raiz realocada
    novaRaiz.p[1] = offsetRetorno;   // Ponteiro direito aponta para a página de overflow
    
    // 4. Sobrescreve o offset 0 (início do arquivo) com a nova raiz
    fseek(arq, 0, SEEK_SET);
    fwrite(&novaRaiz, sizeof(Pagina), 1, arq);
  }
}
