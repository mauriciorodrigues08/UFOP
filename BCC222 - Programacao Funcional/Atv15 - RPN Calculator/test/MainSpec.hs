module Main (main) where

import Test.Hspec
import Test.QuickCheck
import RPN (solveRPN)

main :: IO ()
main = hspec $ do
  describe "Função: solveRPN" $ do
    
    it "avalia soma simples" $
      solveRPN "10 2 +" `shouldBe` Just 12.0

    it "avalia precedência implícita (10 4 3 + 2 * -)" $
      -- Equivalente a: 10 - ((4 + 3) * 2) = 10 - 14 = -4
      solveRPN "10 4 3 + 2 * -" `shouldBe` Just (-4.0)

    it "trata divisão corretamente" $
      solveRPN "20 2 /" `shouldBe` Just 10.0

    it "retorna Nothing para divisão por zero" $
      solveRPN "10 0 /" `shouldBe` Nothing

    it "retorna Nothing para operadores insuficientes (falta operando)" $
      solveRPN "10 +" `shouldBe` Nothing

    it "retorna Nothing para operadores insuficientes (pilha vazia)" $
      solveRPN "+" `shouldBe` Nothing
    
    it "retorna Nothing se sobrarem números na pilha" $
      solveRPN "10 2 3 +" `shouldBe` Nothing

    it "retorna Nothing para entrada inválida (letras)" $
      solveRPN "10 batata +" `shouldBe` Nothing

    describe "Propriedades" $ do
      it "um único número resulta nele mesmo" $ property $
        \x -> solveRPN (show x) == Just (x :: Double)
