module Main (main) where

import Data.AEq ((~==))
import Run (runWithInput)
import Test.Hspec
import Text.Printf (printf)
import qualified CacaNiqueis as T

main :: IO ()
main = hspec $ do
  describe "Função Pura: calculaPremio" $ do
    it "retorna 0.0 quando não há bananas" $
      T.calculaPremio 'a' 'm' 'u' 50.0 `shouldBe` 0.0

    it "retorna 1x a aposta para 1 banana" $
      T.calculaPremio 'a' 'b' 'm' 8.0 `shouldBe` 8.0

    it "retorna 5x a aposta para 2 bananas" $
      T.calculaPremio 'b' 'm' 'b' 5.5 `shouldSatisfy` (~== 27.5)

    it "retorna 10x a aposta para 3 bananas (maior prêmio)" $
      T.calculaPremio 'b' 'b' 'b' 100.0 `shouldSatisfy` (~== 1000.0)

  describe "Ação de E/S: main" $ do
    let runTest input expectedOutput = do
          out <- runWithInput T.main input
          out `shouldBe` expectedOutput

    let promptFruta1 = "Informe a primeira fruta: "
    let promptFruta2 = "Informe a segunda fruta: "
    let promptFruta3 = "Informe a terceira fruta: "
    let promptAposta = "Informe o valor da aposta: "
    let allPrompts = promptFruta1 ++ promptFruta2 ++ promptFruta3 ++ promptAposta

    it "imprime o prêmio para 1 banana (Exemplo 1)" $ do
      let input = unlines ["a", "m", "b", "8"]
      let expected = printf "Valor devolvido: R$ %.2f\n" (8.00 :: Double)
      runTest input (allPrompts ++ expected)

    it "imprime o prêmio para 2 bananas (Exemplo 2)" $ do
      let input = unlines ["b", "m", "b", "5.5"]
      let expected = printf "Valor devolvido: R$ %.2f\n" (27.50 :: Double)
      runTest input (allPrompts ++ expected)

    it "imprime 'Tente novamente!' para 0 bananas (Exemplo 3)" $ do
      let input = unlines ["m", "m", "a", "50"]
      let expected = "Tente novamente!\n"
      runTest input (allPrompts ++ expected)

    it "imprime o prêmio para 3 bananas (Exemplo 4)" $ do
      let input = unlines ["b", "b", "b", "100"]
      let expected = printf "Valor devolvido: R$ %.2f\n" (1000.00 :: Double)
      runTest input (allPrompts ++ expected)
