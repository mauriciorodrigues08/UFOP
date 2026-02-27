[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Jt2isHbi)
# Tarefa: Processamento Seguro de Dados com Functor, Applicative e Monad

## Descrição

Em muitas aplicações do mundo real, as computações podem falhar. Uma divisão por zero pode ocorrer, um ficheiro pode não ser encontrado, ou um texto pode estar num formato inválido. Lidar com estes erros de forma explícita pode levar a código complexo e aninhado (o "callback hell").

Nesta tarefa, você irá explorar como as abstrações de `Functor`, `Applicative` e `Monad` em Haskell nos permitem gerir computações que podem falhar de forma elegante e segura. Para isso, você irá implementar o tipo `Result a`, uma alternativa ao `Maybe a` que carrega uma mensagem de erro em caso de falha.

## Tarefas a Implementar

Todas as suas implementações devem ser feitas no ficheiro `src/Result.hs`.

### 1. Definição do Tipo `Result`

Primeiro, defina o tipo algébrico de dados `Result a`. Ele deve ter dois construtores de dados:
* `Ok a`: Para representar uma computação bem-sucedida que encapsula um valor do tipo `a`.
* `Error Exception`: Para representar uma falha, carregando uma mensagem de erro (pode usar o sinónimo de tipo `type Exception = String`).

Não se esqueça de derivar as instâncias para as classes `Show` e `Eq`.

### 2. Instância de `Functor`

Torne o tipo `Result` uma instância da classe de tipo `Functor`. Lembre-se, `fmap` aplica uma função a um valor dentro de um contexto.
* Se o `Result` for um `Ok`, a função deve ser aplicada ao valor interno.
* Se o `Result` for um `Error`, a função não deve ser aplicada e o erro deve ser propagado.

**Exemplo de Uso:**
```haskell
> fmap (*2) (Ok 10)
Ok 20

> fmap (*2) (Error "Divisão por zero")
Error "Divisão por zero"
````

### 3\. Instância de `Applicative`

Torne o tipo `Result` uma instância da classe `Applicative`.

  * A função `pure` deve encapsular um valor puro num `Result` bem-sucedido.
  * O operador `(<*>)` deve aplicar uma função encapsulada num `Result` a um valor também encapsulado num `Result`. Se qualquer um dos dois for um `Error`, o resultado final deve ser o primeiro erro encontrado.

**Exemplo de Uso:**

```haskell
> pure (+) <*> Ok 3 <*> Ok 5
Ok 8

> pure (+) <*> Error "Primeiro valor inválido" <*> Ok 5
Error "Primeiro valor inválido"
```

### 4\. Instância de `Monad`

Finalmente, torne o tipo `Result` uma instância da classe `Monad`. O operador `(>>=)` é a chave para encadear computações que podem falhar.

  * Se o primeiro argumento for um `Error`, o `(>>=)` deve ignorar a função seguinte e propagar o erro.
  * Se o primeiro argumento for um `Ok x`, ele deve aplicar a função ao valor `x` para obter o próximo `Result`.

**Exemplo de Uso:**

```haskell
-- Função de exemplo que pode falhar
divideSeguro :: Double -> Double -> Result Double
divideSeguro _ 0 = Error "Divisão por zero"
divideSeguro x y = Ok (x / y)

-- Encadeamento
> Ok 100 >>= divideSeguro 2 >>= divideSeguro 5
Ok 10.0

> Ok 100 >>= divideSeguro 0 >>= divideSeguro 5
Error "Divisão por zero"
```

-----

## Desafio Opcional: Função de Parsing

Se terminar as instâncias, tente criar uma função `parseInteiros :: String -> Result [Int]` que recebe uma string de números separados por espaços (ex: "10 20 30") e a converte para `Ok [10, 20, 30]`. Se qualquer uma das "palavras" não for um inteiro válido, a função deve retornar um `Error` com uma mensagem apropriada.
