module Main (main) where

import Run (runWithInput)
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck
import qualified Luhn as T

main :: IO ()
main = hspec $ do
  describe "toDigits" $ do
    it "converte um número positivo em uma lista de dígitos" $
      T.toDigits 1234 `shouldBe` [1, 2, 3, 4]
    it "converte um número de um dígito" $
      T.toDigits 5 `shouldBe` [5]
    it "converte um número terminado em 0" $
      T.toDigits 1230 `shouldBe` [1, 2, 3, 0]

  describe "doubleEveryOther" $ do
    it "dobra cada segundo dígito a partir da direita" $
      T.doubleEveryOther [8, 7, 6, 5] `shouldBe` [16, 7, 12, 5]
    it "funciona para listas com número ímpar de elementos" $
      T.doubleEveryOther [1, 8, 7, 6, 5] `shouldBe` [1, 16, 7, 12, 5]
    it "não altera listas com 0 ou 1 elemento" $ do
      T.doubleEveryOther [] `shouldBe` []
      T.doubleEveryOther [5] `shouldBe` [5]

  describe "sumDigits" $ do
    it "soma os dígitos de uma lista, tratando números de dois dígitos" $
      T.sumDigits [16, 7, 12, 5] `shouldBe` 22 -- (1+6) + 7 + (1+2) + 5
    it "soma dígitos de uma lista simples" $
      T.sumDigits [1, 2, 3] `shouldBe` 6

  describe "validate" $ do
    it "valida um número de cartão de crédito correto" $
      T.validate 4012888888881881 `shouldBe` True
    it "invalida um número de cartão de crédito incorreto" $
      T.validate 4012888888881882 `shouldBe` False

  describe "Ação de E/S: main" $ do
    it "imprime 'Válido' para um número correto" $ do
      let input = "4012888888881881\n"
      let expected = "Digite o número do cartão de crédito: " ++ "Válido\n"
      out <- runWithInput T.main input
      out `shouldBe` expected

    it "imprime 'Inválido' para um número incorreto" $ do
      let input = "4012888888881882\n"
      let expected = "Digite o número do cartão de crédito: " ++ "Inválido\n"
      out <- runWithInput T.main input
      out `shouldBe` expected
