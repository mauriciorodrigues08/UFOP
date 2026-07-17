#include "include/Func.h"

double distanciaEntreDoisPontos(Ponto a, Ponto b){
  return sqrt( pow((b.x - a.x), 2) + pow((b.y - a.y), 2) );
}

double distanciaPontoSegmento(Ponto p, Segmento s){
  //algoritmo para determinar distâncida entre um potno e segmento
  double dx = s.b.x - s.a.x;
  double dy = s.b.y - s.a.y;
  double len2 = dx*dx + dy*dy;

  if(len2 < 1e-12) //segmento pequeno demais
      return distanciaEntreDoisPontos(p, s.a);

  //t = (P-A)·(B-A) / ||B-A||²
  double t = ((p.x - s.a.x)*dx + (p.y - s.a.y)*dy) / len2;

  if(t < 0.0) // ponto mais próximo é A
    t = 0.0;   
  if(t > 1.0) // ponto mais próximo é B
    t = 1.0;   

  Ponto projecao(s.a.x + t*dx, s.a.y + t*dy); 
  //calcula a distância entre o ponto dado e seu ponto mais próximo no segmento
  return distanciaEntreDoisPontos(p, projecao);
}

double orientacao(Ponto a, Ponto b, Ponto c){
  return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
  //return > 0 ->  curva a esquerda
  //return < 0 -> curva a direita
  //return = 0 -> mesma reta
}

bool intersecaoSegmentos(Segmento a, Segmento b){
  Ponto pA, pB, pC, pD;
  pA = a.a;
  pB = a.b;
  pC = b.a;
  pD = b.b;

  double o1 = orientacao(pA, pB, pC); //orient (A, B, C);
  double o2 = orientacao(pA, pB, pD); //orient (A, B, D);
  double o3 = orientacao(pC, pD, pA); //orient (C, D, A);
  double o4 = orientacao(pC, pD, pB); //orient (C, D, B);
  return ( o1 * o2 < 0.0) && ( o3 * o4 < 0.0);
}


double distancia(Ponto a, Ponto b){
  return distanciaEntreDoisPontos(a, b);
}

double calculaComprimento(No *seg){
  //comprimento do segmento entre "seg" e seu pai (a raiz não tem segmento)
  if(seg == nullptr || seg->pai == nullptr)
    return 0.0;
  return distancia(seg->p, seg->pai->p);
}

double calculaResistencia(double mu, double comprimento, double raio){
  //Lei de Poiseuille: R = 8*mu*l / (pi*r^4)
  if(raio <= 0.0)
    return 0.0;
  return (8.0 * mu * comprimento) / (M_PI * pow(raio, 4));
}

double calculaVolume(double comprimento, double raio){
  //volume de um segmento cilíndrico: V = pi*r^2*l
  return M_PI * raio * raio * comprimento;
}

double calculaVolumeTotal(No *raiz){
  if(raiz == nullptr)
    return 0.0;

  double total = 0.0;
  if(raiz->pai != nullptr) //a raiz não representa um segmento
    total += raiz->volume;

  total += calculaVolumeTotal(raiz->esq);
  total += calculaVolumeTotal(raiz->dir);
  return total;
}

int atualizaQtdTerminaisDistais(No *no){
  //percorre a árvore em pós-ordem, contando terminais distais a cada nó
  if(no == nullptr)
    return 0;

  if(no->esq == nullptr && no->dir == nullptr){
    no->qtdTermDistal = 1;
    return 1;
  }

  int qtdEsq = atualizaQtdTerminaisDistais(no->esq);
  int qtdDir = atualizaQtdTerminaisDistais(no->dir);

  no->qtdTermDistal = qtdEsq + qtdDir;
  return no->qtdTermDistal;
}

void atualizaFluxos(No *no, double Qterm){
  //fluxo proporcional a quantidade de terminais distais (fluxos terminais iguais)
  if(no == nullptr)
    return;

  no->fluxo = no->qtdTermDistal * Qterm;

  atualizaFluxos(no->esq, Qterm);
  atualizaFluxos(no->dir, Qterm);
}

void atualizaComprimentos(No *no){
  if(no == nullptr)
    return;
  no->comprimento = calculaComprimento(no);
  atualizaComprimentos(no->esq);
  atualizaComprimentos(no->dir);
}

void atualizaResistencias(No *no, double mu){
  if(no == nullptr)
    return;
  no->resistencia = (no->pai != nullptr) ? calculaResistencia(mu, no->comprimento, no->raio) : 0.0;
  atualizaResistencias(no->esq, mu);
  atualizaResistencias(no->dir, mu);
}

void atualizaVolumes(No *no){
  if(no == nullptr)
    return;
  no->volume = (no->pai != nullptr) ? calculaVolume(no->comprimento, no->raio) : 0.0;
  atualizaVolumes(no->esq);
  atualizaVolumes(no->dir);
}

void atualizaRaiosBrutosRec(No *no, double gamma){
  //raio bruto: rj = C * Qj^(1/gamma), com C = 1
  if(no == nullptr)
    return;
  no->raio = (no->pai != nullptr) ? pow(no->fluxo, 1.0 / gamma) : 0.0;
  atualizaRaiosBrutosRec(no->esq, gamma);
  atualizaRaiosBrutosRec(no->dir, gamma);
}

void escalaRaiosRec(No *no, double escala){
  if(no == nullptr)
    return;
  no->raio *= escala;
  escalaRaiosRec(no->esq, escala);
  escalaRaiosRec(no->dir, escala);
}

void atualizaRaiosPorFluxo(No *no, double gamma){
  atualizaRaiosBrutosRec(no, gamma);

  //normaliza pelo raio do tronco (segmento raiz->esq, que carrega o fluxo total)
  if(no != nullptr && no->esq != nullptr && no->esq->raio > 1e-15){
    double escala = 1.0 / no->esq->raio;
    escalaRaiosRec(no, escala);
  }
}

void atualizaGeometriaFisica(No *raiz, double Qterm, double gamma, double mu){
  atualizaComprimentos(raiz);
  atualizaQtdTerminaisDistais(raiz);
  atualizaFluxos(raiz, Qterm);
  atualizaRaiosPorFluxo(raiz, gamma);
  atualizaResistencias(raiz, mu);
  atualizaVolumes(raiz);
}

double funcaoCustoVolume(No *raiz){
  //função custo: volume intravascular total da árvore
  return calculaVolumeTotal(raiz);
}

Ponto pontoBaricentrico(Ponto A, Ponto B, Ponto C, double alpha, double beta, double lambda){
  return Ponto(alpha * A.x + beta * B.x + lambda * C.x,
               alpha * A.y + beta * B.y + lambda * C.y);
}

int pontoDentroTriangulo(Ponto A, Ponto B, Ponto C, Ponto P){
  double d1 = orientacao(P, A, B);
  double d2 = orientacao(P, B, C);
  double d3 = orientacao(P, C, A);

  bool temNegativo = (d1 < 0) || (d2 < 0) || (d3 < 0);
  bool temPositivo = (d1 > 0) || (d2 > 0) || (d3 > 0);

  return (!(temNegativo && temPositivo)) ? 1 : 0; //1 = dentro (ou na borda)
}

bool intersectaComArvore(No *raiz, Segmento segsNovos[3], No *ignorar1, No *ignorar2, No *ignorar3){
  //testa os 3 segmentos novos contra a árvore, ignorando os segmentos que compartilham extremidade com eles
  if(raiz == nullptr)
    return false;

  if(raiz->pai != nullptr && raiz != ignorar1 && raiz != ignorar2 && raiz != ignorar3){
    Segmento segExistente(raiz->pai->p, raiz->p);
    for(int k = 0; k < 3; k++){
      if(intersecaoSegmentos(segExistente, segsNovos[k]))
        return true;
    }
  }

  if(intersectaComArvore(raiz->esq, segsNovos, ignorar1, ignorar2, ignorar3))
    return true;
  return intersectaComArvore(raiz->dir, segsNovos, ignorar1, ignorar2, ignorar3);
}

Ponto otimizaBifurcacaoPorGrade(No *raizArvore, No *novaBifurcacao, No *alvo, No *novoTerminal,
                                 Ponto A, Ponto B, Ponto C, int M,
                                 double Qterm, double gamma, double mu,
                                 double *melhorCusto){
  //busca exaustiva em grade dentro do triângulo ABC (coordenadas baricêntricas)
  //pré-condição: novaBifurcacao já está inserida temporariamente entre alvo->pai e alvo,
  //com novoTerminal como seu outro filho

  bool encontrado = false;
  double custoAtual;
  Ponto melhorX;
  No *paiAlvo = alvo->pai;

  for(int i = 0; i <= M; i++){
    for(int j = 0; j <= M - i; j++){
      double alpha = i / (double)M;
      double beta  = j / (double)M;
      double lambda = 1.0 - alpha - beta;

      Ponto X = pontoBaricentrico(A, B, C, alpha, beta, lambda);
      novaBifurcacao->p = X;

      Segmento segsNovos[3] = {
        Segmento(paiAlvo->p, X),
        Segmento(X, B),
        Segmento(X, C)
      };

      bool valido = !intersectaComArvore(raizArvore, segsNovos, novaBifurcacao, alvo, novoTerminal);

      if(valido){
        atualizaGeometriaFisica(raizArvore, Qterm, gamma, mu);
        custoAtual = funcaoCustoVolume(raizArvore);

        if(!encontrado || custoAtual < *melhorCusto){
          encontrado = true;
          *melhorCusto = custoAtual;
          melhorX = X;
        }
      }
    }
  }

  if(!encontrado)
    *melhorCusto = -1.0; //nenhuma posição candidata foi válida

  return melhorX;
}