module LogProcessor
  ( LogEntry,
    parseLog,
    filterErrors,
    countLogType,
    main
  )
where

-- Sinônimo de tipo para tornar as assinaturas mais legíveis
type LogEntry = (String, String, String)

-- Converte uma linha crua de log em uma entrada estruturada.
parseLog :: String -> LogEntry
parseLog line = case words line of
  (t : d : msgWords) -> (t, d, unwords msgWords)
  _                  -> ("UNKNOWN", "", line)

-- Retorna apenas as mensagens dos logs do tipo "ERROR".
filterErrors :: [LogEntry] -> [String]
filterErrors [] = []
filterErrors ((tipo, _, msg) : xs)
  | tipo == "ERROR" = msg : filterErrors xs
  | otherwise       = filterErrors xs

-- Conta quantos logs de um determinado tipo existem na lista.
countLogType :: String -> [LogEntry] -> Int
countLogType _ [] = 0
countLogType targetType ((tipo, _, _) : xs)
  | tipo == targetType = 1 + countLogType targetType xs
  | otherwise          = countLogType targetType xs

-- Função auxiliar recursiva para aplicar parseLog em uma lista de strings.
parseLines :: [String] -> [LogEntry]
parseLines [] = []
parseLines (x : xs) = parseLog x : parseLines xs

-- Função auxiliar recursiva para imprimir uma lista de strings.
printLines :: [String] -> IO ()
printLines [] = return ()
printLines (x : xs) = do
  putStrLn x
  printLines xs

-- Função principal
main :: IO ()
main = do
  content <- getContents
  let rawLines = lines content
  -- Passo 1: Converter todas as linhas usando recursão auxiliar
  let parsedLogs = parseLines rawLines
  
  -- Passo 2: Contar erros
  let errorCount = countLogType "ERROR" parsedLogs
  
  -- Passo 3: Obter mensagens de erro
  let errorMessages = filterErrors parsedLogs
  
  -- Saída
  putStr "Total de erros: "
  print errorCount
  putStrLn "Mensagens de erro:"
  printLines errorMessages