[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/A4nbpe6j)
# Tarefa: Promoção de Chocolates Rotten Cocoa

## Descrição

Você implementará um programa interativo em Haskell para simular a compra de caixas de chocolate na rede de supermercados "Rotten Cocoa Market Inc.". O programa deve guiar um cliente através de um processo de compra que pode ser repetido várias vezes.

O valor unitário de uma caixa de chocolate depende da quantidade de caixas adquiridas, conforme a tabela de preços a seguir:

| Quantidade de Caixas      | Preço por Caixa |
| ------------------------- | --------------- |
| Até 10 caixas             | R$ 20,00        |
| Acima de 10 e até 30      | R$ 15,00        |
| Acima de 30 e até 60      | R$ 10,00        |
| Acima de 60 caixas        | R$ 5,00         |

Além disso, se o cliente optar por pagar com Pix, ele recebe um **desconto de 8%** sobre o valor total da compra.

## Fluxo do Programa

O programa deve seguir o seguinte algoritmo de interação:

1.  O programa se apresenta e pergunta ao cliente se ele deseja iniciar uma compra, esperando uma resposta 's' (sim) ou 'n' (não).

2.  Se a resposta for 'n', o programa imprime uma mensagem de finalização ("Fim das compras, obrigado!") e termina.

3.  Se a resposta for 's', o programa entra em um laço de compras. Este laço continua até que o cliente decida não comprar mais. Dentro de cada iteração do laço:
    - Pede-se ao cliente a quantidade de caixas de chocolate. A quantidade deve ser um **inteiro positivo e não nulo**.
    - **Se a quantidade for inválida** (menor ou igual a 0), o programa deve exibir uma mensagem de erro.
    - **Se a quantidade for válida**, o programa deve:
        - Calcular e imprimir o valor da compra (sem desconto), formatado com duas casas de precisão.
        - Perguntar ao cliente se o pagamento será com Pix ('s' ou 'n').
        - Se a resposta para o pagamento com Pix for 's', o programa aplica o desconto de 8% e imprime o novo valor da compra com o desconto.
    - Ao final de cada tentativa de compra (seja ela válida ou inválida), o programa pergunta ao cliente se ele deseja realizar uma nova compra. Se a resposta for 's', o laço continua; se for 'n', o programa imprime a mensagem de finalização e termina.

---

## Funções e Ações Sugeridas

É fortemente recomendado separar a lógica dos cálculos da interação com o usuário.

1.  **`calculaPreco :: Int -> Double`**
    * Uma **função de cálculo** que recebe a quantidade de caixas e resulta no valor total da compra (sem o desconto Pix), com base na tabela de preços. Esta função não deve realizar nenhuma E/S (como `putStrLn` ou `getLine`).

2.  **`loopDeCompras :: IO ()`**
    * Uma **ação de E/S recursiva** que implementa o laço de compras principal descrito no fluxo acima.

3.  **`main :: IO ()`**: Ação principal que inicia o programa, imprime a mensagem de boas-vindas e faz a chamada inicial para o `loopDeCompras`.

---

## Dicas e Funções Úteis

### Dica: Usando Guardas com a Expressão `case`
Para implementar a lógica de preços, que possui várias faixas condicionais, uma combinação da expressão `case` com guardas pode ser mais legível e organizada do que múltiplos `if-then-else` aninhados.

**Exemplo de Sintaxe:**
```haskell
-- Suponha que 'maybeValor' seja do tipo 'Maybe Int'
case maybeValor of
  Just valor
    | valor < 10    -> "O valor é menor que 10"
    | valor == 10   -> "O valor é exatamente 10"
    | otherwise     -> "O valor é maior que 10"
  Nothing -> "Nenhum valor foi fornecido"
```

## Formatação da Saída Numérica

A saída de valores monetários deve ser formatada para exibir sempre **duas casas de precisão**. Utilize a função `printf` do módulo `Text.Printf`.

---

## Exemplos de Execução

**Exemplo 1 (Não compra):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): n
Fim das compras, obrigado!
```

**Exemplo 2 (Compra simples, sem Pix):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: 10
Valor da compra: R$ 200.00
Informe pagamento com Pix (s/n): n
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

**Exemplo 3 (Compra simples, com Pix):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: 30
Valor da compra: R$ 450.00
Informe pagamento com Pix (s/n): s
Valor da compra com Pix: R$ 414.00
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

**Exemplo 4 (Fluxo complexo com erros):**
```shellsession
Rotten Cocoa Market
Informe se deseja comprar (s/n): s
Informe a quantidade de caixas: -8
ERRO: Quantidade inválida: -8
Informe se deseja comprar novamente (s/n): s
Informe a quantidade de caixas: 50
Valor da compra: R$ 500.00
Informe pagamento com Pix (s/n): s
Valor da compra com Pix: R$ 460.00
Informe se deseja comprar novamente (s/n): n
Fim das compras, obrigado!
```

---

## Desenvolvimento e Testes

Complete as definições nos arquivos `src/*.hs`. O seu projeto deve passar em todos os testes fornecidos.

```shellsession
$ cabal build               # Compila o projeto
$ cabal repl chocolates     # Carrega o projeto no REPL
$ cabal run chocolates      # Executa o programa
$ cabal test                # Executa os testes
```
