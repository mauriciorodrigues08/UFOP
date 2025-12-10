module Simulador
  ( simulaPopulacao,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Read (readMaybe)
import Data.Maybe (isJust)

simulaPopulacao :: Integer -> Double -> Integer -> Integer -> Integer
simulaPopulacao popInicial taxa colheita anos =
  simulaPopulacao' anos popInicial taxa colheita
    where
      simulaPopulacao' :: Integer -> Integer -> Double -> Integer -> Integer
      simulaPopulacao' 0 popAtual _ _ = popAtual
      simulaPopulacao' anosRestantes popAtual taxa colheita
        | popAtual == 0 = 0
        | otherwise = simulaPopulacao' (anosRestantes - 1) proxPop taxa colheita
        where
          popCrescida :: Double
          popCrescida = fromIntegral popAtual * (1.0 + taxa)

          popAposCrescimento :: Integer
          popAposCrescimento = floor popCrescida

          popAposColheita :: Integer
          popAposColheita = popAposCrescimento - colheita

          proxPop :: Integer
          proxPop = max 0 popAposColheita

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering

  putStr "Populacao inicial: "
  popStr <- getLine
  let popResult = readMaybe popStr :: Maybe Integer

  putStr "Taxa de crescimento (ex: 0.1): "
  taxaStr <- getLine
  let taxaResult = readMaybe taxaStr :: Maybe Double

  putStr "Colheita anual: "
  colheitaStr <- getLine
  let colheitaResult = readMaybe colheitaStr :: Maybe Integer

  putStr "Anos a simular: "
  anosStr <- getLine
  let anosResult = readMaybe anosStr :: Maybe Integer

  if isJust popResult && isJust taxaResult && isJust colheitaResult && isJust anosResult
    then do
      let popInicial = maybe 0 id popResult    -- Extrai o valor
      let taxa       = maybe 0.0 id taxaResult
      let colheita   = maybe 0 id colheitaResult
      let anos       = maybe 0 id anosResult

      if popInicial >= 0 && anos >= 0 && colheita >= 0
        then do
          let popFinal = simulaPopulacao popInicial taxa colheita anos
          putStrLn $ "Populacao final: " ++ show popFinal ++ " coelhos"
        else
          putStrLn "Entrada invalida"
    else
      putStrLn "Entrada invalida"