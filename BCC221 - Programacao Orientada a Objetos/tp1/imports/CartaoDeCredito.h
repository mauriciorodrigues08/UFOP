#ifndef CARTAODECREDITO_H
#define CARTAODECREDITO_H

#include <string>
#include <vector>
#include <ostream>

using namespace std;

// representa uma parcela de uma compra parcelada
struct Parcela
{
    int numero;       // número da parcela (1, 2, 3...)
    int total;        // total de parcelas
    double valor;     // valor de cada parcela
    string descricao; // descrição da compra
};

class CartaoDeCredito
{
private:
    // ATRIBUTOS
    double limite;          // limite total do cartão
    double limiteDisponivel;// limite ainda disponível
    double fatura;          // valor atual da fatura
    bool bloqueado;         // estado do cartão
    vector<Parcela> parcelas; // parcelas pendentes na fatura

public:
    // CONSTRUTOR
    CartaoDeCredito(double _limite = 0.0);

    // GETTERS
    double getLimite() const;
    double getLimiteDisponivel() const;
    double getFatura() const;
    bool isBloqueado() const;
    vector<Parcela> getParcelas() const;

    // SETTERS
    void setLimite(double _limite);
    void setLimiteDisponivel(double _limiteDisponivel);
    void setFatura(double _fatura);
    void setBloqueado(bool _bloqueado);
    void setParcelas(vector<Parcela> _parcelas);

    // MÉTODOS
    // realiza uma compra simples (1 parcela)
    bool realizarCompra(double _valor, string _descricao);

    // realiza uma compra parcelada
    bool realizarCompraParcelada(double _valor, int _numParcelas, string _descricao);

    // paga a fatura — retorna o valor pago
    double pagarFatura();

    // exibe a fatura detalhada
    void exibirFatura() const;

    // SOBRECARGA DE OPERADORES
    // serialização para CSV
    friend ostream& operator<<(ostream& os, const CartaoDeCredito& cartao);
};

#endif