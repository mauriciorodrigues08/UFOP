#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>

using namespace std;

class Pessoa
{
    private:
    // atributos privados
    string login;
    string senha;

    public:
    // atributos públicos
    string nome;
    string trabalho;

    // CONSTRUTOR E DESTRUTOR
    Pessoa(
        string _login = "",
        string _senha = "",
        string _nome = "",
        string _trabalho = ""
    );
    
    virtual ~Pessoa();

    // SETTERS
    void setNome(string _nome);
    void setTrabalho(string _trabalho);
    void setLogin(string _login);
    void setSenha(string _senha);

    // GETTERS
    string getNome() const;
    string getTrabalho() const;
    string getLogin() const;
    string getSenha() const;

    // MÉTODOS
    virtual void exibirDados() = 0;
};

#endif