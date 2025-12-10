module Main (main) where

import Run (runWithInput)
import Test.Hspec

import qualified Overbooking as T

main :: IO ()
main = hspec $ do
  describe "Execução do programa principal (main)" $ do
    let runTest input expectedOutput = do
          out <- runWithInput T.main input
          out `shouldBe` expectedOutput

    it "processa corretamente o Exemplo 1 do README" $ do
      let input = unlines ["2", "560", "550", "350", "400"]
      
      let expected = "Rotten Cocoa Airlines Corp.\n" ++
                     "Informe a quantidade de voos: " ++
                     "Voo 1:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Voo 2:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Alerta: Voo com overbooking!\n" ++
                     "Fim da entrada dos voos:\n" ++
                     "Ocorreram 1 voos com overbooking\n" ++
                     "Ocorreram 50 passageiros acima da capacidade\n"

      runTest input expected

    it "processa corretamente o Exemplo 2 do README" $ do
      let input = unlines ["4", "100", "99", "100", "100", "100", "101", "100", "102"]

      let expected = "Rotten Cocoa Airlines Corp.\n" ++
                     "Informe a quantidade de voos: " ++
                     "Voo 1:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Voo 2:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Voo 3:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Alerta: Voo com overbooking!\n" ++
                     "Voo 4:\n" ++
                     "Capacidade da aeronave: " ++
                     "Quantidade de passagens: " ++
                     "Alerta: Voo com overbooking!\n" ++
                     "Fim da entrada dos voos:\n" ++
                     "Ocorreram 2 voos com overbooking\n" ++
                     "Ocorreram 3 passageiros acima da capacidade\n"

      runTest input expected
