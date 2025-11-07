-- Calculo de IMC
calculaIMC :: (Fractional a, Ord a) => a -> a -> String
calculaIMC peso altura
  | imc < 18.5 = "Abaixo do peso"
  | imc < 25.0 = "Saudavel"
  | imc < 30.0 = "Sobrepeso"
  | otherwise  = "Obeso"
  where
    imc = peso / altura^2
-- Em um comentário, explique por que sua assinatura de tipo precisa das restrições que você escolheu.
-- Precisa de `Fractional a` por causa do (/) e `Ord a` por causa do (<).


-- Classificação de Triângulos
classificaTriangulo :: (Num a, Ord a) => a -> a -> a -> Maybe String
classificaTriangulo a b c
  | not ehTriangulo = Nothing -- Não é triângulo
  | (a == b && a == c)            = Just "Equilatero" -- Equilátero
  | (a /= b && a /= c && b /= c)  = Just "Escaleno" -- Escaleno
  | otherwise                     = Just "Isosceles" -- Isosceles
  where
    -- Validação (desigualdade triangular):
    ehTriangulo
      | a+b < c   = False
      | a+c < b   = False
      | b+c < a   = False
      | otherwise = True

-- Em um comentário, explique as restrições de classe necessárias.
-- Precisa de `Num a` para o (+) e `Ord a` para o (>) e (==).


-- Caixa Eletrônico
saqueCaixa :: Integral a => a -> (a, a, a, a) 
saqueCaixa valor = (q50, q20, q10, q1)
  where
    (q50, r50) = divMod valor 50
    (q20, r20) = divMod r50 20
    (q10, r10) = divMod r20 10
    (q1, r1)   = divMod r10 1

-- Em um comentário, explique a restrição de classe.
-- Precisa de `Integral a` por causa de `divMod`.


-- Calculadora de Tinta
calculaTinta :: 
calculaTinta area = (latas, galoes, precoTotal)
  where
    litrosNecessarios = undefined
    -- Lógica de compra:
    latasFrac = undefined
    latas = undefined -- Arredonda para baixo para latas
    litrosRestantes = undefined
    galoes = undefined -- Arredonda para cima para galoes
    -- Cálculo do preço total:
    precoTotal = undefined
