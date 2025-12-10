module Chocolates(calculaPreco , loopDeCompras, main)
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Printf (printf)
import Text.Read (readMaybe)

-- | Calcula o valor total da compra (sem desconto) com base na quantidade de caixas.
calculaPreco :: Int -> Double
calculaPreco qtde
  | qtde <= 0             = 0.0
  | qtde <= 10            = fromIntegral qtde * 20.0
  | qtde <= 30            = fromIntegral qtde * 15.0
  | qtde <= 60            = fromIntegral qtde * 10.0
  | otherwise             = fromIntegral qtde * 5.0

-- | Ação de E/S recursiva que implementa o laço principal de compras.
loopDeCompras :: IO ()
loopDeCompras = do
  putStr "Informe a quantidade de caixas: "
  hFlush stdout
  entradaQt <- getLine
  case readMaybe entradaQt :: Maybe Int of
    Nothing -> do
      -- entrada não numérica: tratar como inválida e mostrar o que foi digitado
      putStrLn $ "ERRO: Quantidade inválida: " ++ entradaQt
      continuaPergunta
    Just qtde ->
      if qtde <= 0
        then do
          putStrLn $ "ERRO: Quantidade inválida: " ++ show qtde
          continuaPergunta
        else do
          let valor = calculaPreco qtde
          printf "Valor da compra: R$ %.2f\n" valor
          putStr "Informe pagamento com Pix (s/n): "
          hFlush stdout
          respPix <- getLine
          case respPix of
            "s" -> do
              let valorPix = valor * (1 - 0.08) -- 8% de desconto
              printf "Valor da compra com Pix: R$ %.2f\n" valorPix
            _ -> return ()
          continuaPergunta
  where
    continuaPergunta :: IO ()
    continuaPergunta = do
      putStr "Informe se deseja comprar novamente (s/n): "
      hFlush stdout
      resp <- getLine
      case resp of
        "s" -> loopDeCompras
        _   -> putStrLn "Fim das compras, obrigado!"

-- | Ação principal que inicia o programa.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Rotten Cocoa Market"
  putStr "Informe se deseja comprar (s/n): "
  hFlush stdout
  resp <- getLine
  case resp of
    "s" -> loopDeCompras
    _   -> putStrLn "Fim das compras, obrigado!"
