[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/H41-Sye0)
# Atividade: A Conjectura de Collatz

## Descrição

A Conjectura de Collatz (também conhecida como o problema 3n + 1) é um dos problemas mais famosos da matemática. Ela define uma sequência de números gerada pelas seguintes regras:

Dado um número inteiro positivo $n$:
* Se $n$ é **par**, o próximo número é $n / 2$.
* Se $n$ é **ímpar**, o próximo número é $3n + 1$.
* O processo se repete até que $n$ seja igual a **1**.

Por exemplo, começando com $n = 6$:
* $6$ (par) $\to 3$
* $3$ (ímpar) $\to 10$
* $10$ (par) $\to 5$
* $5$ (ímpar) $\to 16$
* $16$ (par) $\to 8$
* $8$ (par) $\to 4$
* $4$ (par) $\to 2$
* $2$ (par) $\to 1$ (Fim)

A sequência foi: `6, 3, 10, 5, 16, 8, 4, 2, 1`.
* **Comprimento da trajetória:** 8 passos (transições).
* **Valor máximo atingido:** 16.

---

## O que você deve implementar

Edite o arquivo `src/Collatz.hs`.

### 1. Função Pura: `analisaTrajetoria`

```haskell
analisaTrajetoria :: Integer -> (Int, Integer)
analisaTrajetoria n = ...
````

  * Esta função deve receber um número inicial `n` e retornar uma tupla `(passos, maximo)`.
  * `passos`: O número de transições necessárias para chegar a 1.
  * `maximo`: O maior valor encontrado em toda a sequência (incluindo o valor inicial).
  * **Pré-condição:** $n > 0$. Se $n = 1$, o resultado deve ser `(0, 1)`.
  * **Dica:** Use uma função auxiliar recursiva (de preferência com acumuladores) para percorrer a sequência mantendo a contagem de passos e o máximo atual.

### 2\. Ação de E/S: `main`

```haskell
main :: IO ()
main = ...
```

  * Solicite um número inteiro positivo ao usuário: `"Digite um numero positivo: "`.
  * Valide a entrada. Se o número for $\le 0$, exiba `"Entrada invalida"`.
  * Se válido, chame `analisaTrajetoria` e exiba os resultados formatados:
      * `"Passos ate 1: X"`
      * `"Valor maximo: Y"`

-----

## Exemplos de Execução

**Exemplo 1: Número 6**

```shellsession
Digite um numero positivo: 6
Passos ate 1: 8
Valor maximo: 16
```

**Exemplo 2: Número 1 (Caso Base)**

```shellsession
Digite um numero positivo: 1
Passos ate 1: 0
Valor maximo: 1
```

**Exemplo 3: Número 27 (Sequência Longa)**
*O número 27 é famoso por demorar muito a convergir.*

```shellsession
Digite um numero positivo: 27
Passos ate 1: 111
Valor maximo: 9232
```

**Exemplo 4: Entrada Inválida**

```shellsession
Digite um numero positivo: 0
Entrada invalida
```

-----

## Testes

Compile, execute e teste o projeto com:

```shellsession
$ cabal build                    # Compila o projeto
$ cabal repl collatz-conjecture  # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run collatz              # Executa o programa
$ cabal test                     # Executa os testes de verificação automática
```
