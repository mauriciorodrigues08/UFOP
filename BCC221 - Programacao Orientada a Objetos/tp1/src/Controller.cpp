// imports
#include "../imports/Controller.h"
#include "../imports/CartaoDeCredito.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// defines
#define ENVIOU 0
#define RECEBEU 1

// destrutor — libera toda memória alocada com new
Controller::~Controller()
{
    // libera as transações de cada cliente, depois o próprio cliente
    for(int i = 0; i < (int)clientes.size(); i++)
    {
        vector<Transacao*> extrato = clientes[i]->getTranscoes();
        for(int j = 0; j < (int)extrato.size(); j++)
        {
            delete extrato[j];
        }
        // libera o cartão se existir
        if (clientes[i]->temCartao())
            delete clientes[i]->getCartao();
        delete clientes[i];
    }

    // libera os gerentes (clientes já foram deletados acima)
    for(int i = 0; i < (int)gerentes.size(); i++)
    {
        delete gerentes[i];
    }
}

// cadastrar Clientes
void Controller::cadastrarCliente(Cliente &_novoCliente)
{
    // gera e atribui o número de conta antes de inserir
    _novoCliente.setNumeroDeConta(gerarNumeroDeConta());

    //adiciona o novo cliente na lista
    clientes.push_back(&_novoCliente);

    // notifica sucesso
    cout << "\nConta de titular " << _novoCliente.getNome() << " cadastrada com sucesso!" << endl;
    cout << "Número de conta: " << _novoCliente.getNumeroDeConta() << endl;
}

// cadastrar gerente
void Controller::cadastrarGerente(Gerente &_novoGerente)
{
    // adiciona o novo Gerente na lista
    gerentes.push_back(&_novoGerente);
    
    // notifica sucesso
    cout << "\nGerente  " << _novoGerente.getNome() << " cadastrado com sucesso!\n" << endl;
}

// retorna o próximo número de conta e incrementa o valor
int Controller::gerarNumeroDeConta()
{
    return proxNumeroDeConta++;
}

// visualizar (sobrecarga para cliente)
void Controller::visualizar(Cliente &_cliente)
{
    cout << "- DADOS DO CLIENTE -" << endl;
    cout << "Login: " << _cliente.getLogin() << endl;
    cout << "Nome: " << _cliente.getNome() << endl;
    cout << "Trabalho: " << _cliente.getTrabalho() << endl;
    cout << "Data de Nascimento: " << _cliente.getDataDeNascimento() << endl;
    cout << "Tipo de Conta: " << _cliente.getTipoDeConta() << endl;
    cout << "Número de Conta: " << _cliente.getNumeroDeConta() << endl;
    cout << "Taxa de Rendimento: " << _cliente.getTaxaDeRendimento() << endl;
    cout << "Remuneração: R$" << _cliente.getRemuneracao() << endl;
    cout << "Saldo: R$" << _cliente.getSaldo() << endl;
    cout << "\n";
}

// visualizar (sobrecarga para gerente)
void Controller::visualizar(Gerente &_gerente)
{
    cout << "- DADOS DO GERENTE -" << endl;
    cout << "Login: " << _gerente.getLogin() << endl;
    cout << "Nome: " << _gerente.getNome() << endl;
    cout << "Data de Nascimento: " << _gerente.getDataDeNascimento() << endl;
    cout << "Trabalho: " << _gerente.getTrabalho() << endl;
    cout << "Clientes:" << endl;
    int tamanho = _gerente.getClientes().size();
    for(int i = 0; i < tamanho; i++)
    {
        cout << "\n";
        cout << "Cliente #" << i+1 << endl;
        cout << "Nome: " << _gerente.getClientes()[i]->getNome() << endl;
        cout << "Trabalho: " << _gerente.getClientes()[i]->getTrabalho() << endl;
        cout << "Tipo de Conta: " << _gerente.getClientes()[i]->getTipoDeConta() << endl;
    }
    cout << "\n";
}

// lista um cliente
void Controller::listarCliente(Cliente &cliente)
{
    cout << endl;
    visualizar(cliente);
}

// lista um gerente
void Controller::listarGerente(Gerente &gerente)
{
    cout << endl;
    visualizar(gerente);
}

// sacar valor
bool Controller::sacar(double _valor, Cliente* &cliente ,bool ehTransf)
{
    // verifica se o saldo é suficiente 
    if (_valor > cliente->getSaldo()) {
        // notifica erro
        cout << "\nErro! Saldo insuficiente!" << endl;
        return false;
    }

    // retira o valor do saldo
    cliente->setSaldo(cliente->getSaldo() - _valor);

    // notifica suceso, caso seja apenas saque
    if (!ehTransf)
    {
        adicionaAoExtrato(cliente, "Saque", _valor, {}, ENVIOU);
        cout << "\nSaque de R$" << _valor << " realizado com sucesso!" << endl;
    }

    return true;
}
    
// depositar valor
bool Controller::depositar(double _valor, Cliente* &cliente, bool ehTransf)
{
    // adiciona o valor ao saldo
    cliente->setSaldo(cliente->getSaldo() + _valor);

    // caso não seja uma transferência, notifica
    if (!ehTransf)
    {
        adicionaAoExtrato(cliente, "Depósito", _valor, {}, RECEBEU);
        cout << "\nDepósito de R$" << _valor << " realizado com sucesso!" << endl;
    }

    return true;
}

// realizar transferência
void Controller::transferir(Cliente* &_origem, Cliente* &_destino, double _valor)
{
    // tenta realizar o saque da conta de origem
    if (sacar(_valor, _origem, true))
    {
        // caso consiga, deposita na conta destino
        depositar(_valor, _destino, true);

        // adiciona a transação ao extrato dos clientes envolvidos
        adicionaAoExtrato(_origem, "Transação", _valor, {_destino}, ENVIOU);
        adicionaAoExtrato(_destino, "Transação", _valor, {_origem}, RECEBEU);

        // notifica sucesso
        cout << "\nTransferência de " << _origem->getNome() << " para " << _destino->getNome() << " no valor\nde R$" << _valor << " realizada com sucesso!" << endl;
    }

    // notificação de erro será feita pelo método sacar()
}

// busca uma conta pelo numero
bool Controller::buscaClientePorNumero(int _numeroDestino, Cliente* &cliente)
{
    int n = clientes.size();
    for(int i=0; i < n; i++)
    {
        // se encontrar uma conta com o número passado
        if (clientes[i]->getNumeroDeConta() == _numeroDestino) 
        {
            // salva os dados na variável de referência e retorna
            cliente = clientes[i];
            return true;
        }
    }

    // noifica erro
    cout << "\nErro! Cliente de número " << _numeroDestino << " não encontrado!" << endl;
    return false;
}

// busca um cliente pelo login (sobrecarga com retorno)
bool Controller::buscaClientePorLogin(string _login, Cliente* &cliente)
{
    for (Cliente* clienteAtual : clientes)
    {
        // se encontrar uma conta com o login passado, retorna true
        if (clienteAtual->getLogin() == _login)
        {
            // salva os dados na variável de referência e retorna
            cliente = clienteAtual;
            return true;
        }
    }

    // noifica erro
    cout << "\nErro! Cliente de login '" << _login << "' não encontrado!" << endl;
    return false;
}

// busca uma conta pelo login (sobrecarga sem retorno)
bool Controller::buscaClientePorLogin(string _login)
{
    for (Cliente* clienteAtual : clientes)
    {
        // se encontrar uma conta com o login passado, retorna true
        if (clienteAtual->getLogin() == _login) return true;
    }

    return false;
}

// busca uma gerente pelo login (sobrecarga com retorno)
bool Controller::buscaGerentePorLogin(string _login, Gerente* &gerente)
{
    for (Gerente* gerenteAtual : gerentes)
    {
        if (gerenteAtual->getLogin() == _login) 
        {
            // se encontrar um gerente com o login passado, retorna true
            gerente = gerenteAtual;
            return true;
        }
    }

    // noifica erro
    cout << "\nErro! Gerente de login '" << _login << "' não encontrado!" << endl;
    return false;
}

// busca um gerente por login (sobrecarga sem retorno)
bool Controller::buscaGerentePorLogin(string _login)
{
    for (Gerente* gerenteAtual : gerentes)
    {
        // se encontrar um gerente com o login passado, retorna true
        if (gerenteAtual->getLogin() == _login) return true;
    }

    return false;
}


// verifica se o login e senha correspondem (sobrecarga para Cliente)
bool Controller::verificaLogin(const Cliente &cliente, string _senha)
{
    return (cliente.getSenha() == _senha) ? true : false;
}

// verifica se o login e senha correspondem (sobrecarga para Gerente)
bool Controller::verificaLogin(const Gerente &gerente, string _senha)
{
    return (gerente.getSenha() == _senha) ? true : false;
}

// adiciona uma operação ao extrato
void Controller::adicionaAoExtrato(Cliente* &_cliente, string _tipo, double _valor, vector<Cliente*> _clientesEnvolvidos, int tag)
{
    // se enviou o valor, adiciona o valor como negativo na transação
    if (tag == ENVIOU) _valor *= -1;

    // instancia uma nova transação
    Transacao* transacao = new Transacao();
    
    // adiciona os atributos
    transacao->setTipo(_tipo);
    transacao->setValor(_valor);
    transacao->setClientesEnvolvidos(_clientesEnvolvidos);
    transacao->setData(obterDataAtual());
    transacao->setHorario(obterHorarioAtual());
    
    // insere a transação no extrato do cliente
    vector<Transacao*> extrato = _cliente->getTranscoes();
    extrato.push_back(transacao);
    _cliente->setTranscoes(extrato);
}

Data Controller::obterDataAtual()
{
    time_t agora = time(nullptr);
    tm* time = localtime(&agora);
 
    Data data;
    data.dia = time->tm_mday;
    data.mes = time->tm_mon + 1;   // tm_mon começa em 0
    data.ano = time->tm_year + 1900; // tm_year é anos desde 1900

    return data;
}

Horario Controller::obterHorarioAtual()
{
    time_t agora = time(nullptr);
    tm* time = localtime(&agora);
 
    Horario horario;
    horario.horas   = time->tm_hour;
    horario.minutos = time->tm_min;

    return horario;
}

// exibir extrato de um cliente
void Controller::exibirExtrato(Cliente &_cliente)
{
    vector<Transacao*> extrato = _cliente.getTranscoes();
    int tamanho = extrato.size();
    for(int i = 0; i < tamanho; i++)
    {
        cout << "\n-> Transação #" << i+1 << endl;
        extrato[i]->exibirTransacao();
        cout << endl;
    }
}

// associar gerente ao cliente
void Controller::associar(Gerente* &_gerente, Cliente* &_cliente)
{
    // pega o vetor de clientes atual daquele gerente
    vector<Cliente*> clientesAssociados = _gerente->getClientes();

    // adiciona o novo cliente no final
    clientesAssociados.push_back(_cliente);

    // salva novamente no gerente
    _gerente->setClientes(clientesAssociados);
}

// salvar dados    
void Controller::salvarCSV(const string nome_arq_clientes, const string nome_arq_gerentes)


{
    // SALVAR CLIENTES
    fstream arq_clientes;
    
    // abre o arquivo no final (se não existir, cria)
    arq_clientes.open(nome_arq_clientes, ios::out | ios::trunc);

    // verifica se o arquivo abriu
    if (!arq_clientes.is_open())
    {
        cerr << "Erro ao abrir o arquivo de clientes!" << endl;
        return;
    }

    // salva o prox numero de conta
    arq_clientes << proxNumeroDeConta << "\n";

    // salva os dados
    for(Cliente* cliente : clientes)
    {
        arq_clientes << cliente->getLogin() << ","
                        << cliente->getSenha() << ","
                        << cliente->getNome() << ","
                        << cliente->getTrabalho() << ","
                        << cliente->getRemuneracao() << ","
                        << cliente->getTipoDeConta() << ","
                        << cliente->getTaxaDeRendimento() << ","
                        << cliente->getDataDeNascimento() << ","
                        << cliente->getSaldo() << ","
                        << serializarTransacoes(cliente->getTranscoes()) << ","
                        << cliente->getNumeroDeConta() << ","
                        << serializarCartao(cliente) << "\n";
    }

    arq_clientes.close();
    cout << "Dados de Clientes salvos com sucesso!" << endl;

    // SALVAR GERENTES
    fstream arq_gerentes;

    // abre o arquivo no final (se não existir, cria)
    arq_gerentes.open(nome_arq_gerentes, ios::out | ios::trunc);

    // verifica se o arquivo abriu
    if (!arq_gerentes.is_open())
    {
        cerr << "Erro ao abrir o arquivo de gerentes!" << endl;
        return;
    }
    
    // salva os dados
    for(Gerente* gerente : gerentes)
    {
        arq_gerentes << gerente->getLogin() << ","
                        << gerente->getSenha() << ","
                        << gerente->getNome() << ","
                        << gerente->getTrabalho() << ","
                        << gerente->getDataDeNascimento() << ","
                        << serializarClientes(gerente->getClientes()) << "\n";
    }

    arq_gerentes.close();
    cout << "Dados de Gerentes salvos com sucesso!" << endl;
}

// carregar dados
void Controller::carregarCSV(const string nome_arq_clientes, const string nome_arq_gerentes)
{
    /*
    SEPARADORES:
    , -> separa as informações cliente/gerente no csv
    # -> separa o vetor de transações
    ; -> separa os campos de uma transação
    | -> separa o vetor de clientes do gerente
    */

    // LÊ OS CLIENTES
    // abre o arquivo de clientes
    ifstream arq_clientes(nome_arq_clientes);
    
    // caso o arquivo não exista, cria um novo vazio
    if (!arq_clientes.is_open()) 
    {
        ofstream novoArq(nome_arq_clientes);
        novoArq.close();
    }
    else
    {
        // pega o prox numero de conta    
        string proxNumContaString;
        if (!getline(arq_clientes, proxNumContaString) || proxNumContaString.empty())
        {
            proxNumeroDeConta = 1000;
        }
        else
        {
            // tenta converter o numero de conta, previnindo erro de leitura
            try 
            {
                proxNumeroDeConta = stoi(proxNumContaString);
            } 
            catch (const exception& e) 
            {
                proxNumeroDeConta = 1000;
            }
        }  
        
        // pega todas linhas do arquivo
        string linha;
        while (getline(arq_clientes, linha))
        {
            // verifica se o arquivo é vazio
            if (linha.empty()) continue;
    
            // tenta desserializar a linha, ignorando em caso de erro
            try 
            {
                // desserializa a linha lida
                vector<string> campos = split(linha, ',');
        
                // desserializa a data de nascimento
                vector<string> d = split(campos[7], '/');
                Data dataNasc = { stoi(d[0]), stoi(d[1]), stoi(d[2]) };
        
                // desserializa as transações
                vector<Transacao*> transacoes = deserializarTransacoes(campos[9]);
        
                // cria o novo Cliente que foi desserializado
                Cliente* novoCliente = new Cliente (
                    campos[0],          // login
                    campos[1],          // senha
                    campos[2],          // nome
                    campos[3],          // trabalho
                    stod(campos[4]),    // remuneracao
                    campos[5],          // tipoDeConta
                    stod(campos[6]),    // taxaDeRendimento
                    dataNasc,           // dataDeNascimento
                    stod(campos[8]),    // saldo
                    transacoes,         // transacoes
                    stoi(campos[10])    // numeroDeConta
                );
        
                // desserializa o cartão se existir (campo 11)
                if ((int)campos.size() > 11 && !campos[11].empty())
                {
                    CartaoDeCredito* cartao = deserializarCartao(campos[11]);
                    novoCliente->setCartao(cartao);
                }

                // adiciona ao vetor de clientes
                this->clientes.push_back(novoCliente);
            }
            catch (const exception& e)
            {
                // ignora a linha corrompida e avisa no console
                cerr << "Aviso: Linha corrompida ignorada em clientes.csv" << endl;
                continue;
            }
        }
    
        // fecha o arquivo de clientes
        arq_clientes.close();
    }


    // LÊ OS GERENTES
    // abre o arquivo de gerentes
    ifstream arq_gerentes(nome_arq_gerentes);

    // caso o arquivo não exista, cria um novo vazio
    if (!arq_gerentes.is_open()) 
    {
        ofstream novoArq(nome_arq_gerentes);
        novoArq.close();
    }
    else
    {
        // lê todas as linhas do arquivo de gerentes
        string linha;
        while (getline(arq_gerentes, linha))
        {
            // verifica se o arquivo é vazio
            if (linha.empty()) continue;
    
            // tenta desserializar a linha, ignorando em caso de erro
            try 
            {
                // deserializa a linha lida
                vector<string> campos = split(linha, ',');
        
                // desserializa a data de nascimento
                vector<string> d = split(campos[4], '/');
                Data dataNasc = { stoi(d[0]), stoi(d[1]), stoi(d[2]) };
        
                // vincula os clientes pelo numeroDeConta
                vector<Cliente*> clientesDoGerente;
                if (!campos[5].empty())
                {
                    vector<string> nums = split(campos[5], '|');
                    for (const string& num : nums)
                    {
                        int numeroConta = stoi(num);
                        for (Cliente* clienteAtual : this->clientes)
                        {
                            if (clienteAtual->getNumeroDeConta() == numeroConta)
                                clientesDoGerente.push_back(clienteAtual);
                        }
                    }
                }
        
                // cria o novo Gerente que foi desserializado
                Gerente* novoGerente = new Gerente(
                    campos[0],          // login
                    campos[1],          // senha
                    campos[2],          // nome
                    campos[3],          // trabalho
                    dataNasc,           // dataDeNascimento
                    clientesDoGerente   // clientes
                );
        
                // adiciona ao vetor de gerentes
                this->gerentes.push_back(novoGerente);
            }
            catch (const exception& e)
            {
                // ignora a linha corrompida e avisa no console
                cerr << "Aviso: Linha corrompida ignorada em gerentes.csv" << endl;
                continue;
            }
        }
    
        // fecha o arquivo de gerentes
        arq_gerentes.close();
    }
}


// serializa o cartão de crédito para csv
string Controller::serializarCartao(Cliente* cliente)
{
    // verifica se o cliente possui cartão
    if (!cliente->temCartao()) return "";

    // utiliza o stream de string para serializar
    ostringstream out;
    out << *cliente->getCartao();
    
    // retorna a string formatada
    return out.str();
}

// desserializa o cartão de crédito vindo do csv
CartaoDeCredito* Controller::deserializarCartao(const string& str)
{
    // separa os campos principais do cartão usando o ponto e vírgula
    vector<string> campos = split(str, ';');

    // converte os valores
    double limite           = stod(campos[0]);
    double limiteDisponivel = stod(campos[1]);
    double fatura           = stod(campos[2]);
    bool   bloqueado        = (campos[3] == "1");

    // instancia o novo cartão
    CartaoDeCredito* cartao = new CartaoDeCredito(limite);
    cartao->setLimiteDisponivel(limiteDisponivel);
    cartao->setFatura(fatura);
    cartao->setBloqueado(bloqueado);

    // verifica se existem parcelas pendentes
    if ((int)campos.size() > 4 && !campos[4].empty())
    {
        vector<Parcela> parcelas;
        
        // separa as parcelas usando a barra vertical
        vector<string> parcelasString = split(campos[4], '|');
        for (const string& parc : parcelasString)
        {
            // separa os atributos da parcela usando dois pontos
            vector<string> p = split(parc, ':');
            Parcela parcela;
            parcela.numero    = stoi(p[0]);
            parcela.total     = stoi(p[1]);
            parcela.valor     = stod(p[2]);
            parcela.descricao = p[3];
            
            // adiciona a parcela lida ao vetor
            parcelas.push_back(parcela);
        }
        
        // salva as parcelas no cartão
        cartao->setParcelas(parcelas);
    }

    // retorna o ponteiro do cartão montado
    return cartao;
}
string Controller::serializarTransacoes(const vector<Transacao*>& transacoes)
{
    /*
    o tipo ostringstream é um stream de escrita em memória
    
    funciona exatamente como ofstream (escrita em arquivo) ou cout (escrita no terminal)
    mas em vez de escrever em algum destino externo, escreve em uma string interna.

    útil porque ele é um ostream, assim não é necessário refazer todas as sobrecargas do cout
    */
    ostringstream out;

    int transacoesInseridas = 0;
    for (Transacao* transacao : transacoes)
    {
        if (transacoesInseridas > 0) out << "#"; // separador de transações -> #
        out << *transacao;
        transacoesInseridas++;
    }

    // retorna a saída como uma string
    return out.str();
}

// função auxiliar para serializar os clientes de um gerente
string Controller::serializarClientes(const vector<Cliente*>& clientes)
{
    ostringstream out;
    
    int clientesInseridos = 0;
    for (Cliente* cliente : clientes)
    {
        if (clientesInseridos > 0) out << "|"; // separador de clientes -> |
        out << cliente->getNumeroDeConta(); // envia apenas o número de conta de cada cliente para o CSV 
        clientesInseridos++;
    }

    // retorna a saída como uma string
    return out.str();
}

vector<string> Controller::split(const string& linha, char delimitador)
{
    vector<string> campos;
    istringstream ss(linha);
    string campo;

    // separa a linha pelo delimitador
    while (getline(ss, campo, delimitador))
        campos.push_back(campo);
    
    // retorna os campos da linha separados
    return campos;
}

Transacao* Controller::deserializarTransacao(const string& str)
{
    vector<string> campos = split(str, ';');
    // campos[0] = tipo
    // campos[1] = valor
    // campos[2] = data
    // campos[3] = horario
    // campos[4] = clientes (opcional)

    string tipo = campos[0];
    double valor = stod(campos[1]);

    // desserializa data (dd/mm/aaaa)
    vector<string> d = split(campos[2], '/');
    Data data = { stoi(d[0]), stoi(d[1]), stoi(d[2]) };

    // desserializa horario (hh:mm)
    vector<string> h = split(campos[3], ':');
    Horario horario = { stoi(h[0]), stoi(h[1]) };

    return new Transacao(tipo, valor, data, horario);
    // clientes envolvidos serão vinculados depois
}

vector<Transacao*> Controller::deserializarTransacoes(const string& str)
{
    vector<Transacao*> transacoes;
    if (str.empty()) return transacoes;

    vector<string> partes = split(str, '#');
    for (const string& parte : partes)
        transacoes.push_back(deserializarTransacao(parte));

    return transacoes;
}

void Controller::listarLogins()
{
    // Clientes
    cout << "> CLIENTES:" << endl;
    if(clientes.empty())
    {
        cout << "  Nenhum Cliente cadastrado até o momento!" << endl;
        cout << endl;
    }
    else
    {
        for (Cliente* clienteAtual : clientes)
        {
            cout << "  - " << clienteAtual->getLogin() << endl;
        }
        cout << endl;
    }
    
    // Gerentes
    cout << "> GERENTES:" << endl;
    if(gerentes.empty())
    {
        cout << "  Nenhum Gerente cadastrado até o momento!" << endl;
        cout << endl;
    }
    else
    {
        for (Gerente* gerenteAtual : gerentes)
        {
            cout << "  - " << gerenteAtual->getLogin() << endl;
        }
        cout << endl;
    }
}
// ─── CARTÃO DE CRÉDITO ───────────────────────────────────────────────────────

// cria cartão para o cliente com limite = 30% da remuneração
bool Controller::criarCartao(Cliente* &cliente)
{
    // verifica se já tem cartão
    if (cliente->temCartao())
    {
        cout << "\nErro! Cliente já possui um cartão de crédito." << endl;
        return false;
    }

    // define o limite como 30% da remuneração
    double limite = cliente->getRemuneracao() * 0.3;

    // cria e associa o cartão ao cliente
    CartaoDeCredito* cartao = new CartaoDeCredito(limite);
    cliente->setCartao(cartao);

    cout << "\nCartão de crédito criado com sucesso!" << endl;
    cout << "Limite: R$" << fixed << setprecision(2) << limite << endl;
    return true;
}

// altera o limite do cartão
bool Controller::alterarLimiteCartao(Cliente* &cliente, double novoLimite)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return false;
    }

    if (novoLimite <= 0)
    {
        cout << "\nErro! O limite deve ser maior que zero." << endl;
        return false;
    }

    CartaoDeCredito* cartao = cliente->getCartao();
    double limiteAntigo = cartao->getLimite();
    double diferenca    = novoLimite - limiteAntigo;

    cartao->setLimite(novoLimite);
    // ajusta o limite disponível proporcionalmente
    cartao->setLimiteDisponivel(cartao->getLimiteDisponivel() + diferenca);

    cout << "\nLimite alterado de R$" << fixed << setprecision(2) << limiteAntigo
         << " para R$" << novoLimite << " com sucesso!" << endl;
    return true;
}

// realiza compra simples no cartão
bool Controller::comprarNoCartao(Cliente* &cliente, double valor, string descricao)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return false;
    }
    return cliente->getCartao()->realizarCompra(valor, descricao);
}

// realiza compra parcelada no cartão
bool Controller::comprarParceladoNoCartao(Cliente* &cliente, double valor, int numParcelas, string descricao)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return false;
    }
    return cliente->getCartao()->realizarCompraParcelada(valor, numParcelas, descricao);
}

// paga a fatura — debita do saldo do cliente
bool Controller::pagarFaturaCartao(Cliente* &cliente)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return false;
    }

    CartaoDeCredito* cartao = cliente->getCartao();
    double valorFatura = cartao->getFatura();

    if (valorFatura <= 0.0)
    {
        cout << "\nFatura já está zerada." << endl;
        return true;
    }

    // verifica se o cliente tem saldo suficiente
    if (valorFatura > cliente->getSaldo())
    {
        cout << "\nErro! Saldo insuficiente para pagar a fatura." << endl;
        cout << "Saldo: R$" << fixed << setprecision(2) << cliente->getSaldo() << endl;
        cout << "Fatura: R$" << fixed << setprecision(2) << valorFatura << endl;
        return false;
    }

    // debita do saldo e paga a fatura
    cliente->setSaldo(cliente->getSaldo() - valorFatura);
    cartao->pagarFatura();

    // registra no extrato
    adicionaAoExtrato(cliente, "Pagamento Fatura", valorFatura, {}, ENVIOU);
    return true;
}

// exibe fatura do cartão
void Controller::exibirFaturaCartao(Cliente* &cliente)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return;
    }
    cliente->getCartao()->exibirFatura();
}

// bloqueia o cartão
void Controller::bloquearCartao(Cliente* &cliente)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return;
    }
    if (cliente->getCartao()->isBloqueado())
    {
        cout << "\nCartão já está bloqueado." << endl;
        return;
    }
    cliente->getCartao()->setBloqueado(true);
    cout << "\nCartão bloqueado com sucesso." << endl;
}

// desbloqueia o cartão
void Controller::desbloquearCartao(Cliente* &cliente)
{
    if (!cliente->temCartao())
    {
        cout << "\nErro! Cliente não possui cartão de crédito." << endl;
        return;
    }
    if (!cliente->getCartao()->isBloqueado())
    {
        cout << "\nCartão já está desbloqueado." << endl;
        return;
    }
    cliente->getCartao()->setBloqueado(false);
    cout << "\nCartão desbloqueado com sucesso." << endl;
}

// verifica uma associação
bool Controller::verificaAssociacao(const Gerente &gerente, int numeroDeConta, Cliente* &cliente)
{
    for(Cliente* clienteAtual : gerente.getClientes())
    {
        if (clienteAtual->getNumeroDeConta() == numeroDeConta) 
        {
            cliente = clienteAtual;
            return true;
        }
    }

    return false;
}
