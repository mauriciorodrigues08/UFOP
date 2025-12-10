[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/eQl4C8GN)
# Tarefa: Processador de Logs

## Descrição

Em sistemas reais, analisamos constantemente arquivos de log para detectar falhas ou monitorar atividades. Nesta tarefa, você construirá um pequeno processador capaz de ler linhas de log cruas, estruturá-las e extrair informações úteis.

O foco desta atividade é praticar **Casamento de Padrão** (em tuplas e listas) e **Recursão**.

**Atenção:** Como o objetivo é praticar a estrutura recursiva, você **NÃO** deve usar funções de ordem superior como `map`, `filter` ou `fold`. Você deve implementar a lógica percorrendo as listas manualmente.

### Formato do Log

Cada linha do log segue o formato:
`TIPO DATA MENSAGEM`

Exemplos:
* `INFO 2023-11-01 Servidor iniciado`
* `ERROR 2023-11-01 Falha de conexão com DB`
* `WARN 2023-11-02 Uso de memória elevado`

---

## Funções a Implementar

Trabalhe no arquivo `src/LogProcessor.hs`.

### 1. Tipos de Dados
Para facilitar, definimos um sinônimo de tipo para representar uma entrada de log estruturada:
```haskell
type LogEntry = (String, String, String)
-- (Tipo, Data, Mensagem)
````

### 2\. `parseLog :: String -> LogEntry`

Recebe uma linha de texto crua e a converte em uma tupla `LogEntry`.

  * Você pode usar as funções `words` (para quebrar a string em palavras) e `unwords` (para juntar palavras) do Prelude.
  * Use casamento de padrão na lista resultante de `words` para separar o Tipo e a Data do resto da mensagem.
  * Se a linha não tiver o formato esperado (menos de 2 palavras), devolva `("UNKNOWN", "", linha_original)`.

**Exemplo:**

```haskell
parseLog "ERROR 2023-11-01 Falha de conexão"
-- Resultado: ("ERROR", "2023-11-01", "Falha de conexão")
```

### 3\. `filterErrors :: [LogEntry] -> [String]`

Recebe uma lista de entradas de log estruturadas e retorna apenas as **mensagens** dos logs cujo tipo seja `"ERROR"`.

  * Use recursão e casamento de padrão na lista.
  * **Não** use a função `filter` do Prelude.

**Exemplo:**

```haskell
logs = [("INFO", "...", "Ok"), ("ERROR", "...", "Falha"), ("WARN", "...", "Cuidado")]
filterErrors logs
-- Resultado: ["Falha"]
```

### 4\. `countLogType :: String -> [LogEntry] -> Int`

Recebe um tipo de log alvo (ex: `"INFO"`) e uma lista de entradas. Retorna quantos logs desse tipo existem na lista.

  * Use recursão.

### 5\. `main :: IO ()`

Um programa interativo que:

1.  Lê todo o conteúdo da entrada padrão (`getContents`).
2.  Separa o conteúdo em linhas (`lines`).
3.  Converte as linhas em `LogEntry` (usando uma função auxiliar recursiva ou `parseLog` em cada uma).
4.  Imprime o número total de erros encontrados.
5.  Imprime as mensagens de todos os erros.

-----

## Desenvolvimento e Testes

Compile, execute e teste o projeto com:

```shellsession
$ cabal build                 # Compila o projeto
$ cabal repl log-processor    # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run                   # Executa o programa
$ cabal test                  # Executa os testes de verificação automática
```
