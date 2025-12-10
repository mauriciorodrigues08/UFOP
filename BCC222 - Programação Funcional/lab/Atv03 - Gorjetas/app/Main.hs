module Main (main) where

import qualified Gorjeta (main) -- Importa a 'main' lógica de Gorjeta.hs

main :: IO ()
main = Gorjeta.main -- Chama a 'main' lógica
