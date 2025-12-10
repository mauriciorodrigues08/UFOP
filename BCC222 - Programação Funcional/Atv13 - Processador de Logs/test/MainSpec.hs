module Main (main) where

import Run (runWithInput)
import Test.Hspec
import qualified LogProcessor as L

-- Dados de exemplo para os testes
exLogs :: [L.LogEntry]
exLogs =
  [ ("INFO", "2023-01-01", "System start"),
    ("ERROR", "2023-01-02", "Connection timeout"),
    ("WARN", "2023-01-03", "Low memory"),
    ("ERROR", "2023-01-04", "Disk full")
  ]

main :: IO ()
main = hspec $ do
  describe "parseLog" $ do
    it "analisa corretamente uma linha de log padrão" $
      L.parseLog "INFO 2023-11-01 Servidor iniciado" `shouldBe` ("INFO", "2023-11-01", "Servidor iniciado")
    
    it "lida com mensagens contendo várias palavras" $
      L.parseLog "ERROR 2023-11-02 Falha crítica no banco de dados" `shouldBe` ("ERROR", "2023-11-02", "Falha crítica no banco de dados")

    it "lida com linhas mal formadas (fallback)" $
      let (tipo, _, _) = L.parseLog "Lixo"
      in tipo `shouldBe` "UNKNOWN"

  describe "filterErrors" $ do
    it "retorna lista vazia se não houver erros" $
      L.filterErrors [("INFO", "d", "m"), ("WARN", "d", "m")] `shouldBe` []
    
    it "extrai as mensagens apenas dos logs de erro" $
      L.filterErrors exLogs `shouldBe` ["Connection timeout", "Disk full"]

  describe "countLogType" $ do
    it "conta corretamente logs do tipo INFO" $
      L.countLogType "INFO" exLogs `shouldBe` 1
    
    it "conta corretamente logs do tipo ERROR" $
      L.countLogType "ERROR" exLogs `shouldBe` 2
      
    it "retorna 0 para tipos inexistentes" $
      L.countLogType "DEBUG" exLogs `shouldBe` 0

  describe "Integração (main)" $ do
    it "Lê logs da entrada e imprime contagem e erros" $ do
      let input = unlines 
            [ "INFO 2023-01-01 Start"
            , "ERROR 2023-01-02 Falha 1"
            , "WARN 2023-01-03 Aviso"
            , "ERROR 2023-01-04 Falha 2"
            ]
      -- O formato exato da saída pode variar dependendo da implementação do aluno,
      -- mas deve conter o número 2 e as mensagens de erro.
      output <- runWithInput L.main input
      output `shouldContain` "2"
      output `shouldContain` "Falha 1"
      output `shouldContain` "Falha 2"
      output `shouldNotContain` "Start"
