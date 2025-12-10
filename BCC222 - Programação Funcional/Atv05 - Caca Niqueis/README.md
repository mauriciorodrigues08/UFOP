[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/kyOkWjbD)
# Tarefa: Caça-Níqueis

## Descrição

Você implementará um programa em Haskell que simula o pagamento de uma máquina de caça-níqueis simples. A máquina possui três cilindros, e o programa deve ler 3 caracteres, representando as frutas que aparecem no visor, e um número real, representando o valor da aposta.

As frutas são representadas pelos seguintes caracteres:
* `'a'`: abacaxi
* `'b'`: banana
* `'m'`: morango
* `'u'`: uva

Os prêmios são pagos apenas quando há bananas no visor, de acordo com a tabela abaixo:

| Cilindros                     | Valor devolvido         |
| ----------------------------- | ----------------------- |
| 3 bananas                     | 10x o valor da aposta   |
| 2 bananas em qualquer posição | 5x o valor da aposta    |
| 1 banana em qualquer posição  | o valor da aposta       |

**Regra Importante:** Se uma determinada configuração tiver direito a múltiplos prêmios (por exemplo, 3 bananas também se qualifica como "2 bananas" e "1 banana"), **apenas o maior prêmio será pago**. Se não houver prêmio (nenhuma banana), o programa deve exibir a mensagem "Tente novamente!".

---

## Funções e Ações a Implementar

É recomendado separar a lógica do cálculo do prêmio da interação com o usuário. As definições devem ser feitas em `src/CacaNiqueis.hs`.

1.  **`calculaPremio :: Char -> Char -> Char -> Double -> Double`**
    * Esta é uma **função pura** que recebe os três caracteres das frutas e o valor da aposta.
    * Ela deve resultar no valor do prêmio a ser devolvido.
    * Se não houver prêmio, a função deve retornar `0.0`.

2.  **`main :: IO ()`**
    * Esta é a **ação de E/S** principal que implementa a interação com o usuário.
    * Ela deve solicitar e ler as três frutas e o valor da aposta.
    * Deve chamar a função `calculaPremio` para determinar o valor do prêmio.
    * Se o prêmio for maior que zero, deve exibir o valor devolvido, formatado com o prefixo "R$ " e duas casas decimais.
    * Se o prêmio for zero, deve exibir a mensagem "Tente novamente!".

---

## Dica de Implementação: O Desafio do `getChar`

Ao contrário do `getLine` (que só retorna após o `Enter`), a ação `getChar` tem um comportamento que pode ser surpreendente em um terminal padrão.

* O seu terminal geralmente opera em **modo de buffer de linha**. Isso significa que, mesmo que você chame `getChar`, o terminal não envia *nada* para o seu programa (nem mesmo o primeiro caractere) até que você pressione `Enter`.
* Quando você digita `a` e pressiona `Enter`, o terminal envia a string `"a\n"` para o buffer de entrada do Haskell.
* A ação `getChar` consome o primeiro caractere (`'a'`) e o retorna.
* O caractere de nova linha (`'\n'`) **permanece no buffer**.
* A próxima vez que você chamar `getChar` (para a segunda fruta), ele lerá imediatamente o `'\n'` que sobrou, sem esperar por uma nova entrada do usuário.

**Solução Robusta:**
Para evitar isso, você pode chamar a ação `getLine` logo após cada `getChar`. O `getLine` consumirá o restante da linha (no caso, apenas o `'\n'`) e o descartará, limpando o buffer para a próxima leitura real.

**Exemplo de Padrão:**
```haskell
-- ... dentro de uma ação IO em um bloco 'do' ...
putStr "Informe a primeira fruta: "
fruta1 <- getChar
getLine -- Consome o '\n' deixado pelo 'Enter'

putStr "Informe a segunda fruta: "
fruta2 <- getChar
getLine -- Consome o '\n' deixado pelo 'Enter'
-- ... e assim por diante
````

---

## Exemplos de Execução

**Exemplo 1 (1 banana):**
```shellsession
Informe a primeira fruta: a
Informe a segunda fruta: m
Informe a terceira fruta: b
Informe o valor da aposta: 8
Valor devolvido: R$ 8.00
```

**Exemplo 2 (2 bananas):**
```shellsession
Informe a primeira fruta: b
Informe a segunda fruta: m
Informe a terceira fruta: b
Informe o valor da aposta: 5.5
Valor devolvido: R$ 27.50
```

**Exemplo 3 (Sem prêmio):**
```shellsession
Informe a primeira fruta: m
Informe a segunda fruta: m
Informe a terceira fruta: a
Informe o valor da aposta: 50
Tente novamente!
```

**Exemplo 4 (3 bananas):**
```shellsession
Informe a primeira fruta: b
Informe a segunda fruta: b
Informe a terceira fruta: b
Informe o valor da aposta: 100
Valor devolvido: R$ 1000.00
```

---

## Desenvolvimento e Testes

Complete as definições nos arquivos `src/*.hs`. O seu projeto deve passar em todos os testes fornecidos.

Você pode editar os arquivos fonte e testá-los localmente com a ferramenta _cabal_:

```shellsession
$ cabal build                 # Compila o projeto
$ cabal repl caca-niqueis     # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run caca-niqueis      # Executa o programa
$ cabal test                  # Executa os testes de verificação automática
```
