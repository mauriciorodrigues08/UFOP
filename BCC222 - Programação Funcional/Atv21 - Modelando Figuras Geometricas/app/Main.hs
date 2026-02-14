module Main (main) where

import Figuras

main :: IO ()
main = do
    putStrLn "Exemplos de Figuras Geométricas:"

    let c = Circulo 10.0
    let r = Retangulo 4.0 5.0
    let q = Retangulo 4.0 4.0
    let t = Triangulo 3.0 4.0 5.0
    let te = Triangulo 5.0 5.0 5.0

    putStrLn "\n--- Áreas ---"
    print $ area c
    print $ area r

    putStrLn "\n--- Perímetros ---"
    print $ perimetro c
    print $ perimetro r
    print $ perimetro t

    putStrLn "\n--- Figuras Regulares? ---"
    print $ ehRegular c
    print $ ehRegular q
    print $ ehRegular te
