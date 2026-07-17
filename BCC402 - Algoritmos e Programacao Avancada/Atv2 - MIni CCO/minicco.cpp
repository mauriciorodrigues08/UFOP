#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <ctime>
#include <chrono>

#include "include/Arvore.h"
#include "include/Dominio.h"
#include "include/Func.h"
#include "include/Ponto.h"
#include "include/Segmento.h"

//valor pelo qual epsilon será multiplicado após várias iterações sem sucesso
#define DECREMENTO_EPSILON 0.9

//parâmetros físicos sugeridos no enunciado
#define QPERF 8.33e-6  //fluxo total de perfusão (m^3/s)
#define PPERF 1.33e4   //pressão de perfusão (Pa)
#define PTERM 7.98e3   //pressão terminal (Pa)
#define MU    3.6e-3   //viscosidade sanguínea (Pa.s)

typedef struct Candidato{
    //struct de um candidato para facilitar a organização

    Ponto pCandidato; //ponto médio do segmento que desejamos conectar
    No *noAlvo; //nó onde o segmento termina (Seu ponteiro *pai aponta para o inicio do segmento)
    double custo; //custo euclidiano estimado, usado apenas para ordenar a tentativa de conexão
}Candidato;

double determinarEpsilon(double raio, int numTerminais);
double custoEuclidiano(Ponto a, Ponto b);
void elegeCandidatos(std::vector<Candidato>& candidatos, No *raiz, Ponto& pNovo);
bool respeitaDistanciaMinima(No *raiz, Ponto &pNovo, double epsilon);
void escreveArvoreCSV(std::ofstream& arq, No *raiz);
void somaRaios(No *raiz, double &soma, int &contagem);
double calculaComprimentoTotal(No *raiz);


int main(int argc, char *argv[]) {
    if(argc < 5){
        std::cout << "Uso: ./minicco <N_terminais> <Raio> <gamma> <M>\n";
        return 1;
    }

    srand(time(NULL));

    int numTerminais = atoi(argv[1]);
    double raio      = atof(argv[2]);
    double gamma     = atof(argv[3]);
    int M            = atoi(argv[4]);

    if(numTerminais < 2 || raio <= 0.0 || gamma <= 0.0 || M < 1){
        std::cout << "Parâmetros inválidos.\n";
        return 1;
    }

    Dominio dominio(raio);
    double Qterm = QPERF / (double)numTerminais; //fluxo terminal, assumindo terminais iguais

    auto tInicio = std::chrono::high_resolution_clock::now();

    int conexoesTestadas = 0;
    int conexoesRejeitadas = 0;
    int idCounter = 0; //Chave dos nós criados

    //cria raiz fixada na borda do dominio
    No* raiz = new No(Ponto(0.0, raio), idCounter++);

    //cria o primeiro nó em um ponto fixo para garantir sua distância da raiz
    double x = -raio/10.0;
    double y = -(0.80 * raio);
    Ponto pInicial(x, y);
    No* noInicial = new No(pInicial, idCounter++);
    noInicial->pai = raiz;
    raiz->esq = noInicial;

    int iterCounter = 0;
    double epsilon; //distância mínima de um ponto gerado aos segmentos existentes

    for(int i = 1; i < numTerminais; ) {
        //gera os n terminais

        epsilon = determinarEpsilon(raio, i+1);
        iterCounter = 0;

        bool sucessoInsercao = false;
        while(!sucessoInsercao) {
            Ponto pNovo;
            bool pontoValido = false;

            do{
                do{
                    double x = ((double)rand() / RAND_MAX) * 2 * raio - raio;
                    double y = ((double)rand() / RAND_MAX) * 2 * raio - raio;
                    pNovo.alteraPonto(x, y, 0);
                }while(!dominio.isInDominio(pNovo)); //sorteia um ponto até que esteja no domínio

                if(respeitaDistanciaMinima(raiz, pNovo, epsilon)){
                    pontoValido = true;
                }
                else {
                    iterCounter++;
                    if(iterCounter > 10) {
                        iterCounter = 0;
                        epsilon *= DECREMENTO_EPSILON;
                    }
                    conexoesRejeitadas++;
                }
            }while(!pontoValido); //repete o sorteio até o ponto ser válido

            std::vector<Candidato> candidatos;

            //preenche o vetor de candidatos e ordena pelo custo euclidiano (mesma ideia do MiniCCO-0);
            //serve apenas para definir a ordem de tentativa, já que a decisão final usa o volume
            elegeCandidatos(candidatos, raiz, pNovo);
            std::sort(candidatos.begin(), candidatos.end(), [](const Candidato& a, const Candidato& b) {
                return a.custo < b.custo;
            });

            //tenta, do candidato mais próximo ao mais distante, otimizar geometricamente a
            //bifurcação (busca em grade) e aceita o primeiro que resultar em posição válida
            for(Candidato& cand : candidatos) {
                conexoesTestadas++;

                No* alvo = cand.noAlvo;
                No* paiAlvo = alvo->pai;

                Ponto A = paiAlvo->p; //ponto proximal do segmento antigo
                Ponto B = alvo->p;    //ponto distal do segmento antigo
                Ponto C = pNovo;      //novo ponto terminal

                //insere temporariamente a bifurcação e o novo terminal na árvore
                No* novaBifurcacao = new No(A, -1);
                No* novoTerminal = new No(C, -2);

                bool eraEsquerda = (paiAlvo->esq == alvo);
                novaBifurcacao->pai = paiAlvo;
                novaBifurcacao->esq = alvo;
                novaBifurcacao->dir = novoTerminal;
                alvo->pai = novaBifurcacao;
                novoTerminal->pai = novaBifurcacao;
                if(eraEsquerda) paiAlvo->esq = novaBifurcacao;
                else            paiAlvo->dir = novaBifurcacao;

                double melhorCusto = -1.0;
                Ponto melhorX = otimizaBifurcacaoPorGrade(raiz, novaBifurcacao, alvo, novoTerminal,
                                                           A, B, C, M, Qterm, gamma, MU, &melhorCusto);

                //desfaz a inserção temporária
                alvo->pai = paiAlvo;
                if(eraEsquerda) paiAlvo->esq = alvo;
                else            paiAlvo->dir = alvo;
                novaBifurcacao->esq = nullptr; //evita apagar a subárvore real no delete abaixo
                novaBifurcacao->dir = nullptr;
                delete novaBifurcacao;
                delete novoTerminal;

                bool valido = (melhorCusto >= 0.0);

                if(valido){
                    //candidato aceito: insere a bifurcação na melhor posição encontrada

                    No* novoNoTerminal = new No(pNovo, idCounter++);
                    No* novaBifurcacaoOK = new No(melhorX, idCounter++);

                    novaBifurcacaoOK->pai = paiAlvo;
                    novaBifurcacaoOK->esq = alvo;
                    novaBifurcacaoOK->dir = novoNoTerminal;
                    alvo->pai = novaBifurcacaoOK;
                    novoNoTerminal->pai = novaBifurcacaoOK;
                    if(paiAlvo->esq == alvo) paiAlvo->esq = novaBifurcacaoOK;
                    else                     paiAlvo->dir = novaBifurcacaoOK;

                    atualizaGeometriaFisica(raiz, Qterm, gamma, MU);

                    sucessoInsercao = true;
                    i++;
                    break; //inserção realizada com sucesso
                }
                else {
                    conexoesRejeitadas++;
                }
            }
        }
    }

    auto tFim = std::chrono::high_resolution_clock::now();
    double tempoExecucao = std::chrono::duration<double>(tFim - tInicio).count();

    double somaRaiosTotal = 0.0;
    int qtdSegmentos = 0;
    somaRaios(raiz, somaRaiosTotal, qtdSegmentos);
    double raioMedio = (qtdSegmentos > 0) ? (somaRaiosTotal / qtdSegmentos) : 0.0;
    double raioRaiz = (raiz->esq != nullptr) ? raiz->esq->raio : 0.0;

    std::cout << "Número total de nós: " << numeroNos(raiz) << "\n";
    std::cout << "Número total de segmentos: " << qtdSegmentos << "\n";
    std::cout << "Número de terminais: " << numeroFolhas(raiz) << "\n";
    std::cout << "Comprimento total da árvore: " << calculaComprimentoTotal(raiz) << "\n";
    std::cout << "Volume intravascular total: " << funcaoCustoVolume(raiz) << "\n";
    std::cout << "Raio da raiz: " << raioRaiz << "\n";
    std::cout << "Raio médio dos segmentos: " << raioMedio << "\n";
    std::cout << "Número de conexões testadas: " << conexoesTestadas << "\n";
    std::cout << "Número de conexões rejeitadas: " << conexoesRejeitadas << "\n";
    std::cout << "Tempo de execução: " << tempoExecucao << " s\n";

    std::ofstream arquivoArvore("arvore.csv");
    arquivoArvore << "id,pai,x0,y0,x1,y1,raio,comprimento,fluxo,resistencia,volume\n";
    escreveArvoreCSV(arquivoArvore, raiz);
    arquivoArvore.close();

    delete raiz;

    return 0;
}

double custoEuclidiano(Ponto a, Ponto b){
    return distanciaEntreDoisPontos(a, b);
}

void elegeCandidatos(std::vector<Candidato>& candidatos, No *raiz, Ponto& pNovo) {
    //preenche o vetor de candidatos
    if(raiz == nullptr)
        return;

    Candidato tempCandidato;
    Ponto pBifurcacao;
    Ponto pA = raiz->p;
    Ponto pB;

    if(raiz->esq != nullptr) {
        pB = raiz->esq->p;
        pBifurcacao.alteraPonto((pA.x + pB.x) / 2.0, (pA.y + pB.y) / 2.0);

        tempCandidato.pCandidato = pBifurcacao;
        tempCandidato.custo = custoEuclidiano(pNovo, pBifurcacao);
        tempCandidato.noAlvo = raiz->esq;

        candidatos.push_back(tempCandidato);
    }

    if(raiz->dir != nullptr) {
        pB = raiz->dir->p;
        pBifurcacao.alteraPonto((pA.x + pB.x) / 2.0, (pA.y + pB.y) / 2.0);

        tempCandidato.pCandidato = pBifurcacao;
        tempCandidato.custo = custoEuclidiano(pNovo, pBifurcacao);
        tempCandidato.noAlvo = raiz->dir;

        candidatos.push_back(tempCandidato);
    }

    //percorre toda a arvore listando os pontos-medios dos segmentos
    elegeCandidatos(candidatos, raiz->esq, pNovo);
    elegeCandidatos(candidatos, raiz->dir, pNovo);
}

bool respeitaDistanciaMinima(No *raiz, Ponto &pNovo, double epsilon) {
    //testa se o ponto respeita a distancia mínima de epsilon para todos os segmentos existentes
    if(raiz == nullptr)
        return true;

    Segmento segExistente;

    if(raiz->esq != nullptr) {
        segExistente.alteraSegmento(raiz->p, raiz->esq->p);
        if(distanciaPontoSegmento(pNovo, segExistente) < epsilon)
            return false;
    }
    if(raiz->dir != nullptr) {
        segExistente.alteraSegmento(raiz->p, raiz->dir->p);
        if(distanciaPontoSegmento(pNovo, segExistente) < epsilon)
            return false;
    }

    if(!respeitaDistanciaMinima(raiz->esq, pNovo, epsilon))
        return false;
    return respeitaDistanciaMinima(raiz->dir, pNovo, epsilon);
}

double determinarEpsilon(double raio, int numTerminais){
    if(numTerminais <= 0)
        return raio;
    return std::sqrt(M_PI * raio * raio / numTerminais);
}

void somaRaios(No *raiz, double &soma, int &contagem){
    if(raiz == nullptr)
        return;
    if(raiz->pai != nullptr){
        soma += raiz->raio;
        contagem++;
    }
    somaRaios(raiz->esq, soma, contagem);
    somaRaios(raiz->dir, soma, contagem);
}

double calculaComprimentoTotal(No *raiz){
    if(raiz == nullptr)
        return 0.0;
    double total = (raiz->pai != nullptr) ? raiz->comprimento : 0.0;
    total += calculaComprimentoTotal(raiz->esq);
    total += calculaComprimentoTotal(raiz->dir);
    return total;
}

void escreveArvoreCSV(std::ofstream& arq, No *raiz){
    //escreve, para cada segmento (nó com pai != nullptr), uma linha no CSV
    if(raiz == nullptr)
        return;

    if(raiz->pai != nullptr){
        arq << raiz->chave << "," << raiz->pai->chave << ","
            << raiz->pai->p.x << "," << raiz->pai->p.y << ","
            << raiz->p.x << "," << raiz->p.y << ","
            << raiz->raio << "," << raiz->comprimento << ","
            << raiz->fluxo << "," << raiz->resistencia << "," << raiz->volume << "\n";
    }

    escreveArvoreCSV(arq, raiz->esq);
    escreveArvoreCSV(arq, raiz->dir);
}