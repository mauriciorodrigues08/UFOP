module Figuras
  ( Figura(..),
    area,
    perimetro,
    ehRegular
  )
where

-- Tarefa 1: Adicionado construtor Triangulo com três campos Double
data Figura = Circulo Double
            | Retangulo Double Double
            | Triangulo Double Double Double
            deriving (Show, Eq)

-- Tarefa 2: Cálculo da área incluindo Triangulo (Fórmula de Heron)
area :: Figura -> Double
area (Circulo r)      = pi * r^2
area (Retangulo b a)  = b * a
area (Triangulo a b c) = sqrt (p * (p - a) * (p - b) * (p - c))
  where p = (a + b + c) / 2

-- Tarefa 3.1: Implementação do perímetro
perimetro :: Figura -> Double
perimetro (Circulo r)       = 2 * pi * r
perimetro (Retangulo b a)   = 2 * (b + a)
perimetro (Triangulo a b c) = a + b + c

-- Tarefa 3.2: Implementação da regularidade
ehRegular :: Figura -> Bool
ehRegular (Circulo _)         = True
ehRegular (Retangulo b a)     = b == a
ehRegular (Triangulo a b c)   = a == b && b == c