[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/LhwY8P_h)
# Atividade: Urna Eletrônica

## Descrição

Nesta atividade, você desenvolverá um programa interativo em Haskell que simula o funcionamento básico de uma **Urna Eletrônica**. O programa deve coletar votos sequencialmente até que um comando de encerramento seja acionado, momento em que exibirá o boletim de urna com os totais.

Esta atividade exercita os conceitos de:
* **Ações de E/S Recursivas:** Para manter o ciclo de votação ativo.
* **Acumuladores:** Para manter o estado da contagem de votos (passagem de parâmetros na recursão).
* **Condicionais:** Para processar os diferentes códigos de voto.

## Cenário

Está ocorrendo uma eleição para escolher o mascote do Laboratório de Programação Funcional. Os candidatos são:

* **1**: Lambda
* **2**: Monad
* **3**: Curry

## Especificação do Fluxo

1.  O programa deve iniciar exibindo um menu com as opções de candidatos.
2.  O programa entra em um **ciclo de leitura de votos**.
3.  A cada iteração, o programa solicita que o eleitor digite o número do seu voto.
4.  O comportamento deve seguir a tabela abaixo:

| Entrada | Ação do Sistema |
| :---: | :--- |
| `1` | Computa +1 voto para o candidato **Lambda** e reinicia o ciclo. |
| `2` | Computa +1 voto para o candidato **Monad** e reinicia o ciclo. |
| `3` | Computa +1 voto para o candidato **Curry** e reinicia o ciclo. |
| `0` | **Encerra a votação** e exibe o relatório final. |
| *Outro* | Qualquer outro número é considerado **Voto Nulo**. Computa +1 nulo e reinicia. |

5.  Ao receber o código `0`, o programa deve encerrar o laço e imprimir o relatório final contendo:
    * Total de votos para cada candidato.
    * Total de votos nulos.
    * Total geral de votos computados.

## Requisitos de Implementação

Você deve implementar a lógica no arquivo `src/Urna.hs`.

* Recomenda-se criar uma função auxiliar recursiva (ex: `computaVotos`) que receba como argumentos os contadores atuais de cada opção.
    * *Dica:* Sua função recursiva precisará de pelo menos 4 argumentos acumuladores (um para cada candidato e um para os nulos).
* A função `main` deve configurar o buffering de saída e iniciar o processo com os contadores zerados.

## Exemplo de Execução

```shellsession
=== Urna Eletronica ===
Opcoes: [1] Lambda | [2] Monad | [3] Curry | [0] Encerrar

Digite o voto: 1
Voto computado para Lambda.

Digite o voto: 3
Voto computado para Curry.

Digite o voto: 5
Voto Nulo computado.

Digite o voto: 1
Voto computado para Lambda.

Digite o voto: 0

=== Boletim de Urna ===
Lambda: 2
Monad:  0
Curry:  1
Nulos:  1
-----------------------
Total:  4
````

## Testes

Compile, execute e teste o projeto com:

```shellsession
$ cabal build                 # Compila o projeto
$ cabal repl urna-eletronica  # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run                   # Executa o programa
$ cabal test                  # Executa os testes de verificação automática
```
