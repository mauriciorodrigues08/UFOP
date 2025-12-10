[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/h_Krr3Ge)
# Tarefa: Calculadora de Gorjetas

## Descrição

Nesta tarefa, você implementará um programa interativo em Haskell que ajuda um cliente a calcular a gorjeta com base no valor total da conta e na qualidade do serviço percebida. O programa deve seguir as seguintes diretrizes:

1.  Solicitar ao usuário o valor da conta (um número em ponto flutuante).
2.  Perguntar ao usuário a qualidade do serviço recebido. As opções válidas para a qualidade do serviço e suas respectivas porcentagens de gorjeta são:
    * `"ruim"`: 5% do valor da conta.
    * `"bom"`: 10% do valor da conta.
    * `"excelente"`: 15% do valor da conta.
3.  O programa deve calcular o valor da gorjeta e o valor total a pagar (conta + gorjeta).
4.  A saída dos valores monetários (gorjeta e total a pagar) deve ser formatada para exibir sempre **duas casas decimais** e prefixada com "R$ ". Veja a seção "Formatação da Saída Numérica" abaixo.
5.  Se a entrada do usuário para a qualidade do serviço não for uma das opções válidas ("ruim", "bom", "excelente"), o programa deve exibir a mensagem "Entrada inválida!" e encerrar. Se o valor da conta fornecido não puder ser lido como um número válido ou for negativo, o programa também deve tratar isso como uma entrada inválida (exibindo "Entrada inválida!" ou uma mensagem de erro apropriada ao falhar a leitura).

---

## Funções e Ações a Implementar

Você precisará implementar as seguintes definições no arquivo `src/Gorjeta.hs`:

1.  **`gorjeta :: Double -> String -> Maybe Double`**
    * Esta função pura recebe o valor da conta (um `Double`) e uma `String` representando a avaliação da qualidade do serviço.
    * Ela deve resultar em:
        * `Just valorCalculadoDaGorjeta` se o valor da conta for não negativo e a string de qualidade for válida.
        * `Nothing` se o valor da conta for negativo ou a string de qualidade não for uma das opções válidas.

2.  **`main :: IO ()`**
    * Esta ação de E/S implementará a interação principal com o usuário:
        * Configurar o buffering da saída para que os prompts apareçam corretamente antes da leitura da entrada (ex: usando `hSetBuffering stdout NoBuffering` no início ou `hFlush stdout` após cada `putStr`).
        * Solicitar e ler o valor da conta.
        * Solicitar e ler a qualidade do serviço.
        * Utilizar a função `gorjeta` para calcular o valor da gorjeta.
        * Com base no resultado da função `gorjeta`:
            * Se for `Just gorjValue`, calcular o total (conta + gorjValue) e imprimir a gorjeta e o total formatados.
            * Se for `Nothing` (devido à falha na leitura da conta, conta negativa, ou qualidade inválida), imprimir "Entrada inválida!".

---

## Dicas e Funções Úteis

### Convertendo Strings para Números com `readMaybe`

Ao ler a entrada do usuário (que é uma `String`), você precisará convertê-la para um `Double` para representar o valor da conta. A função `read` padrão do Haskell pode fazer isso, mas ela lança uma exceção (um erro que interrompe o programa) se a string não puder ser convertida. Para esta tarefa, uma forma mais segura e controlada é usar `readMaybe`.

* **Importação:** `readMaybe` está no módulo `Text.Read`. Adicione `import Text.Read (readMaybe)` no início do seu arquivo `src/Gorjeta.hs`.
* **Funcionamento:** `readMaybe` tenta converter uma `String` para um tipo que seja instância da classe de tipo `Read` (como `Double`, `Int`, etc.).
    * Se a conversão for bem-sucedida, ela retorna `Just valorConvertido`.
    * Se a conversão falhar (ex: a string não é um número válido), ela retorna `Nothing`.
* **Tipo:** `readMaybe :: Read a => String -> Maybe a`
* **Exemplo de Uso:**
    ```haskell
    let entradaUsuario = "123.45"
    let talvezDouble = readMaybe entradaUsuario :: Maybe Double -- resultado: Just 123.45
    
    let entradaInvalida = "abc"
    let outroTalvezDouble = readMaybe entradaInvalida :: Maybe Double -- resultado: Nothing
    ```

### Fazendo Escolhas com a Expressão `if`

Depois de usar `readMaybe` ou a sua função `gorjeta`, você terá um valor do tipo `Maybe Double`. Para lidar com os dois possíveis cenários (`Just valor` ou `Nothing`), vocês podem usar expressões condicionais e funções dispon´iveis no módulo `Data.Maybe` para analisar a estrutura `Maybe`.* **Uso com `Maybe`:** É ideal para tratar os resultados de `readMaybe` ou da sua função `gorjeta`.

* **Exemplo de Uso (dentro de uma ação `IO` em um bloco `do`):**
    ```haskell
    -- Suponha que 'maybeValorGorjeta' seja do tipo Maybe Double
    -- e contenha o resultado da chamada à sua função 'gorjeta'.
    if isJust maybeValorGorjeta
        then do
            let gorj = fromMaybe maybevalorgorjeta
            -- 'gorj' aqui é o Double de dentro do Just
            -- Faça algo com 'gorj', como calcular o total e imprimir
            let total = valorDaConta + gorj
            printf "Gorjeta: R$ %.2f\n" gorj
            printf "Total a pagar: R$ %.2f\n" total
        else do
            -- Ocorreu um erro (qualidade inválida ou conta negativa)
            putStrLn "Entrada inválida!"
    ```

Neste exemplo, a expressão `if` verifica se `maybeValorGorjeta` é `Just gorj` ou `Nothing`. Se for `Just gorj`, a variável `gorj` fica disponível no bloco de código seguinte, contendo o valor `Double`. Se for `Nothing`, o bloco de código após `Nothing ->` é avaliado.

---

## Formatação da Saída Numérica

Para garantir que os valores da gorjeta e o total a pagar sejam exibidos com o prefixo "R$ " e exatamente duas casas decimais (ex: `R$ 10.00`, `R$ 110.00`), você deverá usar a função `printf` do módulo `Text.Printf`.

* **Importação:** Adicione `import Text.Printf (printf)` no início do seu arquivo `src/Gorjeta.hs`.
* **Uso Básico:** A função `printf` permite formatar strings de forma similar à função `printf` da linguagem C. Para formatar um número de ponto flutuante (`Double`) com duas casas decimais e o prefixo "R$ ", você pode usar um especificador de formato como `"R$ %.2f"`.
    * Exemplo de uso para imprimir:
        ```haskell
        let valorNumerico = 123.456 :: Double
        printf "Valor: R$ %.2f\n" valorNumerico 
        ```
    * Saída produzida:
        ```
        Valor: R$ 123.46
        ```
    * Neste exemplo, `valorNumerico` seria uma variável do tipo `Double`. A função `printf` com um formato que termina em `\n` comporta-se de forma similar a `putStrLn` e é uma ação de E/S do tipo `IO ()`.

---


## Exemplos de Execução

```shellsession
Digite o valor da conta: 100.0
Qualidade do serviço (ruim, bom, excelente): bom
Gorjeta: R$ 10.00
Total a pagar: R$ 110.00
```

```shellsession
Digite o valor da conta: 200.0
Qualidade do serviço (ruim, bom, excelente): excelente
Gorjeta: R$ 30.00
Total a pagar: R$ 230.00
```

```shellsession
Digite o valor da conta: 75.50
Qualidade do serviço (ruim, bom, excelente): ruim
Gorjeta: R$ 3.78
Total a pagar: R$ 79.28
```

```shellsession
Digite o valor da conta: 150.0
Qualidade do serviço (ruim, bom, excelente): medio
Entrada inválida!
```

```shellsession
Digite o valor da conta: abc
Entrada inválida!
```

---

Complete as definições em `src/Gorjeta.hs`. O seu projeto deve passar em todos os testes fornecidos.

Você pode editar os arquivos fonte em um editor de texto e testá-lo diretamente no ambiente interativo ou com a ferramenta _cabal_ em um terminal:

```shellsession
$ cabal build             # compila o projeto
$ cabal repl gorjetas     # carrega o projeto no ambiente interativo
$ cabal run gorjetas      # executa o programa
$ cabal test              # executa os testes
```
