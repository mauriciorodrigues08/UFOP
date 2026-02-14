module Main (main) where

import BinTree

-- Exemplo de árvore para testes manuais
a1 :: BinTree Integer
a1 = N 12
       (N 5
          (N 2 V V)
          (N 9 (N 6 V V) V))
       (N 20
          V
          (N 30 (N 25 V V) (N 31 V V)))

main :: IO ()
main = do
    putStrLn "Exemplo de Árvore Binária:"
    print a1
    
    putStrLn "\n--- Testando Funções ---"
    putStrLn $ "Tamanho da árvore: " ++ show (btLength a1)
    putStrLn $ "Profundidade da árvore: " ++ show (btDepth a1)
    putStrLn $ "O elemento 9 está na árvore? " ++ show (btElem 9 a1)
    putStrLn $ "O elemento 100 está na árvore? " ++ show (btElem 100 a1)
