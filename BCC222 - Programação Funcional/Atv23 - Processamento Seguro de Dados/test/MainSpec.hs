module Main (main) where

import Test.Hspec
import Result

main :: IO ()
main = hspec $ do
  describe "Instância de Functor para Result" $ do
    it "mapeia uma função sobre um valor Ok" $
      fmap (+10) (Ok 5) `shouldBe` Ok 15
      
    it "propaga um Error ao mapear" $
      fmap (+10) (Error "Falha" :: Result Int) `shouldBe` Error "Falha"

  describe "Instância de Applicative para Result" $ do
    it "pure coloca um valor em um contexto Ok" $
      (pure 5 :: Result Int) `shouldBe` Ok 5
      
    it "aplica uma função Ok a um valor Ok" $
      (pure (*2) <*> Ok 10) `shouldBe` Ok 20
      
    it "propaga o erro se a função for Error" $
      (Error "Função falhou" <*> Ok 10 :: Result Integer) `shouldBe` Error "Função falhou"

    it "propaga o erro se o valor for Error" $
      (pure (*2) <*> (Error "Valor falhou" :: Result Int)) `shouldBe` Error "Valor falhou"
      
    it "propaga o primeiro erro se ambos forem Error" $
      (Error "Erro 1" <*> Error "Erro 2" :: Result Int) `shouldBe` Error "Erro 1"

  describe "Instância de Monad para Result" $ do
    it "encadeia duas computações Ok" $
      (Ok 10 >>= (\x -> Ok (x * 2))) `shouldBe` Ok 20
      
    it "propaga o erro na primeira computação" $
      ((Error "Falha 1" :: Result Int) >>= (\x -> Ok (x * 2))) `shouldBe` Error "Falha 1"
      
    it "propaga o erro na segunda computação" $
      (Ok 10 >>= (\_ -> Error "Falha 2" :: Result Int)) `shouldBe` Error "Falha 2"
