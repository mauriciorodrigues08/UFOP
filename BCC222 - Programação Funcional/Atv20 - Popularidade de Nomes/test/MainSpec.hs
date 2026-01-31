module Main (main) where

import Run (runWithInput)
import Test.Hspec
import qualified Popularidade as T
import System.Directory (createDirectory, removeDirectoryRecursive, withCurrentDirectory)
import System.FilePath ((</>))
import System.IO (writeFile)
import Control.Exception (bracket)

-- Conteúdo de exemplo para os arquivos de nomes
sampleBoys :: String
sampleBoys = unlines ["Michael 42721", "Christopher 30993", "Jason 30043"]

sampleGirls :: String
sampleGirls = unlines ["Jessica 46914", "Jennifer 41584", "Amanda 33177"]

main :: IO ()
main = hspec $ do
  describe "Função Pura: tabela" $ do
    it "processa corretamente o conteúdo de um arquivo de nomes" $ do
      let resultado = T.tabela sampleBoys
      resultado `shouldBe` [(1, "Michael", 42721), (2, "Christopher", 30993), (3, "Jason", 30043)]

  describe "Ação de E/S: main" $ do
    it "lê os arquivos e responde corretamente às consultas" $ do
      let tempDir = "temp_test_dir"
      let boyFile = tempDir </> "boynames.txt"
      let girlFile = tempDir </> "girlnames.txt"
      
      -- A entrada do usuário para o teste: consulta "Jason", depois "Amanda", depois linha em branco para sair.
      let userInput = "Jason\nAmanda\n\n"
      
      let setup = do
            createDirectory tempDir
            writeFile boyFile sampleBoys
            writeFile girlFile sampleGirls
      
      let cleanup = \_ -> removeDirectoryRecursive tempDir

      bracket setup cleanup $ \_ -> do
        -- CORREÇÃO: Executa a ação 'main' DENTRO do diretório temporário
        out <- withCurrentDirectory tempDir $ runWithInput T.main userInput
        
        -- Verifica as saídas esperadas
        out `shouldContain` "Jason classificado na posição 3 entre garotos com 30043 registros"
        out `shouldContain` "Jason não encontrado entre garotas"
        out `shouldContain` "Amanda não encontrado entre garotos"
        out `shouldContain` "Amanda classificado na posição 3 entre garotas com 33177 registros"
