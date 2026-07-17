# Trabalho Prático II - Ordenação Externa

Este repositório contém a implementação do Trabalho Prático II da disciplina de **Estruturas de Dados II (BCC203)** da **Universidade Federal de Ouro Preto (UFOP)**.

O objetivo principal deste projeto é implementar e analisar o desempenho de diferentes algoritmos de ordenação externa, lidando com um grande volume de dados (registros de alunos) que não cabem inteiramente na memória principal.

## Algoritmos Implementados

Foram desenvolvidos três métodos principais para a ordenação dos dados no disco:

1. **Intercalação Balanceada (Ordenação Interna):** Lê blocos de registros do tamanho limite da memória, ordena-os e os distribui em fitas magnéticas simuladas. Em seguida, realiza a intercalação desses blocos até que o arquivo esteja completamente ordenado.
2. **Intercalação Balanceada (Seleção por Substituição):** Utiliza uma estrutura de *Heap* (Fila de Prioridades) para gerar blocos ordenados iniciais maiores do que o limite da memória, otimizando e reduzindo a quantidade de passadas necessárias na etapa de intercalação.
3. **Quicksort Externo:** Adaptação do clássico algoritmo Quicksort para manipular os dados e os pivôs lendo e escrevendo diretamente no disco, mantendo apenas uma área mínima de trabalho na memória RAM.

## Estrutura do Projeto

A organização dos diretórios do repositório é a seguinte:

* `src/`: Arquivos de código-fonte (`.cpp`).
* `include/`: Arquivos de cabeçalho (`.h`).
* `obj/`: Diretório de saída para os arquivos objeto compilados (`.o`).
* `bin/`: Diretório onde o executável final (`ordena`) é gerado.
* `fitas/`: Diretório gerado e gerenciado automaticamente durante a execução para armazenar as fitas temporárias e o arquivo final gerado (`ordenado.bin`).
* `data/`: Diretório para arquivos auxiliares de dados.
* `PROVAO.TXT`: Base de dados original contendo os registros a serem ordenados (deve ficar na raiz).

---

## Compilação

O projeto conta com um `Makefile` configurado para automatizar a compilação e execução. Certifique-se de ter o compilador `g++` e a ferramenta `make` instalados no seu ambiente (Linux ou WSL).

No terminal, na raiz do projeto, você pode usar os seguintes comandos:

* `make` *(ou `make all`)*: Compila todos os arquivos e gera o executável final.
* `make clean`: Remove arquivos binários, objetos compilados e apaga o conteúdo gerado na pasta de fitas temporárias.
* `make rebuild`: Limpa todo o lixo de compilações anteriores e recompila o projeto do zero.

---

## Execução

O `Makefile` permite que o programa seja executado com a passagem direta de parâmetros de forma simplificada.

**Sintaxe de execução:**
```bash
make run METODO=<valor> QTD=<valor> SIT=<valor> FLAG=<-P>
```

Obs: a flag -P é opcional, ela serve apenas para que os dados dos 
alunos a serem ordenados e o resultado da ordenação realizada sejam apresentados na tela.

---

## Autores
- Gabriel Canuto
- João Pedro Seabra
- Lara de Andrade
- Luiz Felipe Bento
- Maria Eduarda de Carvalho
- Maurício Rodrigues