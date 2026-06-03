#ifndef TRANSACAO_H
#define TRANSACAO_H

using namespace std;

// imports
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include "../imports/Data.h"
#include "../imports/Horario.h"

// forward declaration
class Cliente;

class Transacao
{
private:
    // ATRIBUTOS
    string tipo;
    double valor;
    Data data;
    Horario horario;
    vector<Cliente*> clientesEnvolvidos;

public:
    // CONSTRUTOR
    Transacao(
        string tipo = "",
        double valor = 0.0,
        Data data = {01, 01, 1900},
        Horario horario = {00, 00},
        vector<Cliente*> clientesEnvolvidos = {}
    );

    // GETTERS
    string getTipo() const;
    double getValor() const;
    Data getData() const; // talvez substituir por Data getData() const;
    Horario getHorario() const;
    vector<Cliente*> getClientesEnvolvidos() const;

    // SETTERS
    void setTipo(string _tipo);
    void setValor(double _valor);
    void setData(Data _data);
    void setHorario(Horario _horario);
    void setClientesEnvolvidos(vector<Cliente*> _clientesEnvolvidos);

    // MÉTODOS
    void exibirTransacao();

    // SOBRECARGA DE OPERADORES
    friend std::ostream& operator<<(std::ostream& os, const Transacao& t);
};

#endif
