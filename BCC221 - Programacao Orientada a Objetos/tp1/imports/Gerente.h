#ifndef GERENTE_H
#define GERENTE_H

using namespace std;

// imports
#include "Pessoa.h"
#include "Cliente.h"
#include "Data.h"
#include <vector>
#include <string>

class Gerente : public Pessoa
{
    private:
    // ATRIBUTOS
    Data dataDeNascimento;
    vector<Cliente*> clientes;

    public:
    // CONSTRUTOR E DESTRUTOR
    Gerente(
        string _login = "",
        string _senha = "",
        string _nome = "",
        string _trabalho = "",
        Data _dataDeNascimento = {01,01,1900},
        vector<Cliente*> _clientes = {}
    );
    
    // destruror

    // GETTERS
    vector<Cliente*> getClientes() const;
    Data getDataDeNascimento() const;
    
    // SETTERS
    void setClientes(vector<Cliente*> _clientes);
    void setDataDeNascimento(Data _dataDeNascimento);

    // MÉTODOS
    void exibirDados() override;
    
};

#endif