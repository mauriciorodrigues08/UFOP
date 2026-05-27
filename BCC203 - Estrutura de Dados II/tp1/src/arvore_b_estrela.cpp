#include "../headers/arvore_b_estrela.h"

void printArvoreEstrelaRec(FILE *arquivo, int offset, int *qtdTransferencias);
bool pesquisaRecEstrela(FILE *arquivo, int chave, int *offset, int *index, int *qtdTransferencias, int *qtdComparacoes);
bool getPaginaEstrela(FILE *arquivo, int offset, int seek, PaginaEstrela *result, int *qtdTransferencias);

bool getPaginaEstrela(FILE *arquivo, int offset, int seek, PaginaEstrela *result, int *qtdTransferencias){
  //Recupera página no arquivo pelo offset
  if(!arquivo)
    return false;
  
  fseek(arquivo, offset * sizeof(PaginaEstrela), seek);
  fread(result, sizeof(PaginaEstrela), 1, arquivo);

  (*qtdTransferencias)++;

  return true;
}

bool pesquisarChaveB_estrela(FILE *arquivo, int chave, Registro *reg, int *qtdTransferencias, int *qtdComparacoes){
  PaginaEstrela resultPag;
  bool encontrou = false;
  int offset = 0;
  int index;

  encontrou = pesquisaRecEstrela(arquivo, chave, &offset, &index, qtdTransferencias, qtdComparacoes);

  if(!encontrou)
    return false;
  
  getPaginaEstrela(arquivo, offset, SEEK_SET, &resultPag, qtdTransferencias);
  *reg = resultPag.UU.paginaExterna.r[index];

  return true;

}

bool pesquisaRecEstrela(FILE *arquivo, int chave, int *offset, int *index, int *qtdTransferencias, int *qtdComparacoes){
  PaginaEstrela tempPagina;
  getPaginaEstrela(arquivo, *offset, SEEK_SET, &tempPagina, qtdTransferencias);

  if(tempPagina.tipoDePagina == interna){
    int i = 1;
    while(i < tempPagina.UU.paginaInterna.n && chave > tempPagina.UU.paginaInterna.ri[i-1]){
      (*qtdComparacoes)++;
      i++;
    }
    
    (*qtdComparacoes)++;
    if(chave < tempPagina.UU.paginaInterna.ri[i-1]){
      *offset = tempPagina.UU.paginaInterna.p[i-1];
      return pesquisaRecEstrela(arquivo, chave, offset, index, qtdTransferencias, qtdComparacoes);
    }
    else{
      *offset = tempPagina.UU.paginaInterna.p[i];
      return pesquisaRecEstrela(arquivo, chave, offset, index, qtdTransferencias, qtdComparacoes);
    }
  }

  else{
    int i = 1;
    while(i < tempPagina.UU.paginaExterna.n && chave > tempPagina.UU.paginaExterna.r[i-1].chave){
      (*qtdComparacoes)++;
      i++;
    }
    (*qtdComparacoes)++;
    if(chave == tempPagina.UU.paginaExterna.r[i-1].chave){
      *index = i-1;
      return true;
    }
    return false;
  }
  return false;
}



bool inserePaginaExterna(PaginaEstrela* pagina, Registro *reg, int *qtdComparacoes) {
  int k = pagina->UU.paginaExterna.n;
  bool naoAchouPosicao = (k > 0);
  
  while (naoAchouPosicao) {
    (*qtdComparacoes)++;
    if (reg->chave >= pagina->UU.paginaExterna.r[k-1].chave) {
      naoAchouPosicao = false;
      break;
    }
    pagina->UU.paginaExterna.r[k] = pagina->UU.paginaExterna.r[k-1];
    k--;
    if (k < 1) naoAchouPosicao = false;
  }
  
  pagina->UU.paginaExterna.r[k] = *reg;
  pagina->UU.paginaExterna.n++;
  return true;
}

bool inserePaginaInterna(PaginaEstrela* pagina, int chave, int pDireita, int *qtdComparacoes) {
  int k = pagina->UU.paginaInterna.n;
  bool naoAchouPosicao = (k > 0);
  
  while (naoAchouPosicao) {
    (*qtdComparacoes)++;
    if (chave >= pagina->UU.paginaInterna.ri[k-1]) {
      naoAchouPosicao = false;
      break;
    }
    pagina->UU.paginaInterna.ri[k] = pagina->UU.paginaInterna.ri[k-1];
    pagina->UU.paginaInterna.p[k+1] = pagina->UU.paginaInterna.p[k];
    k--;
    if (k < 1) naoAchouPosicao = false;
  }
  
  pagina->UU.paginaInterna.ri[k] = chave;
  pagina->UU.paginaInterna.p[k+1] = pDireita;
  pagina->UU.paginaInterna.n++;
  return true;
}

void insRecEstrela(FILE *arquivo, Registro *reg, int offset, bool *cresceu, int *chaveRetorno, int *offsetRetorno, int *qtdTransferencias, int *qtdComparacoes) {
  PaginaEstrela pagAtual;
  getPaginaEstrela(arquivo, offset, SEEK_SET, &pagAtual, qtdTransferencias);

  //pesquisa por onde descer na pagina interna
  if (pagAtual.tipoDePagina == interna) {
    int i = 1;
    while (i < pagAtual.UU.paginaInterna.n && reg->chave > pagAtual.UU.paginaInterna.ri[i-1]) {
      i++;
      (*qtdComparacoes)++;
    }
    (*qtdComparacoes)++;
    if (reg->chave < pagAtual.UU.paginaInterna.ri[i-1]) {
      i--;
    }

    insRecEstrela(arquivo, reg, pagAtual.UU.paginaInterna.p[i], cresceu, chaveRetorno, offsetRetorno, qtdTransferencias, qtdComparacoes);

    if (!*cresceu) return; // Sem overflow no filho

    // Tem espaço na página interna
    if (pagAtual.UU.paginaInterna.n < MM) {
      inserePaginaInterna(&pagAtual, *chaveRetorno, *offsetRetorno, qtdComparacoes);
      fseek(arquivo, offset * sizeof(PaginaEstrela), SEEK_SET);
      fwrite(&pagAtual, sizeof(PaginaEstrela), 1, arquivo);
      (*qtdTransferencias)++;
      *cresceu = false;
      return;
    }
    PaginaEstrela pagOverflow;
    pagOverflow.tipoDePagina = interna;
    pagOverflow.UU.paginaInterna.n = 0;

    int tempChaves[MM + 1];
    int tempP[MM + 2];
    //preenche as variaveis temporarias
    for (int j = 0; j < MM; j++) tempChaves[j] = pagAtual.UU.paginaInterna.ri[j];
    for (int j = 0; j < MM + 1; j++) tempP[j] = pagAtual.UU.paginaInterna.p[j];

    //encontra o meio do vetor
    int k = MM;
    while (k > 0 && *chaveRetorno < tempChaves[k-1]) {
      tempChaves[k] = tempChaves[k-1];
      tempP[k+1] = tempP[k];
      k--;
    }
    tempChaves[k] = *chaveRetorno;
    tempP[k+1] = *offsetRetorno;

    pagAtual.UU.paginaInterna.n = M;
    pagOverflow.UU.paginaInterna.n = M;

    for (int j = 0; j < M; j++) {
      //atualizando a pagina antiga
      pagAtual.UU.paginaInterna.ri[j] = tempChaves[j];
      pagAtual.UU.paginaInterna.p[j] = tempP[j];
    }
    pagAtual.UU.paginaInterna.p[M] = tempP[M];

    *chaveRetorno = tempChaves[M]; // Chave do meio sobe

    for (int j = 0; j < M; j++) {
      //preenche a nova pagina
      pagOverflow.UU.paginaInterna.ri[j] = tempChaves[M + 1 + j];
      pagOverflow.UU.paginaInterna.p[j] = tempP[M + 1 + j];
    }
    pagOverflow.UU.paginaInterna.p[M] = tempP[MM + 1];

    //append a nova pagina
    fseek(arquivo, 0, SEEK_END);
    long posOverflow = ftell(arquivo);
    fwrite(&pagOverflow, sizeof(PaginaEstrela), 1, arquivo);
    (*qtdTransferencias)++;

    //atualiza a pagina antiga no arquivo
    fseek(arquivo, offset * sizeof(PaginaEstrela), SEEK_SET);
    fwrite(&pagAtual, sizeof(PaginaEstrela), 1, arquivo);
    (*qtdTransferencias)++;

    *offsetRetorno = posOverflow / sizeof(PaginaEstrela);
    return;

  } else { // tipoDePagina == externa
    int i = 1;
    while (i <= pagAtual.UU.paginaExterna.n && reg->chave > pagAtual.UU.paginaExterna.r[i-1].chave) {
      //pesquisa onde inserir na pagina externa
      i++;
      (*qtdComparacoes)++;
    }
    (*qtdComparacoes)++;
    if (i <= pagAtual.UU.paginaExterna.n && reg->chave == pagAtual.UU.paginaExterna.r[i-1].chave) {
      printf("Registro repetido\n");
      *cresceu = false;
      return;
    }

    // Tem espaço na página externa
    if (pagAtual.UU.paginaExterna.n < MM) {
      inserePaginaExterna(&pagAtual, reg, qtdComparacoes);
      fseek(arquivo, offset * sizeof(PaginaEstrela), SEEK_SET);
      fwrite(&pagAtual, sizeof(PaginaEstrela), 1, arquivo);
      (*qtdTransferencias)++;
      *cresceu = false;
      return;
    }

    PaginaEstrela pagOverflow;
    pagOverflow.tipoDePagina = externa;
    pagOverflow.UU.paginaExterna.n = 0;

    //preenche o vetor temporario
    Registro tempRegs[MM + 1];
    for (int j = 0; j < MM; j++) tempRegs[j] = pagAtual.UU.paginaExterna.r[j];

    int k = MM;
    while (k > 0 && reg->chave < tempRegs[k-1].chave) {
      tempRegs[k] = tempRegs[k-1];
      k--;
    }
    tempRegs[k] = *reg;

    pagAtual.UU.paginaExterna.n = M;
    pagOverflow.UU.paginaExterna.n = M + 1;

    for (int j = 0; j < M; j++) {
      pagAtual.UU.paginaExterna.r[j] = tempRegs[j];
    }
    for (int j = 0; j < M + 1; j++) {
      pagOverflow.UU.paginaExterna.r[j] = tempRegs[M + j];
    }

    // Copia a primeira chave da nova folha para subir ao pai
    *chaveRetorno = pagOverflow.UU.paginaExterna.r[0].chave; 

    fseek(arquivo, 0, SEEK_END);
    long posOverflow = ftell(arquivo);
    fwrite(&pagOverflow, sizeof(PaginaEstrela), 1, arquivo);
    (*qtdTransferencias)++;

    fseek(arquivo, offset * sizeof(PaginaEstrela), SEEK_SET);
    fwrite(&pagAtual, sizeof(PaginaEstrela), 1, arquivo);
    (*qtdTransferencias)++;

    *offsetRetorno = posOverflow / sizeof(PaginaEstrela);
    *cresceu = true;
    return;
  }
}

void insereArvoreB_estrela(FILE *arq, Registro *reg, int *qtdTransferencias, int *qtdComparacoes) {
  bool cresceu = false;
  int chaveRetorno;
  int offsetRetorno;

  // Verifica se o arquivo está vazio para criar a primeira raiz (sempre externa)
  fseek(arq, 0, SEEK_END);
  if (ftell(arq) == 0) {
    PaginaEstrela novaRaizExterna;
    novaRaizExterna.tipoDePagina = externa;
    novaRaizExterna.UU.paginaExterna.n = 1;
    novaRaizExterna.UU.paginaExterna.r[0] = *reg;
    
    fseek(arq, 0, SEEK_SET);
    fwrite(&novaRaizExterna, sizeof(PaginaEstrela), 1, arq);
    (*qtdTransferencias)++;
    return;
  }

  insRecEstrela(arq, reg, 0, &cresceu, &chaveRetorno, &offsetRetorno, qtdTransferencias, qtdComparacoes);

  if (cresceu) {
    PaginaEstrela raizAntiga;
    getPaginaEstrela(arq, 0, SEEK_SET, &raizAntiga, qtdTransferencias);

    fseek(arq, 0, SEEK_END);
    int offsetAntigaRaiz = ftell(arq) / sizeof(PaginaEstrela);
    fwrite(&raizAntiga, sizeof(PaginaEstrela), 1, arq);
    (*qtdTransferencias)++;

    PaginaEstrela novaRaiz;
    novaRaiz.tipoDePagina = interna;
    novaRaiz.UU.paginaInterna.n = 1;
    novaRaiz.UU.paginaInterna.ri[0] = chaveRetorno;
    
    for (int i = 0; i < MM + 1; i++) {
      novaRaiz.UU.paginaInterna.p[i] = -1;
    }
    
    novaRaiz.UU.paginaInterna.p[0] = offsetAntigaRaiz;
    novaRaiz.UU.paginaInterna.p[1] = offsetRetorno;

    fseek(arq, 0, SEEK_SET);
    fwrite(&novaRaiz, sizeof(PaginaEstrela), 1, arq);
    (*qtdTransferencias)++;
  }
}

void printArvoreB_estrela(FILE *arquivo, int *qtdTransferencias){
  if(arquivo && !feof(arquivo))
    printArvoreEstrelaRec(arquivo, 0, qtdTransferencias);
}

void printArvoreEstrelaRec(FILE *arquivo, int offset, int *qtdTransferencias){
  if(!arquivo || offset == -1)
    return;
  PaginaEstrela paginaAtual;
  getPaginaEstrela(arquivo, offset, SEEK_SET, &paginaAtual, qtdTransferencias);
  int i = 0;
  if(paginaAtual.tipoDePagina == externa){
     while(i < paginaAtual.UU.paginaExterna.n){
      std::cout << "  Chave: " << paginaAtual.UU.paginaExterna.r[i].chave << "\n";
      std::cout << "  Dado 1: " << paginaAtual.UU.paginaExterna.r[i].dado1 << "\n";
      std::cout << "  Dado 2: " << paginaAtual.UU.paginaExterna.r[i].dado2 << "\n";
      std::cout << "  Dado 3: " << paginaAtual.UU.paginaExterna.r[i].dado3 << "\n\n";
      i++;
    }
  }

  else{
    for(int i = 0; i <= paginaAtual.UU.paginaInterna.n; i++)
      printArvoreEstrelaRec(arquivo, paginaAtual.UU.paginaInterna.p[i], qtdTransferencias);
  }
 
}
