module Vendas where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))
import Text.Printf

valorTotal :: Double -> Double -> Double
valorTotal morangos maças =
  let
    precoMorangos = if morangos > 5
                      then morangos * 7.2
                      else morangos * 8.5

    precoMacas = if maças > 5
                    then maças * 4.75
                    else maças * 5.25

  in precoMorangos + precoMacas

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Digite a quantidade de Morangos (em kg):"
  morangos_str <- getLine
  let morangos = read morangos_str :: Double
  hSetBuffering stdout NoBuffering
  putStrLn "Digite a quantidade de Maçãs (em kg):"
  macas_str <- getLine
  let maças = read macas_str :: Double
  if morangos < 0 || maças < 0
    then putStrLn "Entrada inválida"
    else do
      let total = valorTotal morangos maças
      printf "O valor total da compra é R$ %.2f\n" total
