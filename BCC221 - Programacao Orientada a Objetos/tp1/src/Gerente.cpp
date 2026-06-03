using namespace std;

// imports
#include "../imports/Gerente.h"
#include "../imports/Cliente.h"
#include <iostream>

// CONSTRUTOR E DESTRUTOR
Gerente::Gerente(
    string _login,
    string _senha,
    string _nome,
    string _trabalho,
    Data _dataDeNascimento,
    vector<Cliente*> _clientes
)
    : Pessoa::Pessoa(_login, _senha, _nome, _trabalho)
{
    this->clientes = _clientes;
    this->dataDeNascimento = _dataDeNascimento;
}

// GETTERS
vector<Cliente*> Gerente::getClientes() const
{
    return this->clientes;
}
Data Gerente::getDataDeNascimento() const
{
    return this->dataDeNascimento;
}

// SETTERS
void Gerente::setClientes(vector<Cliente*> _clientes)
{
    this->clientes = _clientes;
}

void Gerente::setDataDeNascimento(Data _dataDeNascimento)
{
    this->dataDeNascimento.ano = _dataDeNascimento.ano;
    this->dataDeNascimento.mes = _dataDeNascimento.mes;
    this->dataDeNascimento.dia = _dataDeNascimento.dia;
}


// MÉTODOS
void Gerente::exibirDados()
{

    // Exibe os dados de Pessoa
    Pessoa::exibirDados();

    // Exibe os dados de Gerente
    cout << "Clientes:" << endl;
    for (Cliente *clienteAtual : clientes)
    {
        clienteAtual->exibirDados();
    }

    cout << endl;
}