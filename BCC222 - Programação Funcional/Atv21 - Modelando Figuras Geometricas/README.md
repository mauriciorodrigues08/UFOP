[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G1PoRB86)
# Tarefa: Modelando Figuras Geométricas

## Descrição

Nesta tarefa, você irá trabalhar com um tipo de dado algébrico que modela diferentes figuras geométricas. O objetivo é praticar a extensão de um tipo de dado existente e a implementação de funções que operam sobre ele usando casamento de padrão.

Você começará com um módulo que define o tipo `Figura` e algumas funções básicas, e sua tarefa será adicionar novas funcionalidades.

## Estrutura Inicial

O arquivo `src/Figuras.hs` que você receberá contém as seguintes definições:

```haskell
-- Um tipo para representar figuras 2D
data Figura = Circulo Double
            | Retangulo Double Double
            deriving (Show)

-- Uma função para calcular a área de uma figura
area :: Figura -> Double
area (Circulo r)     = pi * r^2
area (Retangulo b a) = b * a
````

-----

## Tarefas a Implementar

Todas as suas implementações devem ser feitas no arquivo `src/Figuras.hs`.

### 1\. Adicionar o Construtor `Triangulo`

Modifique a declaração do tipo `Figura` para incluir um novo construtor de dados, `Triangulo`, que representa um triângulo a partir do comprimento de seus três lados.

```haskell
data Figura = Circulo Double
            | Retangulo Double Double
            | Triangulo Double Double Double -- Adicione esta alternativa
            deriving (Show)
```

### 2\. Estender as Funções Existentes

Atualize as funções que já existem para que elas também lidem com o novo construtor `Triangulo`.

#### `area :: Figura -> Double`

Adicione uma nova equação à função `area` para calcular a área de um triângulo.

  * **Dica:** Use a **Fórmula de Heron** para calcular a área a partir dos lados $a$, $b$ e $c$:\
    $$A = \sqrt{p(p-a)(p-b)(p-c)}$$
    onde $p$ é o semi-perímetro:\
    $$p = (a+b+c)/2$$

### 3\. Implementar Novas Funções

Implemente as seguintes funções novas, que também devem operar sobre o tipo `Figura` completo.

#### `perimetro :: Figura -> Double`

  * Uma função que recebe uma `Figura` e calcula o seu perímetro.
  * **Fórmulas:**
      * Círculo de raio $r$:\
        $$P = 2 \pi r$$
      * Retângulo de base $b$ e altura $h$:\
        $$P = 2 (b + h)$$
      * Triângulo de lados $a, b, c$:\
        $$P = a + b + c$$

#### `ehRegular :: Figura -> Bool`

  * Uma função que retorna `True` se a figura for *regular* e `False` caso contrário.
  * **Definições de Regularidade:**
      * Um `Circulo` é sempre regular.
      * Um `Retangulo` é regular se for um quadrado (base == altura).
      * Um `Triangulo` é regular se for equilátero (todos os lados são iguais).

-----

## Exemplo de Uso no GHCi

```haskell
> c = Circulo 10.0
> r = Retangulo 4.0 5.0
> q = Retangulo 4.0 4.0
> t = Triangulo 3.0 4.0 5.0
> te = Triangulo 5.0 5.0 5.0

> area t
12.0

> perimetro c
62.83185307179586

> ehRegular q
True

> ehRegular t
False

> ehRegular te
True
```
