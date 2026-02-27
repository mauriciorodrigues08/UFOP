module RPN where

import Text.Read (readMaybe)
import System.IO (hSetBuffering, stdout, BufferMode(NoBuffering))

-- | Avalia uma expressão em Notação Polonesa Reversa (RPN).
solveRPN :: String -> Maybe Double
solveRPN expression = processa [] (words expression)
  where    
    -- 1. Caso Base: acabaram os tokens
    processa [resultado] [] = Just resultado -- Sucesso: sobrou exatamente 1 item
    processa _ []           = Nothing        -- Erro: pilha vazia ou com itens demais

    -- 2. Caso Recursivo: processando token por token
    processa stack (token:rest) = case token of
      "+" -> case stack of
               (y:x:s) -> processa ((x + y) : s) rest
               _       -> Nothing -- Falta operandos
      
      "-" -> case stack of
               (y:x:s) -> processa ((x - y) : s) rest -- Note a ordem: x - y
               _       -> Nothing

      "*" -> case stack of
               (y:x:s) -> processa ((x * y) : s) rest
               _       -> Nothing

      "/" -> case stack of
               (y:x:s) -> if y == 0 
                          then Nothing              -- Erro: Divisão por zero
                          else processa ((x / y) : s) rest
               _       -> Nothing

      -- Se não for operador, tenta ler como número
      valStr -> case readMaybe valStr of
                  Just num -> processa (num : stack) rest -- É número: empilha
                  Nothing  -> Nothing                     -- Token inválido

-- | Ação principal: Loop interativo (REPL)
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Calculadora RPN Segura"
  putStrLn "Digite sua expressão (ou tecle Enter/'sair' para encerrar):"
  replLoop

-- Função auxiliar para o loop
replLoop :: IO ()
replLoop = do
  putStr "> "
  input <- getLine
  
  case input of
    ""     -> putStrLn "Fim."
    "sair" -> putStrLn "Fim."
    _      -> do
      case solveRPN input of
        Just result -> putStrLn $ "Resultado: " ++ show result
        Nothing     -> putStrLn "Erro: Expressão inválida ou erro matemático."
      replLoop -- Recomeça o ciclo