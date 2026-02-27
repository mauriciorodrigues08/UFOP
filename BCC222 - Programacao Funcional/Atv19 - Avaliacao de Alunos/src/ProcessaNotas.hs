module ProcessaNotas
  ( processaAluno,
    processa,
    main,
  )
where

import System.Environment (getArgs)
import System.Exit (exitFailure)
import System.IO (hPutStrLn, stderr)

-- | Recebe uma linha de texto (mat nome n1 n2) e retorna a linha processada com média e situação.
processaAluno :: String -> String
processaAluno linha = case words linha of
  [mat, nome, n1Str, n2Str] ->
    let n1 = read n1Str :: Double
        n2 = read n2Str :: Double
        media = (n1 + n2) / 2
        situacao
          | media >= 7.0 = "aprovado"
          | media >= 3.0 = "exame especial"
          | otherwise    = "reprovado"
    in unwords [mat, nome, n1Str, n2Str, show media, situacao]
  _ -> "" -- Ignora linhas com formato inválido

-- | Recebe todo o conteúdo de um arquivo e retorna o conteúdo processado via composição.
processa :: String -> String
processa = unlines . map processaAluno . lines

-- | Ação principal que orquestra a entrada de argumentos e E/S de arquivos.
main :: IO ()
main = do
  args <- getArgs
  case args of
    [pathIn, pathOut] -> do
      conteudo <- readFile pathIn
      let resultado = processa conteudo
      writeFile pathOut resultado
    _ -> do
      hPutStrLn stderr "Erro: Forneça exatamente dois argumentos (arquivo_entrada arquivo_saida)."
      exitFailure