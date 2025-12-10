module Overbooking(loopProcessaVoos, main)
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Read (readMaybe)

-- E/S recursiva.
-- argumentos: vooAtual, totalDeVoos, voosComOverbooking, passageirosExcedentes
loopProcessaVoos :: Int -> Int -> Int -> Int -> IO ()
loopProcessaVoos vooAtual totalVoos overbookingCount excessoCount
  | vooAtual > totalVoos = do
      putStrLn "Fim da entrada dos voos:"
      putStrLn $ "Ocorreram " ++ show overbookingCount ++ " voos com overbooking"
      putStrLn $ "Ocorreram " ++ show excessoCount ++ " passageiros acima da capacidade"
  | otherwise = do
      putStrLn $ "Voo " ++ show vooAtual ++ ":"
      putStr "Capacidade da aeronave: "
      hFlush stdout
      linhaCap <- getLine
      let capacidade = case readMaybe linhaCap :: Maybe Int of
                        Just x  -> x
                        Nothing -> 0
      putStr "Quantidade de passagens: "
      hFlush stdout
      linhaPass <- getLine
      let passagens = case readMaybe linhaPass :: Maybe Int of
                        Just x  -> x
                        Nothing -> 0
      if passagens > capacidade
        then do
          putStrLn "Alerta: Voo com overbooking!"
          let novosVoos = overbookingCount + 1
              novosExcessos = excessoCount + (passagens - capacidade)
          loopProcessaVoos (vooAtual + 1) totalVoos novosVoos novosExcessos
        else
          loopProcessaVoos (vooAtual + 1) totalVoos overbookingCount excessoCount

-- main
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Rotten Cocoa Airlines Corp."
  putStr "Informe a quantidade de voos: "
  hFlush stdout
  linhaN <- getLine
  let n = case readMaybe linhaN :: Maybe Int of
            Just x  -> x
            Nothing -> 0
  loopProcessaVoos 1 n 0 0
