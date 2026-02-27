module Popularidade
  ( tabela,
    pesquisa,
    go,
    main,
  )
where

import System.IO (BufferMode (NoBuffering), hSetBuffering, stdout)
import Text.Printf (printf)
import Data.List (find)

-- | Converte o conteúdo de um arquivo em uma lista de (Ranking, Nome, Registros).
-- O ranking é determinado pela ordem das linhas (1-indexed).
tabela :: String -> [(Int, String, Int)]
tabela texto = zipWith processaLinha [1..] (lines texto)
  where
    processaLinha r ln = case words ln of
      [nome, num] -> (r, nome, read num)
      _           -> (r, "Erro", 0)

-- | Pesquisa um nome em uma tabela e imprime o resultado formatado.
pesquisa :: String -> [(Int, String, Int)] -> String -> IO ()
pesquisa tipo tabelaDeNomes nomeAlvo = 
  case find (\(_, n, _) -> n == nomeAlvo) tabelaDeNomes of
    Just (rank, _, registros) ->
      printf "%s classificado na posição %d entre %s com %d registros\n" 
             nomeAlvo rank tipo registros
    Nothing ->
      printf "%s não encontrado entre %s\n" nomeAlvo tipo

-- | Ação recursiva que mantém o estado das tabelas e processa entradas do usuário.
go :: [(Int, String, Int)] -> [(Int, String, Int)] -> IO ()
go tabGarotos tabGarotas = do
  putStr "Nome: "
  nomeInput <- getLine
  if null nomeInput
    then return () -- Encerra o programa
    else do
      -- Realiza a pesquisa em ambas as tabelas
      pesquisa "garotas" tabGarotas nomeInput
      pesquisa "garotos" tabGarotos nomeInput
      go tabGarotos tabGarotas -- Chamada recursiva para o próximo nome

-- | Ação principal: carrega arquivos, processa tabelas e inicia o loop.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  
  -- Leitura dos arquivos de dados
  conteudoGarotos <- readFile "boynames.txt"
  conteudoGarotas <- readFile "girlnames.txt"
  
  -- Geração das tabelas puras
  let tabGarotos = tabela conteudoGarotos
  let tabGarotas = tabela conteudoGarotas
  
  -- Início do laço interativo
  go tabGarotos tabGarotas