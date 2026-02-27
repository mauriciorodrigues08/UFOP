[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/v9IZEmEQ)
# Tarefa: Ferramenta de Compressão e Descompressão (RLE)

## Descrição

Nesta tarefa, você implementará uma ferramenta de linha de comando interativa em Haskell para compressão e descompressão de texto usando um algoritmo conhecido como Run-Length Encoding (RLE).

O objetivo é criar um par de funções, `comprime` e `descomprime`, que sejam inversas uma da outra.

1.  **Compressão:** Transforma uma string com caracteres repetidos em uma lista de pares, onde cada par contém o caractere e o número de suas repetições consecutivas.
    * **Exemplo:** `"aaabbcccca"` é comprimido para `[('a', 3), ('b', 2), ('c', 4), ('a', 1)]`.

2.  **Descompressão:** Transforma a lista de pares de volta para a string original.
    * **Exemplo:** `[('a', 3), ('b', 2)]` é descomprimido para `"aaabb"`.

O programa oferecerá um menu ao usuário, permitindo que ele escolha entre comprimir um texto, descomprimir uma lista de dados, ou sair.

---

## Funções e Ações a Implementar

O seu trabalho será dividido em duas funções de cálculo e uma ação de E/S principal que gerencia a interação.

### `comprime :: String -> [(Char, Int)]`

Uma função pura que recebe a string de entrada e resulta na lista de pares `(Char, Int)` representando os dados comprimidos.

### `descomprime :: [(Char, Int)] -> Maybe String`

* Uma função pura que recebe a lista de pares e resulta na string original expandida, empacotada em uma estrutura `Maybe`.
* **Validação:** A descompressão deve falhar (retornar `Nothing`) se a lista de entrada contiver uma contagem inválida (um número menor ou igual a zero).
* Se todos os pares forem válidos, a função deve resultar em `Just "string_descomprimida"`.

### `main :: IO ()`

Esta é a **ação de E/S** principal e deve implementar um laço interativo que se repete até que o usuário decida sair, seguindo o fluxo indicado a seguir.

---

## Fluxo do Programa

1.  O programa inicia e entra imediatamente em um laço, começando por apresentar um menu de opções ao usuário: `1) Comprimir`, `2) Descomprimir`, `*) Sair`.

2.  O programa lê a opção do usuário.

3.  **Se a opção for '1' (Comprimir):**
    *   O programa executa o fluxo de compressão:
        1.  solicitar e lê uma linha de texto
        2.  chama `comprime` e exibe o resultado.
        3.  **verifica a propriedade de inversão:** chama `descomprime` no resultado da compressão e verifica se o resultado é igual ao texto original, exibindo a mensagem apropriada: "Verificação (ida e volta): OK" ou "Verificação (ida e volta): FALHOU".
    *   Ao final, o laço recomeça, e o menu é exibido novamente.

4.  **Se a opção for '2' (Descomprimir):**
    *   O programa executa o fluxo de descompressão:
        1.  solicita e lê uma string que representa uma lista de pares (ex: `"[('a',2)]"`)
        2.  usa `readMaybe` para tentar converter a string para `Maybe [(Char, Int)]`
        3.  se a conversão falha, informa "Entrada da lista inválida."
        4.  se a conversão sucede chama `descomprime` e, usando `case`, trata o resultado:
            -   `Nothing`: informa "Resultado da descompressão: Falha (dados inválidos)"
            -   `Just str`:
                1.  exibe a string descomprimida
                2.  **verifica a propriedade de inversão:** chama `comprime` no resultado da descompressão, e verifica se o resultado é igual à lista original, exibindo a mensagem apropriada: "Verificação (ida e volta): OK" ou "Verificação (ida e lta): FALHOU".
    *   Ao final, o laço recomeça, e o menu é exibido novamente.

5.  **Se a opção for qualquer outra tecla**, o programa termina sem exibir mais nada.

---
## Dicas de Implementação

### Dicas para `comprime`: A Função `group`

* Para implementar a compressão de forma elegante, use a função `group` do módulo `Data.List`. Ela agrupa elementos iguais e adjacentes em sub-listas, simplificando muito o problema.
  * **Importação:** `import Data.List (group)`
  * **Exemplo:** `group "aaabbc"` resulta em `["aaa", "bb", "c"]`.
  * Com isso, sua tarefa se resume a transformar essa lista de strings em uma lista de pares `(Char, Int)`.

* O padrão com `@` (as-pattern) é extremamente útil aqui, como vimos em aula.

### Dicas para `descomprime`: Recursão e `case`

* A função de descompressão é um ótimo caso para uma recursão simples sobre a lista de tuplas.
* Para gerar a string de caracteres repetidos, use a função `replicate` do módulo `Data.List`. Por exemplo, `replicate 3 'a'` resulta na string `"aaa"`.
* Lembre-se de usar a expressão `case` para tratar o resultado da validação (o `Maybe String`) na sua ação `main`.

### Dica para Ler a Lista: A Função `readMaybe`

* Para ler a lista de pares na opção 2, você lerá uma `String` (ex: `"[('a',1)]"`) e precisará usar `readMaybe` para convertê-la para o tipo `Maybe [(Char, Int)]`.

---
## Testando a Inversão (Property-Based Testing)

Uma forma poderosa de verificar se suas funções estão corretas é testar a propriedade de que elas são (quase) inversas. Para qualquer `texto` que não contenha sequências inválidas, o seguinte deve ser verdade:
```haskell
descomprime (comprime texto) == Just texto
```
Nossa suíte de testes incluirá uma verificação para esta propriedade usando QuickCheck!

---

## Exemplos de Execução

**Exemplo 1: Comprimir**
```shellsession
-- Menu --
1) Comprimir
2) Descomprimir
*) Sair
Opção: 1
Digite o texto para comprimir: aaabbcccca
Resultado: [('a',3),('b',2),('c',4),('a',1)]
Verificação (ida e volta): OK
```

**Exemplo 2: Descomprimir com Sucesso**
```shellsession
-- Menu --
1) Comprimir
2) Descomprimir
*) Sair
Opção: 2
Digite a lista de pares: [('H',1),('a',1),('s',1),('k',1),('e',1),('l',2),('!',3)]
Resultado: "Haskell!!!"
Verificação (ida e volta): OK
```

**Exemplo 3: Descomprimir com Sintaxe Inválida**
```shellsession
-- Menu --
1) Comprimir
2) Descomprimir
*) Sair
Opção: 2
Digite a lista de pares: [('a',2)
Entrada da lista inválida.
```

**Exemplo 4: Descomprimir com Dados Inválidos**
```shellsession
-- Menu --
1) Comprimir
2) Descomprimir
*) Sair
Opção: 2
Digite a lista de pares: [('x',2),('y',-1)]
Resultado da descompressão: Falha (dados inválidos)
```

**Exemplo 5: Sair**
```shellsession
-- Menu --
1) Comprimir
2) Descomprimir
*) Sair
Opção: 3
```
