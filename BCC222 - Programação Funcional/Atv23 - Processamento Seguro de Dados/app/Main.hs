module Main (main) where

import Result

-- Função de exemplo que pode falhar
divideSeguro :: Double -> Double -> Result Double
divideSeguro _ 0 = Error "Divisão por zero!"
divideSeguro x y = Ok (x / y)

main :: IO ()
main = do
    putStrLn "--- Testando Functor ---"
    print (fmap (*2) (Ok 10))
    print (fmap (*2) (Error "Falha inicial" :: Result Int))

    putStrLn "\n--- Testando Applicative ---"
    print (pure (+) <*> Ok 3 <*> Ok 5)
    print (pure (+) <*> Ok 3 <*> (Error "Segundo valor falhou" :: Result Int))

    putStrLn "\n--- Testando Monad ---"
    let computacao = Ok 100 >>= divideSeguro 2 >>= divideSeguro 5
    print computacao
    
    let computacaoComFalha = Ok 100 >>= divideSeguro 0 >>= divideSeguro 5
    print computacaoComFalha
