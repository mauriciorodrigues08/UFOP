module Main (main) where

import Run (runWithInput)
import Test.Hspec
import qualified Hanoi as T

main :: IO ()
main = hspec $ do
  describe "Função Pura: hanoi" $ do
    it "retorna uma lista vazia para 0 discos" $
      T.hanoi 0 "A" "B" "C" `shouldBe` []

    it "retorna um único movimento para 1 disco" $
      T.hanoi 1 "A" "B" "C" `shouldBe` [("A", "B")]

    it "retorna a sequência correta para 2 discos" $
      T.hanoi 2 "A" "B" "C" `shouldBe` [("A", "C"), ("A", "B"), ("C", "B")]
      
    it "retorna a sequência correta para 3 discos" $
      T.hanoi 3 "A" "B" "C" `shouldBe` [ ("A", "B"), ("A", "C"), ("B", "C"), 
                                        ("A", "B"), 
                                        ("C", "A"), ("C", "B"), ("A", "B") ]

  describe "Ação de E/S: main" $ do
    it "imprime a sequência de movimentos para 3 discos" $ do
      let input = "3\n"
      let expected = "Quantos discos? " ++
                     "A solução para mover 3 discos de A para B é:\n" ++
                     "Mova o disco de A para B\n" ++
                     "Mova o disco de A para C\n" ++
                     "Mova o disco de B para C\n" ++
                     "Mova o disco de A para B\n" ++
                     "Mova o disco de C para A\n" ++
                     "Mova o disco de C para B\n" ++
                     "Mova o disco de A para B\n"
      out <- runWithInput T.main input
      out `shouldBe` expected