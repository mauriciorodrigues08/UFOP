using namespace std;

// imports
#include "../imports/Cliente.h"
#include <iostream>

// CONSTRUTOR E DESTRUTOR
Cliente::Cliente(
    // atributos de Pessoa
    string _login,
    string _senha,
    string _nome,
    string _trabalho,
    // atributos de Cliente
    double _remuneracao,
    string _tipoDeConta,
    double _taxaDeRendimento,
    Data _dataDeNascimento,
    double _saldo,
    vector<Transacao*> _transacoes,
    int _numeroDeConta
)
    : Pessoa::Pessoa(_login, _senha, _nome, _trabalho)
{
    this->setRemuneracao(_remuneracao);
    this->setTipoDeConta(_tipoDeConta);
    this->setTaxaDeRendimento(_taxaDeRendimento);
    this->setSaldo(_saldo);
    this->setDataDeNascimento(_dataDeNascimento);
    this->setTranscoes(_transacoes);
    this->setNumeroDeConta(_numeroDeConta);
    this->cartao = nullptr;
}

// destrutor

// SETTERS
void Cliente::setRemuneracao(double _remuneracao)
{
    this->remuneracao = _remuneracao;
}

void Cliente::setTipoDeConta(string _tipoDeConta)
{
    this->tipoDeConta = _tipoDeConta;
}

void Cliente::setTaxaDeRendimento(double _taxaDeRendimento)
{
    this->taxaDeRendimento = _taxaDeRendimento;
}

void Cliente::setSaldo(double _saldo)
{
    this->saldo = _saldo;
}

void Cliente::setDataDeNascimento(Data _dataDeNascimento)
{
    this->dataDeNascimento.ano = _dataDeNascimento.ano;
    this->dataDeNascimento.mes = _dataDeNascimento.mes;
    this->dataDeNascimento.dia = _dataDeNascimento.dia;
}

void Cliente::setTranscoes(vector<Transacao*> _transacoes)
{
    this->transacoes = _transacoes;
}

void Cliente::setNumeroDeConta(int _numero)
{
    this->numeroDeConta = _numero;
}

void Cliente::setCartao(CartaoDeCredito* _cartao)
{
    this->cartao = _cartao;
}

// GETTERS
double Cliente::getRemuneracao() const
{
    return this->remuneracao;
}

string Cliente::getTipoDeConta() const
{
    return this->tipoDeConta;
}

double Cliente::getTaxaDeRendimento() const
{
    return this->taxaDeRendimento;
}

double Cliente::getSaldo() const
{
    return this->saldo;
}

Data Cliente::getDataDeNascimento() const
{
    return this->dataDeNascimento;
}


vector<Transacao*> Cliente::getTranscoes() const
{
    return this->transacoes;
}

int Cliente::getNumeroDeConta() const
{
    return this->numeroDeConta;
}

CartaoDeCredito* Cliente::getCartao() const
{
    return this->cartao;
}

bool Cliente::temCartao() const
{
    return this->cartao != nullptr;
}

// MÉTODOS
void Cliente::exibirDados()
{
    // Exibe os dados
    Pessoa::exibirDados();

    // Exibe os dados de Cliente
    cout << "Remuneracao: " << this->getRemuneracao() << endl; 
    cout << "Tipo de Conta: " << this->getTipoDeConta() << endl; 
    cout << "Taxa de Rendimento: " << this->getTaxaDeRendimento() << endl; 
    cout << "Saldo: " << this->getSaldo() << endl; 
    // transacoes
    cout << endl;
}

// SOBRECARGA DE OPERADORES
// sobrecarga do operador =
Cliente& Cliente::operator=(const Cliente& novo) {
    // proteção contra auto-atribuição (a = a)
    if (this == &novo) return *this;

    // libera recursos antigos
    for (Transacao* transacaoAtual : this->transacoes)
    {
        delete transacaoAtual;
    }
    this->transacoes.clear();

    // copia os dados do objeto fonte
    this->nome = novo.nome;
    this->trabalho = novo.trabalho;
    this->remuneracao = novo.remuneracao;
    this->tipoDeConta = novo.tipoDeConta;
    this->taxaDeRendimento = novo.taxaDeRendimento;
    this->saldo = novo.saldo;
    this->dataDeNascimento = novo.dataDeNascimento;
    this->transacoes = novo.transacoes; 
    this->setLogin(novo.getLogin());
    this->setSenha(novo.getSenha());

    // retorna referência para si mesmo
    return *this;    
}