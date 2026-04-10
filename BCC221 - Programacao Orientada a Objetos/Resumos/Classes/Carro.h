#ifndef CARRO_H
#define CARRO_H

#include<string>

using namespace std;

//criação da classe Carro
class Carro {
    // atributos (privados)
    private:
        string placa;
        float velocidade;

    // métodos (públicos)
    public:
        // getters e setters
        void setPlaca(string placa);
        string getPlaca();
        void setVelocidade(float velocidade);
        float getVelocidade();

        // métodos da classe Carro
        void acelerar();
        void frear();
};

#endif
