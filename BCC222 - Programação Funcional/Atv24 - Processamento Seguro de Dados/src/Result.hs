module Result
  ( Exception,
    Result(..),
    parseInteiros
  )
where

import Text.Read (readMaybe)

type Exception = String

-- Tarefa 1: Definição do tipo de dado Result
data Result a = Ok a | Error Exception
  deriving (Show, Eq)

-- Tarefa 2: Instância de Functor
instance Functor Result where
  -- fmap :: (a -> b) -> Result a -> Result b
  fmap f (Ok x)    = Ok (f x)
  fmap _ (Error e) = Error e

-- Tarefa 3: Instância de Applicative
instance Applicative Result where
  -- pure :: a -> Result a
  pure = Ok

  -- (<*>) :: Result (a -> b) -> Result a -> Result b
  Ok f    <*> Ok x    = Ok (f x)
  Error e <*> _       = Error e
  _       <*> Error e = Error e

-- Tarefa 4: Instância de Monad
instance Monad Result where
  -- (>>=) :: Result a -> (a -> Result b) -> Result b
  Ok x    >>= f = f x
  Error e >>= _ = Error e

-- Desafio: Função de Parsing
parseInteiros :: String -> Result [Int]
parseInteiros s = mapM validar (words s)
  where
    validar w = case readMaybe w of
      Just n  -> Ok n
      Nothing -> Error ("Falha ao processar: " ++ w)