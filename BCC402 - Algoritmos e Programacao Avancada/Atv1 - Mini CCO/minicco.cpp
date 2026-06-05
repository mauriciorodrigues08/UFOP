#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <time.h>

#include "include/Arvore.h"
#include "include/Dominio.h"
#include "include/Func.h"
#include "include/Ponto.h"
#include "include/Segmento.h"


//valor pelo qual epsilon será multiplicado após várias iterações sem sucesso
#define DECREMENTO_EPSILON 0.9 

typedef struct Candidato{
    //struct de um candidato para facilitar a organização

    Ponto pCandidato; //ponto médio do segmento que desejamos conectar
    No *noAlvo; //nó onde o segmento termina (Seu ponteiro *pai aponta para o inicio do segmento)
    double custo; //custo para inserir no candidato
}Candidato;

double determinarEpsilon(double raio, int numTerminais); 
double custoEuclidiano(Ponto a, Ponto b);
void escreveNoArquivo(std::ofstream& arquivoNos, std::ofstream& arquivoSegmentos, No *raiz);
double calculaComprimentoRec(No* raiz);

void elegeCandidatos(std::vector<Candidato>& candidatos, No *raiz, Ponto& pNovo); //preenche vetor de possiveis candidatos
bool validaCandidato(Candidato &candidato, No *raiz, Ponto &pNovo, double epsilon); //verifica se o candidato cumpre os requisitos
bool respeitaDistanciaMinima(No *raiz, Ponto &pNovo, double epsilon);


int main(int argc, char *argv[]) {
    if(argc < 3){
        std::cout << "Uso: ./programa <N_terminais> <Raio>\n";
        return 1;
    }
    
    srand(time(NULL));

    int numTerminais = atoi(argv[1]);
    double raio = atof(argv[2]);
    Dominio dominio(raio);

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

        //escolhe o epsilon levando em conta o numero de terminais atual
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
                    //verifica se o ponto está a uma distância menor que epsilon dos outros segmentos
                    pontoValido = true; 
                } 
                else {
                    iterCounter++;
                    if(iterCounter > 10) { 
                        //decrementa o valor de epsilon caso muitos pontos inválidos sejam gerados em sequencia
                        iterCounter = 0;
                        epsilon *= DECREMENTO_EPSILON;
                    }
                    conexoesRejeitadas++;
                }
            }while(!pontoValido); //repete o sorteio até o ponto ser válido 

            std::vector<Candidato> candidatos;

            //preenche o vetor de candidatos
            elegeCandidatos(candidatos, raiz, pNovo); 


            //ordena o vetor do candidato de menor custo até o maior
            std::sort(candidatos.begin(), candidatos.end(), [](const Candidato& a, const Candidato& b) {
                return a.custo < b.custo;
            }); 

            //verifica cada candidato do vetor
            for(Candidato& cand : candidatos) {

                //validaCandidato analisa segmento por segmento da árvore, procurando
                //intersecções com o possível novo segmento criado entre o candidato e o novo ponto
                bool valido = validaCandidato(cand, raiz, pNovo, epsilon);

                if(valido){
                    //candidato de menor custo válido                    

                    No* paiAntigo = cand.noAlvo->pai;
                    No* filhoAntigo = cand.noAlvo;

                    No* novoNoTerminal = new No(pNovo, idCounter++);
                    No* novaBifurcacao = new No(cand.pCandidato, idCounter++);

                    //inicializa os valores da bifurcação criada
                    novaBifurcacao->pai = paiAntigo;
                    novaBifurcacao->esq = filhoAntigo;
                    novaBifurcacao->dir = novoNoTerminal;

                    filhoAntigo->pai = novaBifurcacao;
                    novoNoTerminal->pai = novaBifurcacao;

                    if(paiAntigo->esq == filhoAntigo) //verifica qual segmento foi substituido
                        paiAntigo->esq = novaBifurcacao;
                    else 
                        paiAntigo->dir = novaBifurcacao;

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



    std::cout << "Número total de nós: " << numeroNos(raiz) << "\n";
    std::cout << "Número de nós-folha: " << numeroFolhas(raiz) << "\n";
    std::cout << "Comprimento total da árvore: " << calculaComprimentoRec(raiz) << "\n";
    std::cout << "Número de conexões rejeitadas: " << conexoesRejeitadas << "\n";


    std::ofstream arquivoNos("nos.csv");
    arquivoNos<<"id,x,y\n";
    
    std::ofstream arquivoSegmentos("linhas.csv");
    arquivoSegmentos<<"id_pai,id_filho\n";

    escreveNoArquivo(arquivoNos, arquivoSegmentos, raiz);
    arquivoNos.close();
    arquivoSegmentos.close();

    
    delete raiz; 

    return 0;
}

double custoEuclidiano(Ponto a, Ponto b){
    //custo euclidiano simples
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
        //calcula onde será criada a bifurcação
        pB = raiz->esq->p;
        pBifurcacao.alteraPonto((pA.x + pB.x) / 2.0, (pA.y + pB.y) / 2.0);

        tempCandidato.pCandidato = pBifurcacao;
        tempCandidato.custo = custoEuclidiano(pNovo, pBifurcacao); //calcula o custo euclidiano
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

bool validaCandidato(Candidato &candidato, No *raiz, Ponto &pNovo, double epsilon) {
    //percorre toda a arvore verificando se há algum segmento com distancia menor que epsilon
    if(raiz == nullptr)
        return true;

    Segmento segExistente;
    Segmento segTeste(candidato.pCandidato, pNovo); //segmento entre o candidato e o novo ponto

    if(raiz->esq != nullptr) {
        if(raiz->esq != candidato.noAlvo) { 
            //ignora o teste de intersecção entre o novo ponto e seu candidato
            
            segExistente.alteraSegmento(raiz->p, raiz->esq->p);

            if(intersecaoSegmentos(segExistente, segTeste)) {
                //testa a intersecção entre o possível segmento a ser gerado e o segmento atual
                return false;
            }
            

        }
    }

    if(raiz->dir != nullptr) {
        if(raiz->dir != candidato.noAlvo) {
            //ignora o teste de intersecção entre o novo ponto e seu candidato

            segExistente.alteraSegmento(raiz->p, raiz->dir->p);
            if(intersecaoSegmentos(segExistente, segTeste)) {
                //testa a intersecção entre o possível segmento a ser gerado e o segmento atual
                return false; 
            }
        }
    }
    

    if(!validaCandidato(candidato, raiz->esq, pNovo, epsilon)) //testa para toda sub-arvore da esquerda
        return false;
    //caso não colida com nenhum segmento da sub-arvore esquerda, testa com a direita
    return validaCandidato(candidato, raiz->dir, pNovo, epsilon);
}

bool respeitaDistanciaMinima(No *raiz, Ponto &pNovo, double epsilon) {
    //testa se o ponto respeita a distancia mínima de epsilon para todos os segmentos existentes
    if(raiz == nullptr) 
        return true;

    Segmento segExistente;

    //testa a distancia entre o segmento formado entre o nó atual e seus filhos, e o ponto dado
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

    if(!respeitaDistanciaMinima(raiz->esq, pNovo, epsilon))//testa para toda sub-arvore da esquerda
        return false;

    //caso não falhe na esquerda, testa a direita
    return  respeitaDistanciaMinima(raiz->dir, pNovo, epsilon);
}

void escreveNoArquivo(std::ofstream& arquivoNos, std::ofstream& arquivoSegmentos, No *raiz){
    //escreve no .csv no formato correto
    if(raiz == nullptr)
        return;

    arquivoNos<<raiz->chave<<","<<raiz->p.x<<","<<raiz->p.y<<"\n";
    if(raiz->esq != nullptr){
        arquivoSegmentos<<raiz->chave<<","<<raiz->esq->chave<<"\n";
        escreveNoArquivo(arquivoNos, arquivoSegmentos, raiz->esq);
    }
    if(raiz->dir != nullptr){
        arquivoSegmentos<<raiz->chave<<","<<raiz->dir->chave<<"\n";
        escreveNoArquivo(arquivoNos, arquivoSegmentos, raiz->dir);
    }
}

double calculaComprimentoRec(No* raiz){
    //calcula o tamanho de todos os segmentos
    if(raiz == nullptr) 
        return 0.0;

    double total = 0.0;
    if(raiz->esq != nullptr) 
        total += distanciaEntreDoisPontos(raiz->p, raiz->esq->p) + calculaComprimentoRec(raiz->esq);
    if(raiz->dir != nullptr) 
        total += distanciaEntreDoisPontos(raiz->p, raiz->dir->p) + calculaComprimentoRec(raiz->dir);
    return total;
}

double determinarEpsilon(double raio, int numTerminais){
    if(numTerminais <= 0)
        return raio;
    return std::sqrt(M_PI * raio * raio / numTerminais);
}
