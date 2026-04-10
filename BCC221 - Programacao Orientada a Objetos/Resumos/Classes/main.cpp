#include "Carro.h"
#include <iostream>

using namespace std;

int main() {
    // instanciando objeto
    Carro creta;

    // inicializando objeto
    creta.setPlaca("ABCD-1234");
    creta.setVelocidade(0);

    // utilizando métodos
    cout << "Placa: " << creta.getPlaca() << endl;
    cout << "Velocidade Inicial: " << creta.getVelocidade() << "km/h" << endl;

    creta.acelerar();
    creta.acelerar();
    cout << "Velocidade atual: " << creta.getVelocidade() << "km/h" << endl;
    
    creta.frear();
    cout << "Velocidade atual: " << creta.getVelocidade() << "km/h" << endl;
    
    creta.frear();
    cout << "Velocidade atual: " << creta.getVelocidade() << "km/h" << endl;

    return 0;
}
