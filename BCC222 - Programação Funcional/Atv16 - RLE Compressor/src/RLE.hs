module RLE
  ( comprime,
    descomprime,
    main,
  )
where

import Data.List (group)
import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Read (readMaybe)

-- | Comprime uma string em uma lista de pares (caractere, contagem).
comprime :: String -> [(Char, Int)]
comprime texto = map (\g -> (head g, length g)) (group texto)

-- | Descomprime uma lista de pares para uma string.
descomprime :: [(Char, Int)] -> Maybe String
descomprime [] = Just ""
descomprime ((char, count) : xs)
  | count <= 0 = Nothing
  | otherwise =
      case descomprime xs of
        Nothing -> Nothing
        Just restante -> Just (replicate count char ++ restante)

-- | Função auxiliar para o laço do menu
runMenu :: IO ()
runMenu = do
  putStrLn "-- Menu --"
  putStrLn "1) Comprimir"
  putStrLn "2) Descomprimir"
  putStrLn "*) Sair"
  putStr "Opção: "
  opcao <- getLine

  case opcao of
    "1" -> do
      putStr "Digite o texto para comprimir: "
      texto <- getLine
      let comprimido = comprime texto
      putStr "Resultado: "
      print comprimido
      
      -- Verificação de ida e volta
      case descomprime comprimido of
        Just t | t == texto -> putStrLn "Verificação (ida e volta): OK"
        _                   -> putStrLn "Verificação (ida e volta): FALHOU"
      
      runMenu -- Reinicia o laço

    "2" -> do
      putStr "Digite a lista de pares: "
      input <- getLine
      -- Tenta ler a string como uma lista de pares
      case readMaybe input :: Maybe [(Char, Int)] of
        Nothing -> do
          putStrLn "Entrada da lista inválida."
          runMenu
        Just lista -> do
          case descomprime lista of
            Nothing -> putStrLn "Resultado da descompressão: Falha (dados inválidos)"
            Just str -> do
              putStr "Resultado: "
              print str -- print inclui as aspas na string, como no exemplo
              
              -- Verificação de ida e volta
              let recomprimido = comprime str
              if recomprimido == lista
                then putStrLn "Verificação (ida e volta): OK"
                else putStrLn "Verificação (ida e volta): FALHOU"
          
          runMenu -- Reinicia o laço

    _ -> return () -- Sai do programa

-- | Ação principal que inicializa o buffer e chama o laço do menu.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  runMenu