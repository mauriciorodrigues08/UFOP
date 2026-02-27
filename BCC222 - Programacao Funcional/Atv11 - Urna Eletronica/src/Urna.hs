module Urna(computaVotos, main)
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Printf (printf)

-- função principal de inicialização
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "=== Urna Eletronica ==="
  putStrLn "Opcoes: [1] Lambda | [2] Monad | [3] Curry | [0] Encerrar"
  putStrLn ""
  -- inicia a recursão com contadores zerados
  computaVotos 0 0 0 0

-- ação recursiva que gerencia o estado da votação.
-- recebe os contadores atuais: (v1, v2, v3, nulos)
computaVotos :: Int -> Int -> Int -> Int -> IO ()
computaVotos v1 v2 v3 nulos = do
  putStr "Digite o voto: "
  line <- getLine
  -- tenta converter para inteiro; se falhar, trata como voto nulo
  case reads line :: [(Int, String)] of
    [(x, _)] ->
      case x of
        0 -> do
          putStrLn ""
          putStrLn "=== Boletim de Urna ==="
          printf "Lambda: %d\n" v1
          printf "Monad:  %d\n" v2
          printf "Curry:  %d\n" v3
          printf "Nulos:  %d\n" nulos
          putStrLn "-----------------------"
          printf "Total:  %d\n" (v1 + v2 + v3 + nulos)
        1 -> do
          putStrLn "Voto computado para Lambda."
          putStrLn ""
          computaVotos (v1 + 1) v2 v3 nulos
        2 -> do
          putStrLn "Voto computado para Monad."
          putStrLn ""
          computaVotos v1 (v2 + 1) v3 nulos
        3 -> do
          putStrLn "Voto computado para Curry."
          putStrLn ""
          computaVotos v1 v2 (v3 + 1) nulos
        _ -> do
          putStrLn "Voto Nulo computado."
          putStrLn ""
          computaVotos v1 v2 v3 (nulos + 1)
    _ -> do
      -- entrada não numérica -> voto nulo
      putStrLn "Voto Nulo computado."
      putStrLn ""
      computaVotos v1 v2 v3 (nulos + 1)
