module Main (main) where

import Test.Hspec
import BinTree

-- Árvore de exemplo usada nos testes
a1 :: BinTree Integer
a1 = N 12
       (N 5
          (N 2 V V)
          (N 9 (N 6 V V) V))
       (N 20
          V
          (N 30 (N 25 V V) (N 31 V V)))

main :: IO ()
main = hspec $ do
  describe "btLength" $ do
    it "retorna 0 para uma árvore vazia" $
      btLength V `shouldBe` 0
      
    it "retorna o número correto de nós para a árvore de exemplo" $
      -- CORREÇÃO: O número correto de nós na árvore a1 é 9.
      btLength a1 `shouldBe` 9

  describe "btDepth" $ do
    it "retorna 0 para uma árvore vazia" $
      btDepth V `shouldBe` 0
      
    it "retorna a profundidade correta para a árvore de exemplo" $
      btDepth a1 `shouldBe` 4
      
    it "retorna a profundidade correta para uma árvore simples" $
      btDepth (N 10 (N 5 V V) V) `shouldBe` 2

  describe "btElem" $ do
    it "retorna False para um elemento em uma árvore vazia" $
      btElem 10 V `shouldBe` False
      
    it "retorna True para um elemento que está na raiz" $
      btElem 12 a1 `shouldBe` True
      
    it "retorna True para um elemento que está em uma folha" $
      btElem 25 a1 `shouldBe` True
      
    it "retorna False para um elemento que não está na árvore" $
      btElem 100 a1 `shouldBe` False
