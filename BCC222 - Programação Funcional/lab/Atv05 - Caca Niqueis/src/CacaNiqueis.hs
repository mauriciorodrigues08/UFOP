module CacaNiqueis
  ( calculaPremio,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hFlush, hSetBuffering, stdout)
import Text.Printf (printf)

calculaPremio :: Char -> Char -> Char -> Double -> Double
calculaPremio f1 f2 f3 aposta =
  let frutas = [f1, f2, f3]
      numBananas = length $ filter (== 'b') frutas
  in case numBananas of
       3 -> 10.0 * aposta
       2 -> 5.0 * aposta
       1 -> 1.0 * aposta
       _ -> 0.0

getCharLine :: String -> IO Char
getCharLine prompt = do
  putStr prompt
  hFlush stdout
  c <- getChar
  _ <- getLine
  return c

main :: IO ()
main = do
  hSetBuffering stdout NoBuffering 
  
  f1 <- getCharLine "Informe a primeira fruta: "
  f2 <- getCharLine "Informe a segunda fruta: "
  f3 <- getCharLine "Informe a terceira fruta: "

  putStr "Informe o valor da aposta: "
  hFlush stdout
  apostaStr <- getLine
  let aposta = read apostaStr :: Double

  let premio = calculaPremio f1 f2 f3 aposta

  if premio > 0.0
    then printf "Valor devolvido: R$ %.2f\n" premio
    else putStrLn "Tente novamente!"