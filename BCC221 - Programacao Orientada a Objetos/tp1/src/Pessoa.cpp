using namespace std;

// imports
#include "../imports/Pessoa.h"
#include <iostream>

// CONSTRUTOR E DESTRUTOR
Pessoa::Pessoa(string _login, string _senha, string _nome, string _trabalho)
{
    this->setLogin(_login);
    this->setSenha(_senha);
    this->setNome(_nome);
    this->setTrabalho(_trabalho);
}

Pessoa:: ~Pessoa()
{

}

// SETTERS
void Pessoa::setNome(string _nome)
{
    this->nome = _nome;
}

void Pessoa::setTrabalho(string _trabalho)
{
    this->trabalho = _trabalho;
}

void Pessoa::setLogin(string _login)
{
    this->login = _login;
    
}

void Pessoa::setSenha(string _senha)
{
    this->senha = _senha;

}

// GETTERS
string Pessoa::getNome() const
{
    return this->nome;
}

string Pessoa::getTrabalho() const 
{
    return this->trabalho;
    
}

string Pessoa::getLogin() const 
{
    return this->login;
    
}

string Pessoa::getSenha() const 
{
    return this->senha;
}

// MÉTODOS
void Pessoa::exibirDados()
{
    cout << "Nome: " << this->getNome() << endl; 
    cout << "Trabalho: " << this->getTrabalho() << endl; 
    cout << "Login: " << this->getLogin() << endl; 
    cout << "Senha: " << this->getSenha() << endl; 
    cout << endl;
}