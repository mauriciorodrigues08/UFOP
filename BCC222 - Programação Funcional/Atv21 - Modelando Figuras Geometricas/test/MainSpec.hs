module Main (main) where

import Test.Hspec
import Figuras

main :: IO ()
main = hspec $ do
  -- Instancia um Triangulo para usar nos testes.
  -- Nota: Isso só compilará se o aluno adicionar o construtor ao tipo Figura.
  let t = Triangulo 3.0 4.0 5.0
  let te = Triangulo 5.0 5.0 5.0

  describe "Função: area" $ do
    it "calcula a área de um Círculo" $
      area (Circulo 1) `shouldBe` pi
      
    it "calcula a área de um Retângulo" $
      area (Retangulo 4 5) `shouldBe` 20
      
    it "calcula a área de um Triângulo (Fórmula de Heron)" $
      -- O semi-perímetro de (3,4,5) é (3+4+5)/2 = 6
      -- A área é sqrt(6 * (6-3) * (6-4) * (6-5)) = sqrt(6 * 3 * 2 * 1) = sqrt(36) = 6
      area t `shouldBe` 6.0

  describe "Função: perimetro" $ do
    it "calcula o perímetro de um Círculo" $
      perimetro (Circulo 1) `shouldBe` (2 * pi)
      
    it "calcula o perímetro de um Retângulo" $
      perimetro (Retangulo 4 5) `shouldBe` 18
      
    it "calcula o perímetro de um Triângulo" $
      perimetro t `shouldBe` 12

  describe "Função: ehRegular" $ do
    it "identifica um Círculo como regular" $
      ehRegular (Circulo 10) `shouldBe` True

    it "identifica um Retângulo não-quadrado como irregular" $
      ehRegular (Retangulo 4 5) `shouldBe` False
      
    it "identifica um Quadrado (Retângulo) como regular" $
      ehRegular (Retangulo 5 5) `shouldBe` True
      
    it "identifica um Triângulo não-equilátero como irregular" $
      ehRegular t `shouldBe` False
      
    it "identifica um Triângulo equilátero como regular" $
      ehRegular te `shouldBe` True
