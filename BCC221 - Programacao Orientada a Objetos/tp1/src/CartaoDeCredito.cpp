using namespace std;

// imports
#include "../imports/CartaoDeCredito.h"
#include <iostream>
#include <iomanip>

// CONSTRUTOR
CartaoDeCredito::CartaoDeCredito(double _limite)
{
    this->limite           = _limite;
    this->limiteDisponivel = _limite;
    this->fatura           = 0.0;
    this->bloqueado        = false;
}

// GETTERS
double CartaoDeCredito::getLimite() const
{
    return this->limite;
}

double CartaoDeCredito::getLimiteDisponivel() const
{
    return this->limiteDisponivel;
}

double CartaoDeCredito::getFatura() const
{
    return this->fatura;
}

bool CartaoDeCredito::isBloqueado() const
{
    return this->bloqueado;
}

vector<Parcela> CartaoDeCredito::getParcelas() const
{
    return this->parcelas;
}

// SETTERS
void CartaoDeCredito::setLimite(double _limite)
{
    this->limite = _limite;
}

void CartaoDeCredito::setLimiteDisponivel(double _limiteDisponivel)
{
    this->limiteDisponivel = _limiteDisponivel;
}

void CartaoDeCredito::setFatura(double _fatura)
{
    this->fatura = _fatura;
}

void CartaoDeCredito::setBloqueado(bool _bloqueado)
{
    this->bloqueado = _bloqueado;
}

void CartaoDeCredito::setParcelas(vector<Parcela> _parcelas)
{
    this->parcelas = _parcelas;
}

// MÉTODOS

// realiza uma compra simples
bool CartaoDeCredito::realizarCompra(double _valor, string _descricao)
{
    // verifica se o cartão está bloqueado
    if (bloqueado)
    {
        cout << "\nErro! Cartão bloqueado. Operação não permitida." << endl;
        return false;
    }

    // verifica se há limite disponível
    if (_valor > limiteDisponivel)
    {
        cout << "\nErro! Limite insuficiente." << endl;
        cout << "Limite disponível: R$" << fixed << setprecision(2) << limiteDisponivel << endl;
        return false;
    }

    // debita do limite e adiciona na fatura
    limiteDisponivel -= _valor;
    fatura           += _valor;

    // registra como parcela única
    Parcela p;
    p.numero    = 1;
    p.total     = 1;
    p.valor     = _valor;
    p.descricao = _descricao;
    parcelas.push_back(p);

    cout << "\nCompra de R$" << fixed << setprecision(2) << _valor
         << " realizada com sucesso!" << endl;
    return true;
}

// realiza uma compra parcelada
bool CartaoDeCredito::realizarCompraParcelada(double _valor, int _numParcelas, string _descricao)
{
    // verifica se o cartão está bloqueado
    if (bloqueado)
    {
        cout << "\nErro! Cartão bloqueado. Operação não permitida." << endl;
        return false;
    }

    // verifica se há limite disponível para o valor total
    if (_valor > limiteDisponivel)
    {
        cout << "\nErro! Limite insuficiente." << endl;
        cout << "Limite disponível: R$" << fixed << setprecision(2) << limiteDisponivel << endl;
        return false;
    }

    // calcula o valor de cada parcela
    double valorParcela = _valor / _numParcelas;

    // debita o valor total do limite e adiciona na fatura
    limiteDisponivel -= _valor;
    fatura           += _valor;

    // registra cada parcela
    for (int i = 1; i <= _numParcelas; i++)
    {
        Parcela p;
        p.numero    = i;
        p.total     = _numParcelas;
        p.valor     = valorParcela;
        p.descricao = _descricao;
        parcelas.push_back(p);
    }

    cout << "\nCompra de R$" << fixed << setprecision(2) << _valor
         << " parcelada em " << _numParcelas << "x de R$"
         << fixed << setprecision(2) << valorParcela
         << " realizada com sucesso!" << endl;
    return true;
}

// paga a fatura inteira — retorna o valor pago
double CartaoDeCredito::pagarFatura()
{
    if (fatura <= 0.0)
    {
        cout << "\nFatura já está zerada." << endl;
        return 0.0;
    }

    double valorPago = fatura;

    // zera a fatura e restaura o limite
    fatura           = 0.0;
    limiteDisponivel = limite;
    parcelas.clear();

    cout << "\nFatura de R$" << fixed << setprecision(2) << valorPago
         << " paga com sucesso! Limite restaurado." << endl;

    return valorPago;
}

// exibe fatura detalhada
void CartaoDeCredito::exibirFatura() const
{
    cout << "====================================================" << endl;
    cout << "                   FATURA DO CARTÃO                " << endl;
    cout << "====================================================" << endl;
    cout << "Limite total:      R$" << fixed << setprecision(2) << limite << endl;
    cout << "Limite disponível: R$" << fixed << setprecision(2) << limiteDisponivel << endl;
    cout << "Status: " << (bloqueado ? "BLOQUEADO" : "Ativo") << endl;
    cout << "----------------------------------------------------" << endl;

    if (parcelas.empty())
    {
        cout << "Nenhuma compra na fatura." << endl;
    }
    else
    {
        cout << "Compras:" << endl;
        for (const Parcela& p : parcelas)
        {
            cout << "  " << p.descricao;
            if (p.total > 1)
                cout << " (" << p.numero << "/" << p.total << ")";
            cout << " — R$" << fixed << setprecision(2) << p.valor << endl;
        }
    }

    cout << "----------------------------------------------------" << endl;
    cout << "Total da fatura: R$" << fixed << setprecision(2) << fatura << endl;
    cout << "====================================================" << endl;
}

// serialização para CSV
// formato: limite;limiteDisponivel;fatura;bloqueado;parcelas
// cada parcela: numero:total:valor:descricao separadas por '|'
ostream& operator<<(ostream& os, const CartaoDeCredito& cartao)
{
    os << cartao.limite << ";"
       << cartao.limiteDisponivel << ";"
       << cartao.fatura << ";"
       << cartao.bloqueado;

    // serializa as parcelas
    vector<Parcela> parcelas = cartao.getParcelas();
    if (!parcelas.empty())
    {
        os << ";";
        for (int i = 0; i < (int)parcelas.size(); i++)
        {
            if (i > 0) os << "|";
            os << parcelas[i].numero << ":"
               << parcelas[i].total  << ":"
               << parcelas[i].valor  << ":"
               << parcelas[i].descricao;
        }
    }

    return os;
}