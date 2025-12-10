[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/GHHhi0Wh)
# Tarefa: Gestão de Overbooking

## Descrição

A companhia aérea "Rotten Cocoa Airlines Corp." precisa de um sistema de gestão de check-ins para identificar e contabilizar situações de overbooking.

O programa deve primeiro solicitar ao usuário a quantidade total de voos a serem processados. Em seguida, para cada um desses voos, o programa deve solicitar dois valores inteiros: a capacidade da aeronave e a quantidade de passagens vendidas.

Durante a entrada de dados, se for detectado que um voo tem mais passagens vendidas do que a sua capacidade, um alerta de overbooking deve ser emitido imediatamente para aquele voo, no formato "Alerta: Voo com overbooking!".

Após o processamento de todos os voos, o programa deve exibir um relatório final contendo:
1.  O número total de voos que tiveram overbooking.
2.  O número total de passageiros que excederam a capacidade somando todos os voos com overbooking.

## Funções e Ações a Implementar

A implementação deve ser feita nos arquivos de origem (`src/*.hs`). A abordagem recomendada é o uso de uma ação de E/S recursiva que utiliza acumuladores para manter o estado da contagem.

1.  **`loopProcessaVoos :: Int -> Int -> Int -> Int -> IO ()`** (Sugestão de Ação Recursiva)
    * Esta é uma **ação de E/S recursiva** que pode ser o coração do seu programa. Ela pode receber como argumentos:
        1.  O número do voo atual (para exibição, ex: "Voo 1:", "Voo 2:").
        2.  O número total de voos a processar.
        3.  Um acumulador para a contagem de voos com overbooking.
        4.  Um acumulador para a contagem total de passageiros excedentes.
    * O **caso base** da recursão ocorre quando o número do voo atual ultrapassa o total de voos. Neste ponto, a ação deve imprimir o relatório final.
    * O **caso recursivo** deve processar um voo, imprimir o alerta se necessário, e chamar a si mesma com os valores atualizados.

2.  **`main :: IO ()`**
    * Esta é a **ação de E/S** principal.
    * Ela deve solicitar e ler a quantidade total de voos.
    * Em seguida, deve fazer a chamada inicial para a ação recursiva `loopProcessaVoos`, passando os valores iniciais (ex: `loopProcessaVoos 1 n 0 0`, onde `n` é a quantidade de voos).

## Exemplos de Execução

Sua resposta deve conter as mensagens exatamente como definidas nos exemplos de execução.

**Exemplo 1:**
```shellsession
Rotten Cocoa Airlines Corp.
Informe a quantidade de voos: 2
Voo 1:
Capacidade da aeronave: 560
Quantidade de passagens: 550
Voo 2:
Capacidade da aeronave: 350
Quantidade de passagens: 400
Alerta: Voo com overbooking!
Fim da entrada dos voos:
Ocorreram 1 voos com overbooking
Ocorreram 50 passageiros acima da capacidade
```

**Exemplo 2:**
```shellsession
Rotten Cocoa Airlines Corp.
Informe a quantidade de voos: 4
Voo 1:
Capacidade da aeronave: 100
Quantidade de passagens: 99
Voo 2:
Capacidade da aeronave: 100
Quantidade de passagens: 100
Voo 3:
Capacidade da aeronave: 100
Quantidade de passagens: 101
Alerta: Voo com overbooking!
Voo 4:
Capacidade da aeronave: 100
Quantidade de passagens: 102
Alerta: Voo com overbooking!
Fim da entrada dos voos:
Ocorreram 2 voos com overbooking
Ocorreram 3 passageiros acima da capacidade
```

---

## Desenvolvimento e Testes

Complete as definições para resolver o problema proposto.

```shellsession
$ cabal build             # Compila o projeto
$ cabal repl overbooking  # Carrega o projeto no REPL
$ cabal run overbooking   # Executa o programa
$ cabal test              # Executa os testes
```
