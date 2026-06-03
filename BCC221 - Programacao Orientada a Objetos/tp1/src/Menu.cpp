using namespace std;

// includes
#include "../imports/Menu.h"
#include "../imports/Controller.h"
#include "../imports/CartaoDeCredito.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <iomanip>

// defines
#define NOME_ARQ_CLIENTES "clientes.csv"
#define NOME_ARQ_GERENTES "gerentes.csv"

// iniciar menu
void Menu::iniciar()
{
    // limpa o terminal
    system("clear");

    // instancia variável de controle
    Controller *controller = new Controller();

    // carrega os dados do arquivo csv
    carregarDoCsv(*controller);
    
    // variável de escolha da opção
    int op;

    // loop de execução
    do
    {
        // limpa o terminal
        system("clear");

        // mostra o menu
        imprimeMenu();

        // recebe a opção escolhida
        while (true) 
        {
            // tenta realizar a leitura
            if (cin >> op)
            {
                // se a leitura deu certo, verifica se está no intervalo
                if (op >= 0 && op <= 6) break;
                
                // caso não esteja no intervalo
                cout << "\nOpção Inválida! Digite novamente: ";
            } 
            else 
            {
                // caso o usuário digite algo que não é um int
                cout << "\nOpção inválida! Digite novamente: ";

                // limpa o estado de erro do cin
                cin.clear();

                // remove tudo o que foi digitado de errado do buffer até o final da linha
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // seleciona a opção escolhida
        switch (op)
        {
        case 1:
            menuCadastrar(*controller);
            break;
        
        case 2:
            menuOperacoes(*controller);
            break;
        
        case 3:
            menuConsultas(*controller);
            break;
            
        case 4:
            associar(*controller);
            break;
        
        case 5:
            listarLogins(*controller);
            break;

        case 6:
            menuCartao(*controller);
            break;

        case 0:
            salvarNoCsv(*controller);
            cout << "===================================================" << endl;
            cout << "Programa finalizado!" << endl;
            break;
        }

    } while (op != 0);
    
    delete controller;
}

// imprime o menu principal
void Menu::imprimeMenu()
{
    cout << "===================================================" << endl;
    cout << "         SISTEMA DE GERENCIAMENTO DE BANCO         " << endl;
    cout << "===================================================" << endl;
    cout << "  1. Cadastrar" << endl;
    cout << "  2. Operações bancárias" << endl;
    cout << "  3. Consultas" << endl;
    cout << "  4. Associar gerente a um cliente" << endl;
    cout << "  5. Listar logins cadastrados" << endl;
    cout << "  6. Cartão de crédito" << endl;
    cout << "  0. Salvar dados e sair" << endl;
    cout << "===================================================" << endl;
    cout << "Escolha uma opção: ";
}

// submenu: cadastrar cliente ou gerente
void Menu::menuCadastrar(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "                    CADASTRAR                      " << endl;
    cout << "===================================================" << endl;
    cout << "  1. Cadastrar cliente" << endl;
    cout << "  2. Cadastrar gerente" << endl;
    cout << "  0. Voltar" << endl;
    cout << "===================================================" << endl;
    cout << "Escolha uma opção: ";

    int op;
    while (true)
    {
        if (cin >> op)
        {
            if (op >= 0 && op <= 2) break;
            cout << "\nOpção Inválida! Digite novamente: ";
        }
        else
        {
            cout << "\nOpção inválida! Digite novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    switch (op)
    {
    case 1: cadastrarCliente(controller); break;
    case 2: cadastrarGerente(controller); break;
    case 0: break;
    }
}

// submenu: operações bancárias
void Menu::menuOperacoes(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "               OPERAÇÕES BANCÁRIAS                 " << endl;
    cout << "===================================================" << endl;
    cout << "  1. Realizar depósito" << endl;
    cout << "  2. Realizar saque" << endl;
    cout << "  3. Realizar transferência" << endl;
    cout << "  0. Voltar" << endl;
    cout << "===================================================" << endl;
    cout << "Escolha uma opção: ";

    int op;
    while (true)
    {
        if (cin >> op)
        {
            if (op >= 0 && op <= 3) break;
            cout << "\nOpção Inválida! Digite novamente: ";
        }
        else
        {
            cout << "\nOpção inválida! Digite novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    switch (op)
    {
    case 1: depositar(controller);  break;
    case 2: sacar(controller);      break;
    case 3: transferir(controller); break;
    case 0: break;
    }
}

// submenu: consultas
void Menu::menuConsultas(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "                    CONSULTAS                      " << endl;
    cout << "===================================================" << endl;
    cout << "  1. Exibir extrato" << endl;
    cout << "  2. Listar cliente" << endl;
    cout << "  3. Listar gerente" << endl;
    cout << "  0. Voltar" << endl;
    cout << "===================================================" << endl;
    cout << "Escolha uma opção: ";

    int op;
    while (true)
    {
        if (cin >> op)
        {
            if (op >= 0 && op <= 3) break;
            cout << "\nOpção Inválida! Digite novamente: ";
        }
        else
        {
            cout << "\nOpção inválida! Digite novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    switch (op)
    {
    case 1: exibirExtrato(controller); break;
    case 2: listarCliente(controller); break;
    case 3: listarGerente(controller); break;
    case 0: break;
    }
}

// cadastrar Clientes
void Menu::cadastrarCliente(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // mostra o cabeçalho
    cout << "===================================================" << endl;
    cout << "              CADASTRAR NOVO CLIENTE               " << endl;
    cout << "===================================================" << endl;

    // recebe os dados do Cliente
    // NOME
    string nome;
    cout << "Informe o nome: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
    
    // TRABALHO
    string trabalho;
    cout << "Informe o trabalho: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, trabalho);

    // DATA DE NASCIMENTO
    Data dataDeNascimento;
    cout << "Informe a data de nascimento...\n";

    // dia
    int dia;
    cout << "Dia: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> dia)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (dia > 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Dia inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // mes 
    int mes;
    cout << "Mês: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> mes)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (mes > 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Mês inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // ano 
    int ano;
    cout << "Ano: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> ano)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (ano > 0) break;
            else 
            {
                cout << "Ano inválido! Digite novamente: ";
            }                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Ano inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    dataDeNascimento.dia = dia;
    dataDeNascimento.mes = mes;
    dataDeNascimento.ano = ano;
    
    // LOGIN
    string login;
    cout << "Informe o login: ";
    cin >> login;
    
    // verifica se o login já existe
    while (controller.buscaClientePorLogin(login))
    {
        cout << "Cliente de login '" << login << "' já existe!" << endl;
        cout << "Tente outro login: ";
        cin >> login;
    }

    // SENHA
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;
    
    // confirma a senha escolhida
    string confirmacao;
    cout << "Confirme a senha: ";
    cin >> confirmacao;
    while (confirmacao != senha)
    {
        cout << "Senhas incompatíveis! \nDigite novamente: ";
        cin >> confirmacao;
    }
    
    // REMUNERAÇÃO
    double remuneracao;
    cout << "Informe a remuneração: R$";

    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> remuneracao)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (remuneracao >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Valor inválido! Digite novamente: R$";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // TIPO DE CONTA
    string tipo;
    int op;
    cout << "Informe o tipo de conta(1. Corrente; 2. Poupança): ";

    // verifica o tipo de conta que será fornecido
    while (true)
    {
        // caso a leitura tenha funcionado e o valor seja válido
        if ((cin >> op) && (op == 1 || op == 2)) break;
        else
        {
            // caso o usuário digite algo que não é um int
            cout << "Tipo inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // atribui o tipo de conta
    if (op == 1) tipo = "Corrente";
    else tipo = "Poupança";
    
    // TAXA DE RENDIMENTO
    double rendimento;
    cout << "Informe a taxa de rendimento ao ano (ex: 0.15): ";

    // verifica o valor que será informado
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> rendimento)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (rendimento > 0 && rendimento <= 0.3) break;                
            else cout << "Valor deve estar entre 0.01 e 0.3! Digite novamente:";
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Valor inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // saldo e transações serão inicializados no construtor

    // instancia o novo cliente
    Cliente *novoCliente = new Cliente(login, senha, nome, trabalho, remuneracao, tipo, rendimento, dataDeNascimento);

    // faz a chamada da função do controller
    controller.cadastrarCliente(*novoCliente);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// cadastrar gerente
void Menu::cadastrarGerente(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // mostra o cabeçalho
    cout << "===================================================" << endl;
    cout << "              CADASTRAR NOVO GERENTE               " << endl;
    cout << "===================================================" << endl;

    // recebe os dados do Gerente
    // NOME
    string nome;
    cout << "Informe o nome: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
    
    // DATA DE NASCIMENTO
    Data dataDeNascimento;
    cout << "Informe a data de nascimento...\n";

    // dia
    int dia;
    cout << "Dia: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> dia)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (dia > 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Dia inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // mes 
    int mes;
    cout << "Mês: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> mes)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (mes > 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Mês inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // ano 
    int ano;
    cout << "Ano: ";
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> ano)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (ano > 0) break;
            else 
            {
                cout << "Ano inválido! Digite novamente: ";
            }                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Ano inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    dataDeNascimento.dia = dia;
    dataDeNascimento.mes = mes;
    dataDeNascimento.ano = ano;
    
    // TRABALHO
    string trabalho;
    cout << "Informe o trabalho: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, trabalho);
    
    // LOGIN
    string login;
    cout << "Informe o login: ";
    cin >> login;

    // verifica se o login já existe
    while (controller.buscaGerentePorLogin(login))
    {
        cout << "Gerente de login '" << login << "' já existe!" << endl;
        cout << "Tente outro login: ";
        cin >> login;
    }
    
    // SENHA
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // confirma a senha escolhida
    string confirmacao;
    cout << "Confirme a senha: ";
    cin >> confirmacao;
    while (confirmacao != senha)
    {
        cout << "Senhas incompatíveis! \nDigite novamente: ";
        cin >> confirmacao;
    }

    // vetor de clientes será inicializado pelo construtor

    // instancia o novo Gerente
    Gerente *novoGerente = new Gerente(login, senha, nome, trabalho, dataDeNascimento);

    // chama a função do controller
    controller.cadastrarGerente(*novoGerente);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// realizar depósito
void Menu::depositar(Controller &controller)
{
    system("clear");
    // mostra o cabeçalho
    cout << "===================================================" << endl;
    cout << "                REALIZAR DEPÓSITO                  " << endl;
    cout << "===================================================" << endl;

    // CONTA
    // recebe o login
    string login;
    cout << "Informe o login da conta: ";
    cin >> login;

    // chama o método buscaConta do controller para procurar a conta origem
    Cliente *conta;
    if (!controller.buscaClientePorLogin(login, conta))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // chama o método verificaLogin do controller
    if (!controller.verificaLogin(*conta, senha))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // VALOR
    double valor;
    cout << "Informe o valor: R$";

    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> valor)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (valor >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Valor inválido! Digite novamente: R$";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // chama a função depositar do controller
    controller.depositar(valor, conta, false);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// realizar saque
void Menu::sacar(Controller &controller)
{
    system("clear");
    // mostra o cabeçalho
    cout << "===================================================" << endl;
    cout << "                  REALIZAR SAQUE                   " << endl;
    cout << "===================================================" << endl;

    // CONTA
    // recebe o login
    string login;
    cout << "Informe o login da conta: ";
    cin >> login;

    // chama o método buscaConta do controller para procurar a conta origem
    Cliente *conta;
    if (!controller.buscaClientePorLogin(login, conta))
    {
        cout << "\nSenha incorreta!" << endl;
        cout << "Operação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // chama o método verificaLogin do controller
    if (!controller.verificaLogin(*conta, senha))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // VALOR
    double valor;
    cout << "Informe o valor: R$";

    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> valor)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (valor >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Valor inválido! Digite novamente: R$";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // chama a função depositar do controller
    controller.sacar(valor, conta, false);
    
    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// realizar transação
void Menu::transferir(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // mostra o cabeçalho
    cout << "===================================================" << endl;
    cout << "               REALIZANDO TRANSAÇÃO                " << endl;
    cout << "===================================================" << endl;

    // ORIGEM
    // recebe o login
    string loginOrigem;
    cout << "Informe o login da conta de origem: ";
    cin >> loginOrigem;
    
    // chama o método buscaConta do controller para procurar a conta origem
    Cliente *origem;
    if (!controller.buscaClientePorLogin(loginOrigem, origem))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // chama o método verificaLogin do controller
    if (!controller.verificaLogin(*origem, senha))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // DESTINO
    int numeroDestino;
    cout << "Informe o número da conta de destino: ";
    
    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> numeroDestino)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (numeroDestino >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Número inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // chama o método buscaConta do controller para procurar a conta destino
    Cliente *destino;
    if (!controller.buscaClientePorNumero(numeroDestino, destino))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // verifica se a conta destino é igual a origem
    if (numeroDestino == origem->getNumeroDeConta())
    {
        cout << "Não é possível realizar uma transferência para você mesmo!";
        cout << "Operação cancelada!";
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // realiza uma verificação
    string op;
    cout << "\nTransferindo para " << destino->getNome() << endl;
    cout << "Continuar? (S/N): ";
    cin >> op;

    if (op == "N" || op== "n")
    {
        cout << "\nOperação Cancelada!" << endl;
        return;
    }

    // VALOR
    double valor;
    cout << "Informe o valor: R$";

    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> valor)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (valor >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Valor inválido! Digite novamente: R$";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // chama o método transferir do controller
    controller.transferir(origem, destino, valor);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// exibir extrato de um cliente
void Menu::exibirExtrato(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // exibe o cabeçalho
    cout << "===================================================" << endl;
    cout << "                  EXIBIR EXTRATO                   " << endl;
    cout << "===================================================" << endl;

    // recebe o login
    string login;
    cout << "Informe o login: ";
    cin >> login;

    // verifica se o cliente existe
    Cliente *cliente;
    if (!controller.buscaClientePorLogin(login, cliente))
    {
        cout << "\nOperação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // verifica se a senha está incorreta
    if (!controller.verificaLogin(*cliente, senha))
    {
        cout << "\nSenha incorreta!" << endl;
        cout << "Operação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // chama a função exibirExtrato do controller
    controller.exibirExtrato(*cliente);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// associar gerente ao cliente
void Menu::associar(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // exibe o cabeçalho
    cout << "===================================================" << endl;
    cout << "           ASSOCIAR CLIENTE A UM GERENTE           " << endl;
    cout << "===================================================" << endl;

    // recebe o login do gerente
    string login;
    cout << "Informe o login do Gerente: ";
    cin >> login;

    // verifica se existe um gerente cadastrado com esse login
    Gerente *gerente;
    if(!controller.buscaGerentePorLogin(login, gerente))
    {
        cout << "Operação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // verifica se a senha está correta
    if (!controller.verificaLogin(*gerente, senha))
    {
        cout << "Operação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe o numero de conta do cliente
    int numeroDeConta;
    cout << "Informe o número de conta: ";
    // verifica o valor que será fornecido
    while (true) 
    {
        // tenta realizar a leitura
        if (cin >> numeroDeConta)
        {
            // se a leitura deu certo, verifica se está no intervalo
            if (numeroDeConta >= 0) break;                
        } 
        else 
        {
            // caso o usuário digite algo que não é um int
            cout << "Número inválido! Digite novamente: ";

            // limpa o estado de erro do cin
            cin.clear();

            // remove tudo o que foi digitado de errado do buffer até o final da linha
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // verifica se o cliente existe
    Cliente *cliente;
    if(!controller.buscaClientePorNumero(numeroDeConta, cliente))
    {
        cout << "Operação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return; 
    }

    // chama a função de associar
    controller.associar(gerente, cliente);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// listar clientes
void Menu::listarCliente(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // exibe o cabeçalho
    cout << "===================================================" << endl;
    cout << "                  LISTAR CLIENTE                   " << endl;
    cout << "===================================================" << endl;
    
    // recebe o login do cliente
    string login;
    cout << "Informe o login: ";
    cin >> login;

    // verifica se existe o login
    Cliente *cliente;
    if(!controller.buscaClientePorLogin(login, cliente))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // verifica se a senha está correta
    if(!controller.verificaLogin(*cliente, senha))
    {
        cout << "\nSenha incorreta!\nOperação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // chama a função que lista o cliente
    controller.listarCliente(*cliente);
    
    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// listar gerentes
void Menu::listarGerente(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // exibe o cabeçalho
    cout << "===================================================" << endl;
    cout << "                  LISTAR GERENTE                   " << endl;
    cout << "===================================================" << endl;
    
    // recebe o login do cliente
    string login;
    cout << "Informe o login: ";
    cin >> login;

    // verifica se existe o login
    Gerente *gerente;
    if(!controller.buscaGerentePorLogin(login, gerente))
    {
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // recebe a senha
    string senha;
    cout << "Informe a senha: ";
    cin >> senha;

    // verifica se a senha está correta
    if(!controller.verificaLogin(*gerente, senha))
    {
        cout << "\nSenha incorreta!\nOperação Cancelada!" << endl;
        cout << "===================================================" << endl;
        cout << "\nPressione enter para voltar ao menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
        return;
    }

    // chama a função que lista os gerentes
    controller.listarGerente(*gerente);

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// salvar dados    
void Menu::salvarNoCsv(Controller &controller)
{
    //chama a funcao para salvar os dados
    controller.salvarCSV(NOME_ARQ_CLIENTES, NOME_ARQ_GERENTES);
}

// carregar dados
void Menu::carregarDoCsv(Controller &controller)
{
    // cahama a funcao para carregar os dados
   controller.carregarCSV(NOME_ARQ_CLIENTES, NOME_ARQ_GERENTES);
}

// lista os logins cadastrados
void Menu::listarLogins(Controller &controller)
{
    // limpa o terminal
    system("clear");

    // exibe o cabeçalho
    cout << "===================================================" << endl;
    cout << "                LOGINS CADASTRADOS                 " << endl;
    cout << "===================================================" << endl;

    // chama a função do controller
    controller.listarLogins();

    cout << "===================================================" << endl;
    cout << "\nPressione enter para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// submenu para o cartão de crédito 
void Menu::menuCartao(Controller &controller)
{
    int op;
    do
    {
        system("clear");
        cout << "===================================================" << endl;
        cout << "                 CARTÃO DE CRÉDITO                 " << endl;
        cout << "===================================================" << endl;
        cout << "  1. Criar cartão para cliente" << endl;
        cout << "  2. Alterar limite do cartão" << endl;
        cout << "  3. Realizar compra" << endl;
        cout << "  4. Realizar compra parcelada" << endl;
        cout << "  5. Exibir fatura" << endl;
        cout << "  6. Pagar fatura" << endl;
        cout << "  7. Bloquear cartão" << endl;
        cout << "  8. Desbloquear cartão" << endl;
        cout << "  0. Voltar" << endl;
        cout << "===================================================" << endl;
        cout << "Escolha uma opção: ";

        while (true)
        {
            if ((cin >> op) && op >= 0 && op <= 8) break;
            cout << "Opção inválida! Digite novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (op)
        {
            case 1:
                criarCartao(controller);
                break;
            
            case 2:
                alterarLimiteCartao(controller);
                break;
            
            case 3:
                comprarNoCartao(controller);
                break;
            
            case 4:
                comprarParceladoNoCartao(controller);
                break;
            
            case 5:
                exibirFaturaCartao(controller);
                break;
            
            case 6:
                pagarFaturaCartao(controller);
                break;
            
            case 7:
                bloquearCartao(controller);
                break;
            
            case 8:
                desbloquearCartao(controller);
                break;

            case 0:
                break;
        }

        if (op != 0)
        {
            cout << "\n===================================================" << endl;
            cout << "Pressione enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (op != 0);
}

// pede login e senha e retorna o ponteiro para o gerente
static bool autenticarGerente(Controller &controller, Gerente* &gerente)
{
    controller.listarLogins();

    string login;
    cout << "Login do gerente: ";
    cin >> login;

    if (!controller.buscaGerentePorLogin(login, gerente)) return false;

    string senha;
    cout << "Senha: ";
    cin >> senha;

    if (!controller.verificaLogin(*gerente, senha))
    {
        cout << "\nErro! Senha incorreta." << endl;
        return false;
    }
    return true;
}

// pede login e senha e retorna o ponteiro para o cliente
static bool autenticarCliente(Controller &controller, Cliente* &cliente)
{
    controller.listarLogins();

    string login;
    cout << "Login do cliente: ";
    cin >> login;

    if (!controller.buscaClientePorLogin(login, cliente)) return false;

    string senha;
    cout << "Senha: ";
    cin >> senha;

    if (!controller.verificaLogin(*cliente, senha))
    {
        cout << "\nErro! Senha incorreta." << endl;
        return false;
    }
    return true;
}

// cria um cartão
void Menu::criarCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "           CRIAR CARTÃO DE CRÉDITO                 " << endl;
    cout << "===================================================" << endl;

    // gerente faz o login
    Gerente* gerente = nullptr;
    if (!autenticarGerente(controller, gerente)) return;

    // mostra os clientes daquele gerente
    cout << "\nClientes associados:" << endl;
    vector<Cliente*> clientesDoGerente = gerente->getClientes();
    for(Cliente* clienteAtual : clientesDoGerente)
    {
        cout << "Nome: " << clienteAtual->getNome() << endl;
        cout << "Número de Conta: " << clienteAtual->getNumeroDeConta() << endl;
        cout << "\n";
    }

    // seleciona o cliente
    int numeroDeConta;
    cout << "Informe o número de Conta do cliente: ";
    cin >> numeroDeConta;
    
    // verifica se o cliente está associado ao gerente
    Cliente* cliente;

    if(!controller.verificaAssociacao(*gerente, numeroDeConta, cliente))
    {
        cout << "Cliente não pertence ao gerente!" << endl;
        cout << "Operação Cancelada!" << endl;
        return;
    }

    // cria o cartão
    controller.criarCartao(cliente);
}

// altera o limite do cartão
void Menu::alterarLimiteCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "           ALTERAR LIMITE DO CARTÃO                " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    if (!cliente->temCartao())
    {
        cout << "\nCliente não possui cartão de crédito." << endl;
        return;
    }

    cout << "Limite atual: R$" << fixed << setprecision(2)
         << cliente->getCartao()->getLimite() << endl;
    cout << "Novo limite: R$";

    double novoLimite;
    while (true)
    {
        if ((cin >> novoLimite) && novoLimite > 0) break;
        cout << "Valor inválido! Digite novamente: R$";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    controller.alterarLimiteCartao(cliente, novoLimite);
}

// realiza uma compra simples no cartão
void Menu::comprarNoCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "              COMPRA NO CARTÃO                     " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    if (!cliente->temCartao())
    {
        cout << "\nCliente não possui cartão de crédito." << endl;
        return;
    }

    cout << "Limite disponível: R$" << fixed << setprecision(2)
         << cliente->getCartao()->getLimiteDisponivel() << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string descricao;
    cout << "Descrição da compra: ";
    getline(cin, descricao);

    double valor;
    cout << "Valor: R$";
    while (true)
    {
        if ((cin >> valor) && valor > 0) break;
        cout << "Valor inválido! Digite novamente: R$";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    controller.comprarNoCartao(cliente, valor, descricao);
}

// realiza uma compra parcelada
void Menu::comprarParceladoNoCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "           COMPRA PARCELADA NO CARTÃO              " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    if (!cliente->temCartao())
    {
        cout << "\nCliente não possui cartão de crédito." << endl;
        return;
    }

    cout << "Limite disponível: R$" << fixed << setprecision(2) << cliente->getCartao()->getLimiteDisponivel() << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string descricao;
    cout << "Descrição da compra: ";
    getline(cin, descricao);

    double valor;
    cout << "Valor total: R$";
    while (true)
    {
        if ((cin >> valor) && valor > 0) break;
        cout << "Valor inválido! Digite novamente: R$";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int parcelas;
    cout << "Número de parcelas: ";
    while (true)
    {
        if ((cin >> parcelas) && parcelas >= 2 && parcelas <= 24) break;
        cout << "Inválido! Entre 2 e 24 parcelas: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    controller.comprarParceladoNoCartao(cliente, valor, parcelas, descricao);
}

// exibe a fatura do cartão
void Menu::exibirFaturaCartao(Controller &controller)
{
    system("clear");

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    controller.exibirFaturaCartao(cliente);
}

// pagar a fatura do cartão
void Menu::pagarFaturaCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "              PAGAMENTO DE FATURA                  " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    if (!cliente->temCartao())
    {
        cout << "\nCliente não possui cartão de crédito." << endl;
        return;
    }

    // mostra a fatura antes de pagar
    cliente->getCartao()->exibirFatura();

    cout << "Saldo atual: R$" << fixed << setprecision(2)
         << cliente->getSaldo() << endl;

    cout << "\nConfirmar pagamento da fatura? (1-Sim / 0-Não): ";
    int op;
    cin >> op;
    if (op != 1) return;

    controller.pagarFaturaCartao(cliente);
}

// bloqueia o cartão
void Menu::bloquearCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "              BLOQUEAR CARTÃO                      " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    controller.bloquearCartao(cliente);
}

// desbloqueia o cartão
void Menu::desbloquearCartao(Controller &controller)
{
    system("clear");
    cout << "===================================================" << endl;
    cout << "              DESBLOQUEAR CARTÃO                   " << endl;
    cout << "===================================================" << endl;

    Cliente* cliente = nullptr;
    if (!autenticarCliente(controller, cliente)) return;

    controller.desbloquearCartao(cliente);
}