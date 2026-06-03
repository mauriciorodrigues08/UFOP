# Sistema de Gerenciamento de Banco

Trabalho Prático — BCC 221 Programação Orientada a Objetos (POO)

---

## Descrição

Sistema em C++ que simula a gestão de um banco, permitindo o cadastro e gerenciamento de clientes e gerentes, realização de transações (depósito, saque e transferência), controle de conta poupança com rendimentos e cartão de crédito com fatura e parcelamento. Os dados são persistidos automaticamente em arquivos CSV.

---

## Estrutura de Diretórios

```
.
├── main.cpp
├── Makefile
├── imports/          # Arquivos de cabeçalho (.h)
│   ├── Pessoa.h
│   ├── Cliente.h
│   ├── Gerente.h
│   ├── Transacao.h
│   ├── CartaoDeCredito.h
│   ├── Controller.h
│   ├── Menu.h
│   ├── Data.h
│   └── Horario.h
├── src/              # Implementações (.cpp)
│   ├── Pessoa.cpp
│   ├── Cliente.cpp
│   ├── Gerente.cpp
│   ├── Transacao.cpp
│   ├── CartaoDeCredito.cpp
│   ├── Controller.cpp
│   ├── Menu.cpp
│   ├── Data.cpp
│   └── Horario.cpp
└── build/            # Objetos compilados (gerado automaticamente)
```

---

## Pré-requisitos

- Compilador `g++` com suporte a **C++17** ou superior
- `make`
- Sistema operacional Linux, macOS ou Windows com WSL/MinGW

Para verificar se os pré-requisitos estão instalados:

```bash
g++ --version
make --version
```

---

## Compilação

### Compilar o projeto

```bash
make
```

O executável `exe` será gerado na raiz do projeto.

### Compilar e executar diretamente

```bash
make run
```

### Limpar arquivos gerados

```bash
make clean
```

---

## Execução

Após compilar, execute:

```bash
./exe
```

O sistema iniciará com o menu principal no terminal.

---

## Uso

Ao iniciar o programa, o sistema carrega automaticamente os dados de `clientes.csv` e `gerentes.csv` (se existirem). O menu principal oferece as seguintes opções:

```
===================================================
         SISTEMA DE GERENCIAMENTO DE BANCO         
===================================================
  1. Cadastrar
  2. Operações bancárias
  3. Consultas
  4. Associar gerente a um cliente
  5. Listar logins cadastrados
  6. Cartão de crédito
  0. Salvar dados e Sair
===================================================
```

### Cadastros

- **Cadastrar Cliente:** Cadastra um novo Cliente. Informe nome, login, senha, data de nascimento, trabalho, remuneração e tipo de conta (corrente ou poupança). Contas poupança recebem uma taxa de rendimento.
- **Cadastrar Gerente:** Cadastra um novo Gerente. Informe nome, login, senha, trabalho e data de nascimento.

### Operações

- **Depósito:** Realiza uma operação de Depósito. Realize o login do cliente e informe o valor a depositar.
- **Saque:** Realiza uma operação de Saque. Realize o login do cliente e informe o valor a sacar.
- **Transferência:** Realiza uma operação de transação. Realize o login de origem, informe o número de conta do destino e o valor.

### Consultas

- **Extrato:** Exibe todas as transações de um cliente.
- **Listar Cliente:** Exibe os dados completos de um cliente.
- **Listar Gerente:** Exibe os dados do gerente e seus clientes vinculados.

### Associação
- **Associar gerente a cliente:** Vincula um gerente a um cliente.

### Listar
- **Listar logins:** Exibe todos os logins cadastrados (clientes e gerentes).

### Cartão de Crédito (tarefa extra)

Acessível pelo submenu de Cartão de Crédito:

| Opção | Descrição |
|---|---|
| Criar cartão | Cria cartão com limite de 30% da remuneração do cliente |
| Alterar limite | Redefine o limite do cartão |
| Compra simples | Realiza uma compra à vista |
| Compra parcelada | Realiza uma compra em N parcelas |
| Pagar fatura | Debita o valor da fatura do saldo do cliente |
| Exibir fatura | Mostra todas as compras e o total da fatura |
| Bloquear cartão | Bloqueia o cartão para novas compras |
| Desbloquear cartão | Reativa o cartão |

### Persistência de Dados

- **Salvar:** Grava o estado atual em `clientes.csv` e `gerentes.csv`.
- **Carregar:** Lê os arquivos CSV e restaura todos os dados da sessão anterior.
- Os arquivos são carregados automaticamente na inicialização do programa, caso existam.

---

## Funcionalidades Implementadas

- [x] Cadastro de clientes e gerentes com login e senha
- [x] Operações: depósito, saque e transferência
- [x] Conta poupança com taxa de rendimento
- [x] Extrato com data, horário e clientes envolvidos
- [x] Associação de gerente a cliente
- [x] Listagem de clientes e gerentes
- [x] Persistência em arquivos CSV
- [x] Cartão de crédito com limite, fatura, parcelamento e bloqueio

---

## Observações

- Logins devem ser únicos entre todos os usuários do sistema.
- O número de conta é gerado automaticamente a partir de 1000.
- O rendimento da conta poupança é aplicado a cada vez que o sistema é acionado (ou seja, a cada execução).
- Os arquivos `clientes.csv` e `gerentes.csv` são criados/sobrescritos na raiz do projeto ao salvar.

---

## Autores
- Gabriel Canuto
- João Pedro Seabra
- Lara de Andrade
- Luiz Felipe Bento
- Maurício Rodrigues