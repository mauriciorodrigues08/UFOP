module Main (main) where

import Data.AEq ((~==))
import Run (runWithInput)
import Test.Hspec
import Text.Printf (printf)
import qualified Chocolates as T

main :: IO ()
main = hspec $ do
  describe "Função Pura: calculaPreco" $ do
    it "calcula corretamente para a primeira faixa de preço (<= 10)" $
      T.calculaPreco 10 `shouldSatisfy` (~== 200.0)

    it "calcula corretamente para a segunda faixa de preço (> 10 e <= 30)" $
      T.calculaPreco 11 `shouldSatisfy` (~== 165.0)

    it "calcula corretamente para a terceira faixa de preço (> 30 e <= 60)" $
      T.calculaPreco 31 `shouldSatisfy` (~== 310.0)

    it "calcula corretamente para a quarta faixa de preço (> 60)" $
      T.calculaPreco 61 `shouldSatisfy` (~== 305.0)

  describe "Ação de E/S: main" $ do
    let runTest input expectedOutput = do
          out <- runWithInput T.main input
          out `shouldBe` expectedOutput
          
    it "encerra imediatamente se o usuário não quiser comprar" $ do
      let input = "n\n"
      let expected = "Rotten Cocoa Market\n" ++
                     "Informe se deseja comprar (s/n): " ++
                     "Fim das compras, obrigado!\n"
      runTest input expected

    it "executa o fluxo complexo do Exemplo 2 do README" $ do
      let input = unlines
            [ "s",    -- Deseja comprar? Sim
              "-8",   -- Quantidade inválida
              "s",    -- Comprar novamente? Sim
              "8",    -- 8 caixas
              "n",    -- Pagar com Pix? Não
              "s",    -- Comprar novamente? Sim
              "50",   -- 50 caixas
              "s",    -- Pagar com Pix? Sim
              "s",    -- Comprar novamente? Sim
              "0",    -- Quantidade inválida
              "n"     -- Comprar novamente? Não
            ]
      
      let promptInicial = "Rotten Cocoa Market\nInforme se deseja comprar (s/n): "
      let promptQtde = "Informe a quantidade de caixas: "
      let promptPix = "Informe pagamento com Pix (s/n): "
      let promptNovamente = "Informe se deseja comprar novamente (s/n): "

      let saidaParte1 = promptQtde ++ "ERRO: Quantidade inválida: -8\n" ++ promptNovamente
      let saidaParte2 = promptQtde ++ (printf "Valor da compra: R$ %.2f\n" (160.00 :: Double)) ++ promptPix ++ promptNovamente
      let saidaParte3 = promptQtde ++ (printf "Valor da compra: R$ %.2f\n" (500.00 :: Double)) ++ promptPix ++ (printf "Valor da compra com Pix: R$ %.2f\n" (460.00 :: Double)) ++ promptNovamente
      let saidaParte4 = promptQtde ++ "ERRO: Quantidade inválida: 0\n" ++ promptNovamente
      let saidaFinal = "Fim das compras, obrigado!\n"

      let expected = promptInicial ++ saidaParte1 ++ saidaParte2 ++ saidaParte3 ++ saidaParte4 ++ saidaFinal

      runTest input expected
