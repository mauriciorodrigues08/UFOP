module Gorjeta (main, gorjeta) where

import System.IO (stdout, BufferMode(NoBuffering), hSetBuffering)
import Data.Maybe (isJust, fromJust)
import Text.Printf (printf)
import Text.Read (readMaybe)

gorjeta :: Double -> String -> Maybe Double
gorjeta conta qualidade
    | conta < 0 = Nothing
    | qualidade == "ruim"      = Just (conta * 0.05)
    | qualidade == "bom"       = Just (conta * 0.10)
    | qualidade == "excelente" = Just (conta * 0.15)
    | otherwise                = Nothing

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering

    putStr "Digite o valor da conta: "
    contaStr <- getLine

    let maybeConta = readMaybe contaStr :: Maybe Double

    if isJust maybeConta
        then do let contaValor = fromJust maybeConta
                putStr "Qualidade do serviço (ruim, bom, excelente): "
                qualidade <- getLine

                let g = gorjeta contaValor qualidade
                if isJust g
                    then do let valorGorjetaCalculada = fromJust g
                            let totalPagar = contaValor + valorGorjetaCalculada
                            printf "Gorjeta: R$ %.2f\n" valorGorjetaCalculada
                            printf "Total a pagar: R$ %.2f\n" totalPagar
                    else
                         putStrLn "Entrada inválida!"
        else putStrLn "Entrada inválida!"
