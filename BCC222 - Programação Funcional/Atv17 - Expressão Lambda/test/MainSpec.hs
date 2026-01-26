module Main (main) where

import Test.Hspec
import qualified Exercicios as E

main :: IO ()
main = hspec $ do
  describe "Exercício 1: Refatorando para Lambdas" $ do
    it "somaQuadradosParesLambda funciona corretamente" $
      E.somaQuadradosParesLambda [1, 2, 3, 4, 5, 6] `shouldBe` 56 -- 2*2 + 4*4 + 6*6 = 4 + 16 + 36

    it "stringsMaioresQue5Lambda funciona corretamente" $
      -- CORREÇÃO AQUI: O resultado esperado é apenas ["haskell"]
      E.stringsMaioresQue5Lambda ["haskell", "é", "muito", "legal"] `shouldBe` ["haskell"]
      
    it "adicionaExclamacaoParLambda funciona corretamente" $
      E.adicionaExclamacaoParLambda ["oi", "tudo", "bem", "com", "voce"] `shouldBe` ["oi!", "tudo!", "voce!"]

  describe "Exercício 2: Funções Especializadas com Aplicação Parcial" $ do
    it "ehVogal funciona corretamente" $ do
      E.ehVogal 'a' `shouldBe` True
      E.ehVogal 'b' `shouldBe` False
      E.ehVogal 'e' `shouldBe` True

    it "adicionaCom funciona corretamente" $
      E.adicionaCom "google" `shouldBe` "google.com"

    it "subtraiDe10 funciona corretamente" $
      E.subtraiDe10 3 `shouldBe` 7
      
  describe "Exercício 3: Processamento de Dados" $ do
    it "aplicaTaxa funciona corretamente" $
      let vendas = [("Produto A", 25.0), ("Produto B", 120.0), ("Produto C", 45.0)]
      in E.aplicaTaxa vendas `shouldBe` [("Produto A", 25.0), ("Produto B", 132.0), ("Produto C", 45.0)]
      
    it "alunosAprovados funciona corretamente" $
      let alunos = [("Ana", 8.0, 8.0), ("Beto", 5.0, 7.0), ("Carla", 9.0, 10.0)] -- Médias: 8.0, 6.0, 9.5
      in E.alunosAprovados alunos `shouldBe` ["Ana", "Carla"]
      
    it "aplicaDesconto funciona corretamente" $
      let vendas = [("A", 100.0), ("B", 20.0)]
      in E.aplicaDesconto vendas `shouldBe` [("A", 95.0), ("B", 19.0)]
