using namespace std;

// imports
#include "../imports/Transacao.h"
#include "../imports/Cliente.h"

// CONSTRUTOR
Transacao::Transacao(
    string _tipo,
    double _valor,
    Data _data,
    Horario _horario,
    vector<Cliente*> _clientesEnvolvidos
)
{
    this->tipo = _tipo;
    this->valor = _valor;
    this->data = _data;
    this->horario = _horario;
    this->clientesEnvolvidos = _clientesEnvolvidos;
}

// GETTERS
string Transacao::getTipo() const
{
    return this->tipo;
}

double Transacao::getValor() const
{
    return this->valor;
}

Data Transacao::getData() const
{
    return this->data;
}

Horario Transacao::getHorario() const
{
    return this->horario;
}

vector<Cliente*> Transacao::getClientesEnvolvidos() const
{
    return this->clientesEnvolvidos;
}


// SETTERS
void Transacao::setTipo(string _tipo)
{
    this->tipo = _tipo;
}

void Transacao::setValor(double _valor)
{
    this->valor = _valor;
}

void Transacao::setData(Data _data)
{
    this->data = _data;
}

void Transacao::setHorario(Horario _horario)
{
    this->horario = _horario;
}

void Transacao::setClientesEnvolvidos(vector<Cliente*> _clientesEnvolvidos)
{
    this->clientesEnvolvidos = _clientesEnvolvidos;
}


// MÉTODOS
void Transacao::exibirTransacao()
{
    cout << "Tipo: " << getTipo() << endl;
    cout << "Valor: R$" << getValor() << endl;
    cout << "Data: " << getData() << endl;
    cout << "Horário: " << getHorario() << endl;
    cout << "Clientes envolvidos: ";
    if (getClientesEnvolvidos().size() > 0)
    { 
        cout << "\n";
        int tam = getClientesEnvolvidos().size();
        for (int i=0; i<tam; i++)
        {
            cout << "  " << i+1 << "." << endl;
            cout << "  " << "Nome: " << getClientesEnvolvidos()[i]->getNome() << endl;
            cout << "  " << "Número de Conta: " << getClientesEnvolvidos()[i]->getNumeroDeConta() << endl;
        }
    }
    else
    {
        cout << "-" << endl;
    }
}

// SOBRECARGA DE OPERADORES
/*
Separadores:
; -> separador para os atributos da transação
| -> separador para o numero de conta dos clientes envolvidos
*/
ostream& operator<<(std::ostream& os, const Transacao& transacao)
{
    os << transacao.tipo << ";"
       << transacao.valor << ";"
       << transacao.data << ";"
       << transacao.horario;

    // serializa os clientes envolvidos pelos logins
    vector<Cliente*> clientesEnvolvidos = transacao.getClientesEnvolvidos();
    int qtdInseridos = 0;

    // caso exista pessoas envolvidas, precisa colocar mais um ';' para separar do horario
    if(clientesEnvolvidos.size() > 0) os << ";";

    for(Cliente* cliente : clientesEnvolvidos)
    {
        if (qtdInseridos > 0) os << "|";
        os << cliente->getNome();
        qtdInseridos++;
    }

    return os;
}
