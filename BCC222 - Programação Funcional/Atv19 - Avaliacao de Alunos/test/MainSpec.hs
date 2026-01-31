module Main (main) where

import Run (runWithInput)
import Test.Hspec
import qualified ProcessaNotas as T
import System.Environment (withArgs)
import System.Directory (removeFile, doesFileExist)
import Control.Exception (bracket)

main :: IO ()
main = hspec $ do
  describe "Função Pura: processaAluno" $ do
    it "processa corretamente um aluno reprovado" $
      T.processaAluno "1234 Pedro 1.5 1.7" `shouldBe` "1234 Pedro 1.5 1.7 1.6 reprovado"
    
    it "processa corretamente um aluno em exame especial" $
      T.processaAluno "1111 Carla 6.2 7.0" `shouldBe` "1111 Carla 6.2 7.0 6.6 exame especial"

    it "processa corretamente um aluno aprovado" $
      T.processaAluno "2121 Rafael 8.1 8.8" `shouldBe` "2121 Rafael 8.1 8.8 8.45 aprovado"

  describe "Função Pura: processa" $ do
    it "processa o conteúdo de um arquivo inteiro" $ do
      let input = "1234 Pedro 1.5 1.7\n1111 Carla 6.2 7.0"
      let expected = "1234 Pedro 1.5 1.7 1.6 reprovado\n1111 Carla 6.2 7.0 6.6 exame especial\n"
      T.processa input `shouldBe` expected

  describe "Ação de E/S: main" $ do
    it "lê de um arquivo e escreve em outro corretamente" $ do
      let inputFile = "temp_notas.txt"
      let outputFile = "temp_resultados.txt"
      let inputContent = "9999 Teste 9.0 9.0\n"
      let expectedOutputContent = "9999 Teste 9.0 9.0 9.0 aprovado\n"
      
      -- bracket garante que os arquivos são criados e limpos mesmo se o teste falhar
      bracket (writeFile inputFile inputContent) 
              (\_ -> removeFile inputFile >> removeFile outputFile) 
              (\_ -> do
                  -- Executa a ação main com os argumentos de arquivo corretos
                  withArgs [inputFile, outputFile] T.main
                  
                  -- Verifica o conteúdo do arquivo de saída
                  fileExists <- doesFileExist outputFile
                  fileExists `shouldBe` True
                  
                  actualOutputContent <- readFile outputFile
                  actualOutputContent `shouldBe` expectedOutputContent)
