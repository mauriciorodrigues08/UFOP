[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/r2gT07FY)
# Tarefa: Calculadora RPN Segura

## Descrição

Nesta atividade, você implementará um avaliador de expressões matemáticas que utiliza a **Notação Polonesa Reversa** (RPN - *Reverse Polish Notation*).

Diferente da notação tradicional ("infixa") que usamos na escola (ex: `3 + 4`), a RPN coloca o operador **depois** dos números (ex: `3 4 +`). Isso elimina a necessidade de parênteses e facilita a avaliação computacional usando uma estrutura de dados chamada **Pilha**.

### O que é e como funciona a RPN?

Imagine uma pilha de pratos. Você só pode colocar um prato no topo (`push`) ou tirar um do topo (`pop`). A calculadora RPN funciona assim:

1.  Lemos a expressão da esquerda para a direita, item por item.
2.  Se o item for um **número**: Colocamos ele no topo da pilha.
3.  Se o item for um **operador** (como `+`, `-`, `*`, `/`):
    * Retiramos os dois números que estão no topo da pilha.
    * Aplicamos a operação neles.
    * Colocamos o resultado de volta no topo da pilha.

#### Exemplo Visual

Vamos calcular a expressão: `10 2 + 5 /` (que equivale a `(10 + 2) / 5` na notação tradicional).

| Token Lido | Ação | Estado da Pilha (Topo à esquerda) |
| :--- | :--- | :--- |
| `10` | É número: empilha | `[10.0]` |
| `2` | É número: empilha | `[2.0, 10.0]` |
| `+` | É operador: desempilha 2 e 10, soma (10+2=12), empilha | `[12.0]` |
| `5` | É número: empilha | `[5.0, 12.0]` |
| `/` | É operador: desempilha 5 e 12, divide (12/5=2.4), empilha | `[2.4]` |
| **Fim** | Sobrou 1 item: é o resultado | **Resultado: 2.4** |

---

## Objetivos da Tarefa

Você deve implementar um módulo Haskell que avalie essas expressões de forma **segura**. O programa **não pode falhar abruptamente** (crashar) se o usuário digitar algo errado.

Você deve lidar com dois tipos principais de erro usando o tipo `Maybe`:
1.  **Expressão Malformada:** Operadores sem operandos suficientes (ex: `10 +` ou `+`).
2.  **Erro Matemático:** Divisão por zero (ex: `10 0 /`).

---

## Funções a Implementar

### 1. `solveRPN :: String -> Maybe Double`

Esta é a função principal que recebe a string bruta da expressão e retorna o resultado.

* **Entrada:** Uma `String` contendo números e operadores separados por espaço.
* **Saída:** `Just resultado` se tudo correr bem, ou `Nothing` se houver qualquer erro.

**Dica:** Use a função `words` (do Prelude) para quebrar a string em uma lista de palavras (tokens). Ex: `words "10 2 +"` resulta em `["10", "2", "+"]`.

### 2. `main :: IO ()`

Uma ação de E/S que cria uma interface interativa (REPL) para o usuário.

* Deve solicitar uma entrada.
* Se o usuário digitar nada (linha vazia) ou "sair", o programa encerra.
* Caso contrário, calcula o resultado usando `solveRPN`.
    * Se for `Just v`, imprime o valor.
    * Se for `Nothing`, imprime uma mensagem de erro amigável.
* Repete o processo.

---

## Dicas de Estruturação (Importante!)

A melhor maneira de resolver este problema é criando uma **função auxiliar** que processa a lista de tokens e mantém o estado atual da pilha.

Sugestão de assinatura:
```haskell
-- pilha: Lista de Double
-- tokens: Lista de String (o que falta ler)
processa :: [Double] -> [String] -> Maybe Double
````

Use a expressão **`case`** extensivamente nesta função auxiliar para analisar a estrutura da lista de tokens e da pilha:

1.  **Caso Base (Tokens acabaram):**

      * Analise a pilha. Se tiver exatamente um elemento `[resultado]`, retorne `Just resultado`.
      * Se a pilha estiver vazia ou tiver mais de um elemento, a expressão estava errada: retorne `Nothing`.

2.  **Caso Recursivo (Tem tokens):**

      * Analise o próximo token (a cabeça da lista de tokens).
      * **Se for operador (ex: "+"):** Analise a **pilha** usando `case`.
          * A pilha tem pelo menos dois elementos (`y:x:resto`)? Se sim, calcule `x + y`, empilhe o resultado e continue.
          * Atenção: Para divisão (`/`), verifique se `y` é zero antes de dividir\!
          * A pilha tem menos de dois elementos? Retorne `Nothing` (erro de falta de operandos).
      * **Se for número:** Use `readMaybe` para tentar converter a string em `Double`.
          * Sucesso? Empilhe o número e continue.
          * Falha? Então o token é inválido (não é operador nem número). Retorne `Nothing`.

-----

## Exemplo de Execução

```text
Calculadora RPN Segura
Digite sua expressão (ou tecle Enter para sair):
> 10 2 +
Resultado: 12.0
> 5 1 2 + 4 * + 3 -
Resultado: 14.0
> 10 0 /
Erro: Expressão inválida ou erro matemático.
> 10 +
Erro: Expressão inválida ou erro matemático.
> bla bla
Erro: Expressão inválida ou erro matemático.
>
Fim.
```

-----

## Desenvolvimento e Testes

Compile, execute e teste o projeto com:

```shellsession
$ cabal build                 # Compila o projeto
$ cabal repl rpn-calculator   # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run                   # Executa o programa
$ cabal test                  # Executa os testes de verificação automática
```
