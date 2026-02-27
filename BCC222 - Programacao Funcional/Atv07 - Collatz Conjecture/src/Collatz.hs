module Collatz
  ( analisaTrajetoria,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)


analisaTrajetoria :: Integer -> (Int, Integer)
analisaTrajetoria n = aux n 0 n
  where
    aux :: Integer -> Int -> Integer -> (Int, Integer)
    aux 1 steps currentMax = (steps, currentMax)
    aux current steps currentMax =
      let next = if even current
                   then current `div` 2
                   else 3 * current + 1
          newMax = max currentMax next
       in aux next (steps + 1) newMax


main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  
  putStr "Digite um numero positivo: "
  input <- getLine
  let n = read input :: Integer
  
  if n <= 0
    then putStrLn "Entrada invalida"
    else do
      let (passos, maximo) = analisaTrajetoria n
      putStrLn $ "Passos ate 1: " ++ show passos
      putStrLn $ "Valor maximo: " ++ show maximo