[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/KZQwPGxR)
# Tarefa: Lambdas, Aplicação Parcial e Seções

## Descrição

Nesta tarefa, você não construirá um único programa grande, mas sim uma série de pequenas funções em Haskell. O objetivo é praticar intensivamente os conceitos de funções como valores de primeira classe, que são a base da programação funcional.

Os exercícios estão divididos em três partes, cada uma focada em um conceito chave:
1.  **Expressões Lambda:** Escrever funções anônimas para uso com funções de ordem superior.
2.  **Aplicação Parcial e Seções:** Criar funções especializadas de forma concisa.
3.  **Processamento de Dados:** Combinar os conceitos para resolver um problema prático.

Todas as suas implementações devem ser feitas no arquivo `src/Exercicios.hs`.

---

## Exercícios a Implementar

### Exercício 1: Refatorando para Expressões Lambda

Funções de ordem superior, como `map` e `filter`, frequentemente recebem outras funções como argumento. Quando essas funções auxiliares são simples e usadas apenas uma vez, é idiomático usar uma expressão lambda em vez de dar um nome a elas.

**Sua tarefa:** Crie novas versões das funções abaixo, substituindo as definições locais (`where`) por expressões lambda passadas diretamente para `map` e `filter`.

```haskell
-- 1.1: Função a ser refatorada
somaQuadradosPares :: [Int] -> Int
somaQuadradosPares xs = sum (map f (filter g xs))
  where
    f x = x*x
    g x = even x

-- Sua implementação com lambdas:
somaQuadradosParesLambda :: [Int] -> Int
somaQuadradosParesLambda = undefined

-- 1.2: Função a ser refatorada
stringsMaioresQue5 :: [String] -> [String]
stringsMaioresQue5 xs = filter g xs
  where
    g s = length s > 5

-- Sua implementação com lambdas:
stringsMaioresQue5Lambda :: [String] -> [String]
stringsMaioresQue5Lambda = undefined

-- 1.3: Função a ser refatorada
-- Adiciona o sufixo "!" a todas as strings com comprimento par.
adicionaExclamacaoPar :: [String] -> [String]
adicionaExclamacaoPar xs = map f (filter g xs)
  where
    f s = s ++ "!"
    g s = even (length s)

-- Sua implementação com lambdas:
adicionaExclamacaoParLambda :: [String] -> [String]
adicionaExclamacaoParLambda = undefined
````

### Exercício 2: Funções Especializadas com Aplicação Parcial e Seções

A aplicação parcial e as seções de operadores são ferramentas poderosas para criar novas funções a partir de funções existentes de forma muito concisa.

**Sua tarefa:** Implemente as seguintes funções usando **apenas aplicação parcial ou seções de operadores**. Você não deve usar a sintaxe `\x -> ...` para estas funções.

```haskell
-- 2.1: Deve retornar True se um caractere for uma vogal minúscula.
-- Dica: use a função `elem` e uma string com as vogais.
ehVogal :: Char -> Bool
ehVogal = undefined -- Ex: ehVogal 'a' -> True; ehVogal 'b' -> False

-- 2.2: Deve adicionar o sufixo ".com" a uma string.
adicionaCom :: String -> String
adicionaCom = undefined -- Ex: adicionaCom "google" -> "google.com"

-- 2.3: Deve retornar um número subtraído de 10.
-- Dica: use a função `subtract`.
subtraiDe10 :: Int -> Int
subtraiDe10 = undefined -- Ex: subtraiDe10 3 -> 7
```

### Exercício 3: Processamento de Dados com Lambdas e Padrões

Nesta seção, você combinará os conceitos para resolver pequenos problemas de processamento de dados.

**Sua tarefa:** Implemente as seguintes funções, utilizando `map` ou `filter` com expressões lambda. A lambda deve usar casamento de padrão na tupla de entrada.

```haskell
type Venda = (String, Double)
type Aluno = (String, Double, Double) -- nome, nota1, nota2

-- 3.1: Aplica uma taxa de 10% (* 1.1) apenas nos itens cujo preço seja maior que R$ 50,00.
aplicaTaxa :: [Venda] -> [Venda]
aplicaTaxa = undefined
-- Exemplo: aplicaTaxa [("A", 120.0), ("B", 80.0)] -> [("A", 132.0), ("B", 80.0)]

-- 3.2: Retorna uma lista de nomes dos alunos aprovados (média das notas >= 7.0).
alunosAprovados :: [Aluno] -> [String]
alunosAprovados = undefined
-- Exemplo: alunosAprovados [("Ana", 8.0, 8.0), ("Beto", 5.0, 7.0)] -> ["Ana"]

-- 3.3: Retorna uma lista de tuplas contendo o nome do produto e o preço final,
-- aplicando um desconto de 5% (* 0.95) a todos os produtos.
aplicaDesconto :: [Venda] -> [(String, Double)]
aplicaDesconto = undefined
-- Exemplo: aplicaDesconto [("A", 100.0), ("B", 20.0)] -> [("A", 95.0), ("B", 19.0)]
```

-----

## Desenvolvimento e Testes

Complete as definições no arquivo `src/Exercicios.hs`. O seu projeto deve passar em todos os testes fornecidos.

### Comandos do Cabal

Você pode editar os arquivos fonte e testá-los localmente com a ferramenta *cabal*:

```shellsession
$ cabal build                  # Compila o projeto
$ cabal repl lambda-exercicios # Carrega o projeto no REPL
$ cabal run lambda-exercicios  # Executa o programa, se houver
$ cabal test                   # Executa os testes de funcionalidade
```

### ✅ Dica: Verificação de Estilo com HLint

Além da corretude funcional (verificada com `cabal test`), esta atividade também avalia o **estilo** da sua implementação. Usaremos uma ferramenta chamada **HLint** para verificar se você usou *expressões lambda* e *seções de operadores* nos exercícios corretos.

Você pode (e deve!) executar esta mesma verificação localmente antes de enviar seu código para o GitHub.

**Comando para executar o HLint:**

```shell
cabal exec hlint -- src
````

* Se o comando não exibir nenhuma mensagem (ex: `No hints`), seu código está de acordo com as regras de estilo!
* Se houver um problema, o HLint exibirá mensagens com sugestões de melhoria.

#### Regras importantes de estilo:

* Funções com sufixo `Lambda` (como `somaQuadradosParesLambda`, `stringsMaioresQue5Lambda`, `adicionaExclamacaoParLambda`) **devem usar expressões lambda explícitas** (`\x -> ...`).
* Funções `ehVogal`, `adicionaCom` e `subtraiDe10` **não devem usar `where` ou `let`** — devem ser definidas usando aplicação parcial ou seções de operador.

> ⚠️ *Embora o `hlint` ajude bastante, ele pode não detectar todas as violações dessas regras.* Portanto, revise seu código manualmente antes de submeter. Soluções que não seguirem essas orientações poderão ser penalizadas na avaliação, mesmo que passem no `hlint`.
