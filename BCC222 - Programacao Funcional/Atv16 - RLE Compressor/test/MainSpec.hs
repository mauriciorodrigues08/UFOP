module Main (main) where

import Run (runWithInput)
import Test.Hspec
import Test.Hspec.QuickCheck
import Test.QuickCheck
import qualified RLE as T

-- Gerador para strings simples (sem caracteres de controle)
genSimpleString :: Gen String
genSimpleString = listOf (elements ['a'..'z'])

main :: IO ()
main = hspec $ do
  -- ... (os testes para `comprime` e `descomprime` permanecem os mesmos) ...
  describe "Função: comprime" $ do
    it "comprime uma string com repetições" $
      T.comprime "aaabbcccca" `shouldBe` [('a', 3), ('b', 2), ('c', 4), ('a', 1)]
    it "comprime uma string sem repetições" $
      T.comprime "abcde" `shouldBe` [('a', 1), ('b', 1), ('c', 1), ('d', 1), ('e', 1)]
    it "retorna uma lista vazia para uma string vazia" $
      T.comprime "" `shouldBe` []

  describe "Função: descomprime" $ do
    it "descomprime uma lista válida" $
      T.descomprime [('a', 3), ('b', 2)] `shouldBe` Just "aaabb"
    it "retorna Nothing para contagens inválidas (zero)" $
      T.descomprime [('a', 3), ('b', 0)] `shouldBe` Nothing
    it "retorna Nothing para contagens inválidas (negativa)" $
      T.descomprime [('a', 3), ('b', -1)] `shouldBe` Nothing
    it "retorna Just \"\" para uma lista vazia" $
      T.descomprime [] `shouldBe` Just ""

  describe "Propriedade de Inversão" $ do
    prop "descomprime . comprime == Just" $
      forAll genSimpleString $ \s ->
        (T.descomprime . T.comprime) s == Just s

  describe "Ação de E/S: main" $ do
    let menuText = "-- Menu --\n" ++
                   "1) Comprimir\n" ++
                   "2) Descomprimir\n" ++
                   "*) Sair\n" ++
                   "Opção: "

    it "executa o fluxo de compressão corretamente e volta ao menu" $ do
      -- Entrada: Escolhe 1, fornece string, depois escolhe 3 para sair.
      let input = unlines ["1", "aaabbc", "3"]
      
      let outputCompressao = "Resultado: [('a',3),('b',2),('c',1)]\n" ++
                             "Verificação (ida e volta): OK\n"

      -- Saída esperada: Menu inicial, prompts, resultado, menu de novo, prompt final.
      let expectedOutput = menuText ++ 
                           "Digite o texto para comprimir: " ++
                           outputCompressao ++
                           menuText 

      out <- runWithInput T.main input
      out `shouldBe` expectedOutput

    it "executa o fluxo de descompressão corretamente e volta ao menu" $ do
      -- Entrada: Escolhe 2, fornece lista, depois escolhe 3 para sair.
      let input = unlines ["2", "[('a',2),('b',3)]", "3"]

      let outputDescompressao = "Resultado: \"aabbb\"\n" ++
                                "Verificação (ida e volta): OK\n"
      
      -- Saída esperada: Menu inicial, prompts, resultado, menu de novo, prompt final.
      let expectedOutput = menuText ++
                           "Digite a lista de pares: " ++
                           outputDescompressao ++
                           menuText
                           
      out <- runWithInput T.main input
      out `shouldBe` expectedOutput
