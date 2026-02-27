module Hanoi
  ( Pino,
    Movimento,
    hanoi,
    main
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)

type Pino = String
type Movimento = (Pino, Pino)

-- Calcula a sequência de movimentos para resolver as Torres de Hanói.
hanoi :: Integer -> Pino -> Pino -> Pino -> [Movimento]
hanoi 0 _ _ _ = []
hanoi n origem destino auxiliar =
  passo1 ++ passo2 ++ passo3
  where
    -- Mover n-1 discos da Origem para o Auxiliar
    passo1 = hanoi (n - 1) origem auxiliar destino
    -- Mover o disco grande da Origem para o Destino
    passo2 = [(origem, destino)]
    -- Mover n-1 discos do Auxiliar para o Destino
    passo3 = hanoi (n - 1) auxiliar destino origem

-- Ação de E/S principal para interagir com o usuário.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStr "Quantos discos? "
  input <- getLine
  let n = read input :: Integer
  
  putStrLn $ "A solução para mover " ++ show n ++ " discos de A para B é:"
  
  let movimentos = hanoi n "A" "B" "C"
  printMovimentos movimentos

-- Função auxiliar para formatar a saída (não exportada, uso local no main)
printMovimentos :: [Movimento] -> IO ()
printMovimentos [] = return ()
printMovimentos ((origem, destino) : resto) = do
  putStrLn $ "Mova o disco de " ++ origem ++ " para " ++ destino
  printMovimentos resto