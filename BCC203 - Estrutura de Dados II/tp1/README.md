# TP01 — Pesquisa Externa

Trabalho Prático de Estrutura de Dados II que implementa e compara estruturas de dados para **pesquisa externa**, ou seja, busca em grandes volumes de dados armazenados em disco. O projeto implementa três estruturas clássicas — Árvore B*, Árvore Binária e Árvore B — além de um módulo ASI (Arquivo Sequencial Indexado) e um gerador de dados para testes.

---

## Estruturas implementadas

| Estrutura | Arquivos |
|---|---|
| Árvore B* | `src/arvore_b_estrela.cpp`, `imports/arvore_b_estrela.h` |
| Árvore Binária | `src/arvore_binaria.cpp`, `imports/arvore_binaria.h` |
| Árvore B | `src/arvoreb.cpp`, `imports/arvoreb.h` |
| Arquivo Sequencial Indexado (ASI) | `src/asi.cpp`, `imports/asi.h` |
| Gerador de dados | `gerador/gerador.cpp`, `gerador/gerador.h` |

---

## Estrutura do projeto

```
TP1/
├── imports/             # Headers (.h) compartilhados
│   ├── arvore_b_estrela.h
│   ├── arvore_binaria.h
│   ├── arvoreb.h
│   ├── asi.h
│   └── registro.h
├── src/                 # Implementações das estruturas
│   ├── arvore_b_estrela.cpp
│   ├── arvore_binaria.cpp
│   ├── arvoreb.cpp
│   └── asi.cpp
├── gerador/             # Gerador de dados
│   ├── gerador.cpp
│   └── gerador.h
├── main.cpp             # Ponto de entrada do programa
├── Makefile
└── README.md
```

---

## Pré-requisitos

- Compilador `g++` com suporte a **C++17** ou superior
- `make`

### Linux/WSL
```bash
sudo apt update && sudo apt install g++ make
```

### Windows (MinGW)
Instale o [MinGW-w64](https://www.mingw-w64.org/) e certifique-se de que `g++` e `make` estão no PATH.

---

## Compilação

Na raiz do projeto, execute:

```bash
make
```

Isso compila todos os módulos e gera o executável `pesquisa.exe` na raiz do projeto.
```

---

## Execução

Após compilar, execute:

```bash
# Linux/WSL
./pesquisa <metodo> <quantidade> <situacao> <chave>
./pesquisa <metodo> <quantidade> <situacao> <chave> [-P] #Execução detalhada

# Windows
pesquisa.exe <metodo> <quantidade> <situacao> <chave>
pesquisa.exe <metodo> <quantidade> <situacao> <chave> [-P] #Execução detalhada
```

## Autores
- Gabriel Canuto
- João Pedro Seabra
- Lara de Andrade
- Luiz Felipe Bento
- Maria Eduarda de Carvalho
- Maurício Rodrigues
