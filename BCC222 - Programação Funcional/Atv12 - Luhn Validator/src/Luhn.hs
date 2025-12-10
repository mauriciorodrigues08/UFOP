module Luhn
  ( toDigits,
    toDigitsRev,
    doubleEveryOther,
    sumDigits,
    validate,
    main
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

-- Converte um inteiro para uma lista de dígitos na ordem inversa.
toDigitsRev :: Integer -> [Integer]
toDigitsRev n
  | n <= 0    = []
  | otherwise = (n `mod` 10) : toDigitsRev (n `div` 10)

-- Converte um inteiro para uma lista de dígitos na ordem correta.
toDigits :: Integer -> [Integer]
toDigits n = reverse (toDigitsRev n)

-- Dobra cada segundo dígito, começando da direita.
doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther ns = reverse (doubleFromLeft (reverse ns))
  where
    -- Função auxiliar que processa da esquerda para a direita
    doubleFromLeft :: [Integer] -> [Integer]
    doubleFromLeft []         = []
    doubleFromLeft [x]        = [x] -- O primeiro elemento (originalmente o último) mantém-se
    doubleFromLeft (x : y : zs) = x : (y * 2) : doubleFromLeft zs

-- Soma todos os dígitos. Se um número for > 9, soma seus dígitos constituintes.
sumDigits :: [Integer] -> Integer
sumDigits ns = sum (map normalize ns)
  where
    -- Normaliza um número dobrado: se > 9, soma os dígitos 
    normalize :: Integer -> Integer
    normalize x
      | x > 9     = (x `div` 10) + (x `mod` 10)
      | otherwise = x

-- Valida o cartão se a soma final for múltiplo de 10.
validate :: Integer -> Bool
validate n = (sumDigits (doubleEveryOther (toDigits n))) `mod` 10 == 0

-- Interação com o usuário
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering -- Garante que o prompt apareça imediatamente
  putStr "Digite o número do cartão de crédito: "
  input <- getLine
  let numero = read input :: Integer
  if validate numero
    then putStrLn "Válido"
    else putStrLn "Inválido"