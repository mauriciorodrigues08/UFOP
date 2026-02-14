[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/joZYdkq1)
# Tarefa: Tipos de Dados Recursivos - Árvores Binárias

## Descrição

Nesta tarefa, você irá definir e implementar um tipo de dado algébrico para representar **árvores binárias**, uma das estruturas de dados recursivas mais fundamentais em computação.

O objetivo é praticar a definição de um tipo de dado polimórfico e recursivo a partir do zero e, em seguida, implementar funções que operam sobre essa nova estrutura usando casamento de padrão e recursão.

## Tarefas a Implementar

Todas as suas implementações devem ser feitas no arquivo `src/BinTree.hs`.

### 1. Definição do Tipo `BinTree`

Defina um construtor de tipo algébrico `BinTree` para representar árvores binárias. O tipo deve ser **polimórfico** e **recursivo**.

Uma árvore binária (`BinTree a`) pode ser:
* **Vazia**, representada por um construtor `V`.
* Um **Nó** (não vazia), representada por um construtor `N` que contém:
    * Um valor de tipo `a` (a informação armazenada no nó).
    * Uma sub-árvore esquerda do tipo `BinTree a`.
    * Uma sub-árvore direita do tipo `BinTree a`.

Sua definição deve derivar instâncias para as classes `Show` e `Eq` para facilitar os testes.

### 2. Implementação de Funções sobre Árvores

Implemente as seguintes funções que operam sobre o tipo `BinTree a`.

#### `btLength :: BinTree a -> Int`
* Uma função que recebe uma árvore binária e retorna o número de elementos (nós) armazenados nela.

#### `btDepth :: BinTree a -> Int`
* Uma função que recebe uma árvore binária e retorna a sua profundidade (o comprimento do caminho mais longo da raiz até uma folha vazia).

#### `btElem :: (Eq a) => a -> BinTree a -> Bool`
* Uma função que recebe um valor e uma árvore, e verifica se o valor é um elemento presente em algum nó da árvore.

---

## Exemplo de Árvore

Você pode usar o seguinte exemplo para testar suas funções no GHCi:
```haskell
a1 :: BinTree Integer
a1 = N 12
       (N 5
          (N 2 V V)
          (N 9 (N 6 V V) V))
       (N 20
          V
          (N 30 (N 25 V V) (N 31 V V)))
````

## Exemplo de Uso no GHCi

```haskell
> btLength a1
8

> btDepth a1
4

> btElem 9 a1
True

> btElem 10 a1
False
```
