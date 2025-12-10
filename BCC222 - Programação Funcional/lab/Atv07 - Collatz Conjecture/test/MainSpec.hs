module Main (main) where

import Test.Hspec
import Run (runWithInput)
import qualified Collatz as T

main :: IO ()
main = hspec $ do
  describe "Função Pura: analisaTrajetoria" $ do
    it "retorna (0, 1) para o caso base n=1" $
      T.analisaTrajetoria 1 `shouldBe` (0, 1)

    it "calcula corretamente para n=2 (1 passo, max 2)" $
      T.analisaTrajetoria 2 `shouldBe` (1, 2)

    it "calcula corretamente para n=6 (8 passos, max 16)" $
      T.analisaTrajetoria 6 `shouldBe` (8, 16)

    it "calcula corretamente para n=27 (111 passos, max 9232)" $
      T.analisaTrajetoria 27 `shouldBe` (111, 9232)

    it "calcula corretamente para n=12 (9 passos, max 16)" $
      -- 12 -> 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
      T.analisaTrajetoria 12 `shouldBe` (9, 16)

  describe "Ação de E/S: main" $ do
    it "executa a análise para n=6" $ do
      let input = "6\n"
      let expectedOutput = "Digite um numero positivo: Passos ate 1: 8\nValor maximo: 16\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "executa a análise para n=27" $ do
      let input = "27\n"
      let expectedOutput = "Digite um numero positivo: Passos ate 1: 111\nValor maximo: 9232\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "identifica entrada inválida (0)" $ do
      let input = "0\n"
      let expectedOutput = "Digite um numero positivo: Entrada invalida\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "identifica entrada inválida (negativo)" $ do
      let input = "-10\n"
      let expectedOutput = "Digite um numero positivo: Entrada invalida\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput
