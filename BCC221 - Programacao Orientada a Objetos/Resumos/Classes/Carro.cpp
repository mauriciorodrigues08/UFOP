#include "Carro.h"

#include <iostream>


using namespace std;

// getters e setters
void Carro::setPlaca(string placa) {
    this->placa = placa;
}

string Carro::getPlaca() {
    return this->placa;
}

void Carro::setVelocidade(float velocidade) {
    this->velocidade = velocidade;
}

float Carro::getVelocidade() {
    return this->velocidade;
}

// métodos da classe Carro
void Carro::acelerar(){
    this->velocidade += 10;
    cout << "Carro acelerou!" << endl;
}

void Carro::frear() {
    if ((this->velocidade -= 10) > 0) {
        cout << "Carro freou!" << endl;
        return;
    }
    this->setVelocidade(0);
    cout << "Carro parou!" << endl;
}
