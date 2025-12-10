module Main (main) where

import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck
import Text.Printf (printf) -- Para ajudar a construir strings de saída esperadas
import Data.Maybe (isJust, isNothing, fromJust)
import Data.AEq ((~==))    -- Para comparação aproximada de Doubles (do pacote ieee754)

import Run (runWithInput) -- Assumindo que Run.hs está disponível e funcional
import qualified Gorjeta as T

-- Define uma pequena tolerância para comparações de Double
epsilon :: Double
epsilon = 1e-9 -- Você pode ajustar este valor conforme necessário

-- Função para comparar dois Doubles com tolerância (alternativa se não usar (~==) ou para casos específicos)
aproximadamenteIgual :: Double -> Double -> Bool
aproximadamenteIgual x y = abs (x - y) < epsilon

-- Gerador para qualidades de serviço válidas
genQualidadeValida :: Gen String
genQualidadeValida = elements ["ruim", "bom", "excelente"]

-- Gerador para qualidades de serviço inválidas (exemplos)
genQualidadeInvalida :: Gen String
genQualidadeInvalida = elements ["medio", "regular", "ok", "", "BOOM"]

-- Gerador para valores de conta positivos
genContaPositiva :: Gen Double
genContaPositiva = abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x > 0 && x < 10000 && not (isNaN x) && not (isInfinite x))

main :: IO ()
main = hspec $ do
  describe "Função gorjeta" $ do
    -- Testes de casos específicos
    it "calcula 5% para serviço 'ruim' (R$ 100.00)" $
      T.gorjeta 100.0 "ruim" `shouldSatisfy` (\res -> case res of Just g -> g ~== 5.0; Nothing -> False)

    it "calcula 10% para serviço 'bom' (R$ 100.00)" $
      T.gorjeta 100.0 "bom" `shouldSatisfy` (\res -> case res of Just g -> g ~== 10.0; Nothing -> False)

    it "calcula 15% para serviço 'excelente' (R$ 100.00)" $
      T.gorjeta 100.0 "excelente" `shouldSatisfy` (\res -> case res of Just g -> g ~== 15.0; Nothing -> False)

    it "calcula gorjeta corretamente para R$ 75.50, 'ruim' (resultando em R$ 3.775)" $
      T.gorjeta 75.50 "ruim" `shouldSatisfy` (\res -> case res of Just g -> g ~== 3.775; Nothing -> False)

    it "retorna Nothing para serviço 'medio'" $
      T.gorjeta 100.0 "medio" `shouldBe` Nothing

    it "retorna Nothing para serviço vazio" $
      T.gorjeta 100.0 "" `shouldBe` Nothing

    prop "sempre retorna Just para qualidades válidas e conta positiva não negativa" $ -- Ajustado para incluir conta = 0
      forAll (abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x >= 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \conta ->
      forAll genQualidadeValida $ \qualidade ->
        isJust (T.gorjeta conta qualidade)

    prop "retorna Nothing para conta negativa" $
      forAll ((negate . abs) <$> (arbitrary :: Gen Double) `suchThat` (\x -> x > 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \contaNegativa ->
      forAll genQualidadeValida $ \qualidade ->
        isNothing (T.gorjeta contaNegativa qualidade)

    prop "sempre retorna Nothing para qualidades inválidas (com conta não negativa)" $
      forAll (abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x >= 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \conta ->
      forAll genQualidadeInvalida $ \qualidade ->
        isNothing (T.gorjeta conta qualidade)

    prop "calcula corretamente a porcentagem para 'ruim' (com conta não negativa)" $
      forAll (abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x >= 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \conta ->
        let expectedGorjeta = conta * 0.05
        in fromJust (T.gorjeta conta "ruim") ~== expectedGorjeta

    prop "calcula corretamente a porcentagem para 'bom' (com conta não negativa)" $
      forAll (abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x >= 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \conta ->
        let expectedGorjeta = conta * 0.10
        in fromJust (T.gorjeta conta "bom") ~== expectedGorjeta

    prop "calcula corretamente a porcentagem para 'excelente' (com conta não negativa)" $
      forAll (abs <$> (arbitrary :: Gen Double) `suchThat` (\x -> x >= 0 && x < 10000 && not (isNaN x) && not (isInfinite x))) $ \conta ->
        let expectedGorjeta = conta * 0.15
        in fromJust (T.gorjeta conta "excelente") ~== expectedGorjeta

  describe "Executando o programa principal (T.main)" $ do
    let promptConta = "Digite o valor da conta: "
    let promptQualidade = "Qualidade do serviço (ruim, bom, excelente): "

    it "com qualidade de serviço inválida ('medio')" $ do
      let input = unlines ["150.0", "medio"]
      let expectedOutput = promptConta ++ promptQualidade ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "com serviço 'ruim' (R$ 75.50)" $ do
      let conta = 75.50 :: Double
      let qualidade = "ruim"
      let gorjetaEsperada = conta * 0.05
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, qualidade]
      let saidaGorjeta = printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
      let saidaTotal = printf "Total a pagar: R$ %.2f\n" totalEsperado
      let expectedOutput = promptConta ++ promptQualidade ++ saidaGorjeta ++ saidaTotal
      
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "com serviço 'bom' (R$ 100.00)" $ do
      let conta = 100.0 :: Double
      let qualidade = "bom"
      let gorjetaEsperada = conta * 0.10
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, qualidade]
      let saidaGorjeta = printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
      let saidaTotal = printf "Total a pagar: R$ %.2f\n" totalEsperado
      let expectedOutput = promptConta ++ promptQualidade ++ saidaGorjeta ++ saidaTotal

      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "com serviço 'excelente' (R$ 200.00)" $ do
      let conta = 200.0 :: Double
      let qualidade = "excelente"
      let gorjetaEsperada = conta * 0.15
      let totalEsperado = conta + gorjetaEsperada
      let input = unlines [show conta, qualidade]
      let saidaGorjeta = printf "Gorjeta: R$ %.2f\n" gorjetaEsperada
      let saidaTotal = printf "Total a pagar: R$ %.2f\n" totalEsperado
      let expectedOutput = promptConta ++ promptQualidade ++ saidaGorjeta ++ saidaTotal

      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "com valor da conta textual (inválido)" $ do
      let input = unlines ["abc", "bom"]
      -- Assumindo que o programa imprime "Entrada inválida!" logo após a falha na leitura da conta,
      -- sem pedir a qualidade do serviço.
      let expectedOutput = promptConta ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "com valor da conta negativo (inválido)" $ do
      let input = unlines ["-50.0", "bom"]
      -- A validação de conta negativa ocorre na função gorjeta, após ler a qualidade.
      let expectedOutput = promptConta ++ promptQualidade ++ "Entrada inválida!\n"
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput
