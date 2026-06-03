#ifndef CONTROLLER_H
#define CONTROLLER_H

// imports
#include "Cliente.h"
#include "Gerente.h"
#include "Transacao.h"
#include <vector>

class Controller
{
private:
    // vetor para armazenar os clientes
    vector<Cliente*> clientes;

    // vetor para armazenar os gerentes
    vector<Gerente*> gerentes;

    // valor para a próxima conta cadastrada
    int proxNumeroDeConta = 1000;

    // funções auxiliares
    string serializarTransacoes(const vector<Transacao*>& transacoes);
    string serializarClientes(const vector<Cliente*>& clientes);
    string serializarCartao(Cliente* cliente);
    CartaoDeCredito* deserializarCartao(const string& str);
    vector<string> split(const string& linha, char delimitador);
    Transacao* deserializarTransacao(const string& str);
    vector<Transacao*> deserializarTransacoes(const string& str);

public:
    // destrutor — libera clientes, gerentes e transações alocados com new
    ~Controller();

    // cadastrar Clientes
    void cadastrarCliente(Cliente &_novoCliente);
    
    // cadastrar gerente
    void cadastrarGerente(Gerente &_novoCliente);
    
    // visualizar (sobrecarga para cliente)
    void visualizar(Cliente &_cliente);

    // visualizar (sobrecarga para gerente)
    void visualizar(Gerente &_cliente);

    // listar clientes
    void listarCliente(Cliente &cliente);

    // listar gerentes
    void listarGerente(Gerente &gerente);

    // sacar valor
    bool sacar(double _valor, Cliente* &cliente, bool ehTransf);
    
    // depositar valor
    bool depositar(double _valor, Cliente* &cliente, bool ehTransf);
    
    // realizar transacao
    void transferir(Cliente* &_origem, Cliente* &_destino, double _valor);

    // busca uma conta pelo numero
    bool buscaClientePorNumero(int _numeroDestino, Cliente* &cliente);

    // busca uma conta pelo login (sobrecarga com retorno)
    bool buscaClientePorLogin(string _login, Cliente* &cliente);
    
    // busca uma conta pelo login (sobrecarga sem retorno)
    bool buscaClientePorLogin(string _login);

    // busca um gerente por login (sobrecarga com retorno)
    bool buscaGerentePorLogin(string _login, Gerente* &gerente);
    
    // busca um gerente por login (sobrecarga sem retorno)
    bool buscaGerentePorLogin(string _login);

    // verifica se o login e senha correspondem (sobrecarga para Cliente)
    bool verificaLogin(const Cliente &cliente, string _senha);
    
    // verifica se o login e senha correspondem (sobrecarga para Gerente)
    bool verificaLogin(const Gerente &gerente, string _senha);

    // adiciona uma operação ao extrato
    void adicionaAoExtrato(Cliente* &_cliente, string _tipo, double _valor, vector<Cliente*> _clientesEnvolvidos, int tag);

    // retorna a data atual no formato da struct
    Data obterDataAtual();

    // retorna o horario atual no formato da struct
    Horario obterHorarioAtual();

    // exibir extrato de um cliente
    void exibirExtrato(Cliente &_cliente);

    // gera número de conta
    int gerarNumeroDeConta();    

    // associar gerente ao cliente
    void associar(Gerente* &_gerente, Cliente* &_cliente);
    
    // salvar dados    
    void salvarCSV(const string nome_arq_clientes, const string nome_arq_gerentes);

    // carregar dados
    void carregarCSV(const string nome_arq_clientes, const string nome_arq_gerentes);

    // listar logins cadastrados
    void listarLogins();

    // CARTÃO DE CRÉDITO
    // cria cartão para um cliente (limite = 30% da remuneração)
    bool criarCartao(Cliente* &cliente);

    // altera o limite do cartão
    bool alterarLimiteCartao(Cliente* &cliente, double novoLimite);

    // realiza compra simples no cartão
    bool comprarNoCartao(Cliente* &cliente, double valor, string descricao);

    // realiza compra parcelada no cartão
    bool comprarParceladoNoCartao(Cliente* &cliente, double valor, int parcelas, string descricao);

    // paga a fatura do cartão — debita do saldo do cliente
    bool pagarFaturaCartao(Cliente* &cliente);

    // exibe fatura do cartão
    void exibirFaturaCartao(Cliente* &cliente);

    // bloqueia o cartão
    void bloquearCartao(Cliente* &cliente);

    // desbloqueia o cartão
    void desbloquearCartao(Cliente* &cliente);

    // verifica a associação
    bool verificaAssociacao(const Gerente &gerente, int numeroDeConta, Cliente* &cliente);
};

#endif