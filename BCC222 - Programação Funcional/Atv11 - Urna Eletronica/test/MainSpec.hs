module Main (main) where

import Test.Hspec
import Run (runWithInput)
import qualified Urna as U

main :: IO ()
main = hspec $ do
  describe "Urna Eletronica" $ do
    
    it "encerra imediatamente com voto 0 e mostra tudo zerado" $ do
      let input = "0\n"
      output <- runWithInput U.main input
      
      output `shouldContain` "Lambda: 0"
      output `shouldContain` "Monad:  0"
      output `shouldContain` "Curry:  0"
      output `shouldContain` "Nulos:  0"
      output `shouldContain` "Total:  0"

    it "contabiliza votos corretamente para cada candidato" $ do
      -- Votos: 1 (Lambda), 2 (Monad), 3 (Curry), 1 (Lambda), 0 (Fim)
      let input = unlines ["1", "2", "3", "1", "0"]
      output <- runWithInput U.main input
      
      output `shouldContain` "Lambda: 2"
      output `shouldContain` "Monad:  1"
      output `shouldContain` "Curry:  1"
      output `shouldContain` "Nulos:  0"
      output `shouldContain` "Total:  4"

    it "contabiliza votos nulos corretamente" $ do
      -- Votos: 5 (Nulo), 8 (Nulo), 1 (Lambda), 0 (Fim)
      let input = unlines ["5", "8", "1", "0"]
      output <- runWithInput U.main input
      
      output `shouldContain` "Lambda: 1"
      output `shouldContain` "Nulos:  2"
      output `shouldContain` "Total:  3"

    it "interage com mensagens de feedback a cada voto" $ do
      let input = unlines ["1", "0"]
      output <- runWithInput U.main input
      output `shouldContain` "Voto computado para Lambda."
