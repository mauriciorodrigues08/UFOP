module CalculoPi
  ( valorPi,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)


valorPi :: Integer -> Double
valorPi k
  | k <= 0    = 0.0
  | otherwise = 4 * somatorio 0
  where
    somatorio :: Integer -> Double
    somatorio i
      | i == k    = 0.0 
      | otherwise = termo + somatorio (i + 1)
      where
        
        numerador   = (-1) ** fromIntegral i
        denominador = 2 * fromIntegral i + 1
        termo       = numerador / denominador


main :: IO ()
main = do
  
  hSetBuffering stdout NoBuffering
  
  putStrLn "Cálculo aproximado de π por série"
  putStrLn "===================================="
  putStr "Digite o número de termos desejados na série: "
  
  input <- getLine
  let k = read input :: Integer
  
  if k < 0
    then putStrLn "Número de termos deve ser não negativo."
    else do
      let resultado = valorPi k
      putStrLn $ "π: " ++ show resultado