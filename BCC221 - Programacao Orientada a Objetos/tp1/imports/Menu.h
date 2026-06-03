#ifndef MENU_H
#define MENU_H

// imports
#include <vector>

// declaração futura
class Controller;

class Menu
{
public:
    // iniciar menu
    void iniciar();

    // MENU PRINCIPAL
    void imprimeMenu();

    // SUBMENUS
    // cadastrar cliente ou gerente
    void menuCadastrar(Controller &controller);

    // depósito, saque ou transferência
    void menuOperacoes(Controller &controller);

    // extrato, listar cliente/gerente/logins
    void menuConsultas(Controller &controller);

    // FUNÇÕES DO MENU
    // cadastrar Clientes
    void cadastrarCliente(Controller &controller);
    
    // cadastrar gerente
    void cadastrarGerente(Controller &controller);

    // realizar depósito
    void depositar(Controller &controller);
    
    // realizar saque
    void sacar(Controller &controller);

    // realizar transação
    void transferir(Controller &controller);
    
    // exibir extrato de um cliente
    void exibirExtrato(Controller &controller);
    
    // associar gerente ao cliente
    void associar(Controller &controller);
    
    // listar um cliente
    void listarCliente(Controller &controller);

    // listar um gerente
    void listarGerente(Controller &controller);
    
    // carregar dados
    void carregarDoCsv(Controller &controller);

    // salvar dados    
    void salvarNoCsv(Controller &controller);

    // lista os logins cadastrados
    void listarLogins(Controller &controller);

    // SUBMENU CARTÃO DE CRÉDITO
    void menuCartao(Controller &controller);
    void criarCartao(Controller &controller);
    void alterarLimiteCartao(Controller &controller);
    void comprarNoCartao(Controller &controller);
    void comprarParceladoNoCartao(Controller &controller);
    void pagarFaturaCartao(Controller &controller);
    void exibirFaturaCartao(Controller &controller);
    void bloquearCartao(Controller &controller);
    void desbloquearCartao(Controller &controller);
};

#endif