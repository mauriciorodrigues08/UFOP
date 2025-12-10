[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Lx1cmjBp)
# Atividade: Simulador de Crescimento Populacional

## Descrição

Um biólogo precisa de sua ajuda para modelar o crescimento de uma população de coelhos em uma reserva ambiental. O modelo leva em conta a população inicial, uma taxa de crescimento natural e uma "colheita" anual (remoção de animais para controle ou migração).

Você deve implementar um programa em Haskell que calcule o tamanho da população após um determinado número de anos.

### O Modelo Matemático

A população no ano $N$ ($P_N$) é definida recursivamente em função da população do ano anterior ($P_{N-1}$):

1.  **Ano 0:** A população é a população inicial ($P_0$).
2.  **Ano N:**
    $$P_N = \lfloor P_{N-1} \times (1 + \text{taxa}) \rfloor - \text{colheita}$$

**Regras Importantes:**
* **Arredondamento:** Como não existem "meios coelhos", o resultado do crescimento ($P_{N-1} \times (1 + \text{taxa})$) deve ser arredondado para baixo (função `floor`) antes de subtrair a colheita.
* **Extinção:** Se em qualquer momento o cálculo resultar em um número negativo, a população deve ser considerada **0** (extinção). Uma população de 0 coelhos permanece 0 para sempre.

---

## O que você deve implementar

Edite o arquivo `src/Simulador.hs`.

### 1. Função Pura: `simulaPopulacao`

```haskell
simulaPopulacao :: Integer -> Double -> Integer -> Integer -> Integer
simulaPopulacao popInicial taxa colheita anos = ...
````

  * Esta função deve ser **recursiva** (ou usar uma função auxiliar recursiva).
  * **Dica:** Para eficiência e para evitar estouro de pilha em simulações longas, tente usar recursividade de cauda (com um acumulador ou passando o estado atual para a próxima chamada).

### 2\. Ação de E/S: `main`

```haskell
main :: IO ()
main = ...
```

  * O programa deve solicitar ao usuário, linha a linha:
    1.  População inicial (Inteiro)
    2.  Taxa de crescimento (Decimal, ex: 0.1 para 10%)
    3.  Colheita anual (Inteiro)
    4.  Número de anos (Inteiro)
  * **Validação:** Se a `popInicial` ou o número de `anos` forem negativos, exiba a mensagem `"Entrada invalida"`.
  * Se os dados forem válidos, chame a função `simulaPopulacao` e exiba o resultado no formato: `"Populacao final: X coelhos"`.

-----

## Exemplos de Execução

**Exemplo 1: Simulação Simples**

  * Início: 100 coelhos
  * Taxa: 0.1 (10%)
  * Colheita: 5 coelhos
  * Anos: 2
  * *Cálculo:*
      * Ano 1: floor(100 \* 1.1) - 5 = 110 - 5 = 105
      * Ano 2: floor(105 \* 1.1) - 5 = 115 - 5 = 110

<!-- end list -->

```shellsession
Populacao inicial: 100
Taxa de crescimento (ex: 0.1): 0.1
Colheita anual: 5
Anos a simular: 2
Populacao final: 110 coelhos
```

**Exemplo 2: Extinção**

  * Início: 10
  * Taxa: 0.5 (50%)
  * Colheita: 20
  * Anos: 3
  * *Cálculo:* Ano 1 resulta em 15 - 20 = -5 -\> **0**. Ano 2 e 3 continuam 0.

<!-- end list -->

```shellsession
Populacao inicial: 10
Taxa de crescimento (ex: 0.1): 0.5
Colheita anual: 20
Anos a simular: 3
Populacao final: 0 coelhos
```

**Exemplo 3: Entrada Inválida**

```shellsession
Populacao inicial: 100
Taxa de crescimento (ex: 0.1): 0.1
Colheita anual: 5
Anos a simular: -1
Entrada invalida
```

-----

## Testes

Compile, execute e teste o projeto com:

```shellsession
$ cabal build                          # Compila o projeto
$ cabal repl crescimento-populacional  # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run simulador                  # Executa o programa
$ cabal test                           # Executa os testes de verificação automática
```
