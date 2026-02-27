module MediaSequencia(calculaMedia, lerNumeros, main)
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Printf (printf)
import Text.Read (readMaybe)

-- Calcula a média de uma lista de Doubles.
-- Retorna 0.0 para uma lista vazia.
calculaMedia :: [Double] -> Double
calculaMedia [] = 0.0
calculaMedia xs = sum xs / fromIntegral (length xs)

-- Lê n Doubles da entrada padrão e os retorna em uma lista.
-- Retorna uma lista vazia se n <= 0.
lerNumeros :: Int -> IO [Double]
lerNumeros n
  | n <= 0 = return []
  | otherwise = do
      putStr "Digite um número: "
      hFlush stdout
      entrada <- getLine
      case readMaybe entrada of
        Just valor -> do
          resto <- lerNumeros (n - 1)
          return (valor : resto)
        Nothing -> do
          -- Em caso de erro, tenta novamente sem consumir uma posição
          putStrLn "Entrada inválida, tente novamente."
          lerNumeros n

-- Main
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStr "Quantidade de números a serem lidos: "
  entradaN <- getLine

  let maybeN = readMaybe entradaN :: Maybe Int

  case maybeN of
    Nothing -> do
      putStrLn "A média dos números é: 0.00"
    Just n -> do
      numeros <- lerNumeros n
      let media = calculaMedia numeros
      printf "A média dos números é: %.2f\n" media
