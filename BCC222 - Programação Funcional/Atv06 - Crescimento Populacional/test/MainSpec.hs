module Main (main) where

import Test.Hspec
import Run (runWithInput)
import qualified Simulador as T

main :: IO ()
main = hspec $ do
  describe "Função Pura: simulaPopulacao" $ do
    it "retorna a população inicial se anos for 0" $
      T.simulaPopulacao 100 0.5 10 0 `shouldBe` 100

    it "calcula corretamente 1 ano de crescimento (Ex: 100 * 1.1 - 5 = 105)" $
      T.simulaPopulacao 100 0.1 5 1 `shouldBe` 105

    it "calcula corretamente múltiplos anos (Exemplo do README)" $ do
      -- Ano 1: 105
      -- Ano 2: floor(105 * 1.1) - 5 = 115 - 5 = 110
      T.simulaPopulacao 100 0.1 5 2 `shouldBe` 110

    it "lida com a extinção (população chega a 0 e não fica negativa)" $ do
      -- 10 * 1.5 = 15. 15 - 20 = -5 -> deve ser 0
      T.simulaPopulacao 10 0.5 20 1 `shouldBe` 0
      -- Se já é 0, continua 0
      T.simulaPopulacao 10 0.5 20 5 `shouldBe` 0

  describe "Ação de E/S: main" $ do
    let prompts = [ "Populacao inicial: "
                  , "Taxa de crescimento (ex: 0.1): "
                  , "Colheita anual: "
                  , "Anos a simular: "
                  ]
    
    it "executa a simulação padrão corretamente" $ do
      -- Entradas: 100, 0.1, 5, 2
      let input = unlines ["100", "0.1", "5", "2"]
      let expectedOutput = concat prompts ++ "Populacao final: 110 coelhos\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "identifica entrada inválida (anos negativos)" $ do
      let input = unlines ["100", "0.1", "5", "-1"]
      let expectedOutput = concat prompts ++ "Entrada invalida\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "identifica entrada inválida (população negativa)" $ do
      let input = unlines ["-50", "0.1", "5", "2"]
      let expectedOutput = concat prompts ++ "Entrada invalida\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput
