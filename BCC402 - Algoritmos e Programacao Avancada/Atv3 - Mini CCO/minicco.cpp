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
}Candidato;

TipoCusto parseModo(std::string s);

double determinarEpsilon(double raio, int numTerminais);
void elegeCandidatos(std::vector<Candidato>& candidatos, No *raiz, Ponto& pNovo);
bool respeitaDistanciaMinima(No *raiz, Ponto &pNovo, double epsilon);
void escreveArvoreCSV(std::ofstream& arq, No *raiz);
void somaRaios(No *raiz, double &soma, int &contagem);


int main(int argc, char *argv[]) {
    if(argc < 7){
        std::cout << "Uso: ./minicco <N_terminais> <Raio> <gamma> <M> <modo> <alpha> <beta> <seed>\n";
        return 1;
    }

    
    int numTerminais = atoi(argv[1]);
    double raio = atof(argv[2]);
    double gamma = atof(argv[3]);
    int M = atoi(argv[4]);
    TipoCusto modo = parseModo(argv[5]);

    double alpha = 1;
    double beta = 1;
    int seed = 1;
    if(argc == 7){
        if(modo <= J2)
            seed = atoi(argv[6]);
        else{
            std::cout<<"Para calculo de custo do tipo J3 ou J4, é necessário informar os valores de alpha e beta\n";
            return 1;
        }
    }
    else if(argc == 9){
        alpha = atof(argv[6]);
        beta = atof(argv[7]);
        seed = atoi(argv[8]);
    }
    else{
        std::cout << "Uso: ./minicco <N_terminais> <Raio> <gamma> <M> <modo> <alpha> <beta> <seed>\n";
        return 1;
    }
    
    srand(seed);

    std::cout<<"Calculando custo no modo: "<<modo<<std::endl;

    if(numTerminais < 2 || raio <= 0.0 || gamma <= 0.0 || M < 1){
        std::cout << "Parâmetros inválidos.\n";
        return 1;
    }

    std::ofstream logArquivo("execucao.log");
    logArquivo << "===== LOG DE EXECUCAO - MiniCCO =====\n";
    logArquivo << "Parametros:\n";
    logArquivo << "  N terminais : " << numTerminais << "\n";
    logArquivo << "  Raio        : " << raio << "\n";
    logArquivo << "  Gamma       : " << gamma << "\n";
    logArquivo << "  M (grade)   : " << M << "\n";
    logArquivo << "  Modo custo  : " << modo << "\n";
    logArquivo << "  Alpha       : " << alpha << "\n";
    logArquivo << "  Beta        : " << beta << "\n";
    logArquivo << "  Seed        : " << seed << "\n";
    logArquivo << "======================================\n\n";


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

            //preenche o vetor de candidatos 
            elegeCandidatos(candidatos, raiz, pNovo);

            bool encontradoValido = false;
            double melhorCustoGlobal = -1.0;
            Ponto melhorXGlobal;
            No* melhorAlvoGlobal = nullptr;

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

                double melhorCustoLocal = -1.0;
                Ponto melhorXLocal = otimizaBifurcacaoPorGrade(raiz, novaBifurcacao, alvo, novoTerminal,
                                                           A, B, C, M, Qterm, gamma, MU, &melhorCustoLocal, 
                                                           modo, alpha, beta);

                //desfaz a inserção temporária
                alvo->pai = paiAlvo;
                if(eraEsquerda) 
                    paiAlvo->esq = alvo;
                else
                    paiAlvo->dir = alvo;

                
                delete novaBifurcacao;
                delete novoTerminal;

                bool valido = (melhorCustoLocal >= 0.0);

                if(valido){
                    if(!encontradoValido || melhorCustoLocal < melhorCustoGlobal){
                        encontradoValido = true;
                        melhorCustoGlobal = melhorCustoLocal;
                        melhorXGlobal = melhorXLocal;
                        melhorAlvoGlobal = alvo;
                    }
                }
                else {
                    conexoesRejeitadas++;
                }
            }
            if(encontradoValido){
                //Depois de avaliar todos os candidatos, insere o de menor custo
                No* alvo = melhorAlvoGlobal;
                No* paiAlvo = alvo->pai;

                No* novoNoTerminal   = new No(pNovo, idCounter++);
                No* novaBifurcacao = new No(melhorXGlobal, idCounter++);

                novaBifurcacao->pai = paiAlvo;
                novaBifurcacao->esq = alvo;
                novaBifurcacao->dir = novoNoTerminal;
                alvo->pai = novaBifurcacao;
                novoNoTerminal->pai = novaBifurcacao;
                if(paiAlvo->esq == alvo)
                    paiAlvo->esq = novaBifurcacao;
                else
                    paiAlvo->dir = novaBifurcacao;

                atualizaGeometriaFisica(raiz, Qterm, gamma, MU);

                if(numTerminais < 51 || i % 25 == 0){
                    //Limita as escritas no log
                    //se o número de terminais for muito grande,
                    //novos pontos só são inseridos no log a cada 25
                    logArquivo << "[Terminal " << (i + 1) << "/" << numTerminais << "] inserido com sucesso\n";
                    logArquivo << "  Ponto sorteado         : " << pNovo << "\n";
                    logArquivo << "  Segmento alvo (antigo) : " << paiAlvo->chave << " -> " << alvo->chave << "\n";
                    logArquivo << "  Nova bifurcacao (id)   : " << novaBifurcacao->chave << " em " << melhorXGlobal << "\n";
                    logArquivo << "  Novo terminal (id)     : " << novoNoTerminal->chave << "\n";
                    logArquivo << "  Custo (" << modo << ")           : " << melhorCustoGlobal << "\n";
                    logArquivo << "  Epsilon usado          : " << epsilon << "\n";
                    logArquivo << "  Candidatos avaliados   : " << candidatos.size() << "\n\n";
                }
                




                sucessoInsercao = true;
                i++;
            }
            else if (numTerminais < 20 || i % 50 == 0){
                //limite mais rígido para os terminais rejeitados
                logArquivo << "[Terminal " << (i + 1) << "] nenhum candidato valido para o ponto "
               << pNovo << " - sorteando novo ponto.\n";
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

    int numNos = numeroNos(raiz);
    int totalTerminais = numeroFolhas(raiz);
    int numeroBifurcacoes = numBifurcacoes(raiz);
    double comprimentoTotal = calculaComprimentoTotal(raiz);
    double volumeTotal = calculaVolumeTotal(raiz);
    double profundidadeMaxima = profundidadeMax(raiz);
    
    std::ofstream arquivoMetricas("metricas.csv");
    arquivoMetricas << "Nterm , Nseg , comprimento_total , volume_total , raio_raiz , "
                    << "raio_medio , profundidade_maxima , tempo_execucao\n";
                
    arquivoMetricas << totalTerminais<<" , "
                    << qtdSegmentos<<" , "
                    << comprimentoTotal<<" , "
                    << volumeTotal<<" , "
                    << raioRaiz<<" , "
                    << raioMedio<<" , "
                    << profundidadeMaxima<<" , "
                    << tempoExecucao<<"\n";
    arquivoMetricas.close();



    std::cout << "Número total de nós: " << numNos << "\n";
    std::cout << "Número total de segmentos: " << qtdSegmentos << "\n";
    std::cout << "Número de terminais: " << totalTerminais << "\n";
    std::cout << "Número total de bifurcações: " << numeroBifurcacoes << "\n";
    std::cout << "Comprimento total da árvore: " << comprimentoTotal << "\n";
    std::cout << "Profundidade Máxima da árvore: " << profundidadeMaxima << "\n";
    std::cout << "Volume intravascular total: " << volumeTotal << "\n";
    std::cout << "Raio da raiz: " << raioRaiz << "\n";
    std::cout << "Raio médio dos segmentos: " << raioMedio << "\n";
    std::cout << "Número de conexões testadas: " << conexoesTestadas << "\n";
    std::cout << "Número de conexões rejeitadas: " << conexoesRejeitadas << "\n";
    std::cout << "Tempo de execução: " << tempoExecucao << " s\n";

    logArquivo << "======================================\n";
    logArquivo << "Resumo final:\n";
    logArquivo << "  Numero total de nos        : " << numNos << "\n";
    logArquivo << "  Numero total de segmentos  : " << qtdSegmentos << "\n";
    logArquivo << "  Numero de terminais        : " << totalTerminais << "\n";
    logArquivo << "  Comprimento total          : " << comprimentoTotal << "\n";
    logArquivo << "  Volume intravascular total : " << volumeTotal << "\n";
    logArquivo << "  Raio da raiz               : " << raioRaiz << "\n";
    logArquivo << "  Raio medio dos segmentos   : " << raioMedio << "\n";
    logArquivo << "  Conexoes testadas          : " << conexoesTestadas << "\n";
    logArquivo << "  Conexoes rejeitadas        : " << conexoesRejeitadas << "\n";
    logArquivo << "  Tempo de execucao          : " << tempoExecucao << " s\n";
    logArquivo << "======================================\n";
    logArquivo.close();

    std::ofstream arquivoArvore("arvore.csv");
    arquivoArvore << "id,pai,x0,y0,z0,x1,y1,z1,raio,comprimento,fluxo,resistencia,volume\n";
    escreveArvoreCSV(arquivoArvore, raiz);
    arquivoArvore.close();



    destroiArvore(raiz);

    return 0;
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
        tempCandidato.noAlvo = raiz->esq;

        candidatos.push_back(tempCandidato);
    }

    if(raiz->dir != nullptr) {
        pB = raiz->dir->p;
        pBifurcacao.alteraPonto((pA.x + pB.x) / 2.0, (pA.y + pB.y) / 2.0);

        tempCandidato.pCandidato = pBifurcacao;
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


void escreveArvoreCSV(std::ofstream& arq, No *raiz){
    //escreve, para cada segmento (nó com pai != nullptr), uma linha no CSV
    if(raiz == nullptr)
        return;

    if(raiz->pai != nullptr){
        arq << raiz->chave << "," << raiz->pai->chave << ","
            << raiz->pai->p.x << "," << raiz->pai->p.y << "," << raiz->pai->p.z << ","
            << raiz->p.x << "," << raiz->p.y << "," << raiz->p.z << ","
            << raiz->raio << "," << raiz->comprimento << ","
            << raiz->fluxo << "," << raiz->resistencia << "," << raiz->volume << "\n";
    }

    escreveArvoreCSV(arq, raiz->esq);
    escreveArvoreCSV(arq, raiz->dir);
}

TipoCusto parseModo(std::string s){
    if(s == "J2" || s == "j2")
        return J2;
    if(s == "J3" || s == "j3")
        return J3;
    if(s == "J4" || s == "j4")
        return J4;


    return J1;
}