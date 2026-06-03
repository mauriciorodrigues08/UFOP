#ifndef CLIENTE_H
#define CLIENTE_H

using namespace std;

//imports
#include "Pessoa.h"
#include "Transacao.h"
#include "Data.h"
#include "CartaoDeCredito.h"
#include <string>
#include <vector>

class Cliente : public Pessoa
{
private:
    // ATRIBUTOS
    double remuneracao;
    string tipoDeConta;
    int numeroDeConta;
    double taxaDeRendimento;
    Data dataDeNascimento;
    double saldo;
    vector <Transacao*> transacoes;
    CartaoDeCredito* cartao; // nullptr se não tiver cartão

public:
    // CONSTRUTOR E DESTRUTOR
    Cliente(
        // atributos de Pessoa
        string _login = "",
        string _senha = "",
        string _nome = "",
        string _trabalho = "",
        // atributos de Cliente
        double _remuneracao = 0.0,
        string _tipoDeConta = "",
        double _taxaDeRendimento = 0.0,
        Data _dataDeNascimento = {01,01,1900},    
        double _saldo = 0.0,
        vector<Transacao*> _transacoes = {},
        int numeroDeConta = 0
    );
    // destrutor

    // SETTERS
    void setRemuneracao(double _remuneracao);
    void setTipoDeConta(string _tipoDeConta);
    void setTaxaDeRendimento(double _taxaDeRendimento);
    void setSaldo(double _saldo);
    void setDataDeNascimento(Data _dataDeNascimento);
    void setTranscoes(vector<Transacao*> transacoes);
    void setNumeroDeConta(int _numero);
    void setCartao(CartaoDeCredito* _cartao);
    
    // GETTERS
    double getRemuneracao() const;
    string getTipoDeConta() const;
    double getTaxaDeRendimento() const;
    double getSaldo() const;
    Data getDataDeNascimento() const;
    vector<Transacao*> getTranscoes() const;
    int getNumeroDeConta() const;
    CartaoDeCredito* getCartao() const;

    // MÉTODOS
    void exibirDados() override;
    bool temCartao() const;

    // SOBRECARGA DE OPERADORES
    Cliente& operator=(const Cliente& novo);
};

#endif