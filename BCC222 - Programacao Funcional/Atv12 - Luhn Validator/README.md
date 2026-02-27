[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RDjExyf1)
# Tarefa: Validação de Cartão de Crédito (Algoritmo de Luhn)

## Descrição

Muitos sistemas online validam números de cartão de crédito para detectar erros de digitação simples antes mesmo de enviar os dados para processamento. Um dos algoritmos mais comuns para essa verificação é o **Algoritmo de Luhn**.

Nesta tarefa, você implementará o Algoritmo de Luhn em Haskell, dividindo o problema em uma série de pequenas funções puras que, juntas, podem validar um número de cartão de crédito.

O algoritmo segue os seguintes passos:

1.  Começando pelo penúltimo dígito (o segundo a contar da direita) e movendo-se para a esquerda, dobre o valor de cada segundo dígito.
2.  Some todos os dígitos do resultado. Se um dos números dobrados for maior que 9 (ex: 8 * 2 = 16), você deve somar os dígitos desse resultado (1 + 6 = 7).
3.  O número do cartão é válido se, e somente se, o resultado dessa soma for um múltiplo de 10 (ou seja, `mod soma 10 == 0`).

**Exemplo:**

* Número: **4012 8888 8888 1881**
* Dígitos: `[4, 0, 1, 2, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 8, 1]`
* Dobrando cada segundo dígito a partir da direita: `[8, 0, 2, 2, 16, 8, 16, 8, 16, 8, 16, 8, 2, 8, 16, 1]`
* Somando todos os dígitos individuais: `8+0+2+2+(1+6)+8+(1+6)+8+(1+6)+8+(1+6)+8+2+8+(1+6)+1 = 80`
* Verificação final:  
  `mod 80 10 == 0`  
  O número é **válido**.

---

## Funções a Implementar

Você deve implementar uma série de funções auxiliares puras no módulo `src/Luhn.hs`.

1.  **`toDigits :: Integer -> [Integer]`**
    * Converte um número inteiro não negativo em uma lista de seus dígitos.
    * Exemplo: `toDigits 1234` deve resultar em `[1, 2, 3, 4]`.
    * **Dica:** É mais fácil implementar uma função `toDigitsRev` que retorna os dígitos na ordem inversa (`[4, 3, 2, 1]`) e depois usar `reverse`.

2.  **`doubleEveryOther :: [Integer] -> [Integer]`**
    * Dobra cada segundo dígito de uma lista, começando pela direita.
    * Exemplo: `doubleEveryOther [1, 8, 8, 1]` deve resultar em `[2, 8, 16, 1]`.
    * **Dica:** Pense em como processar a lista da direita para a esquerda. Inverter a lista duas vezes (uma antes e uma depois de uma operação auxiliar) é uma estratégia comum.

3.  **`sumDigits :: [Integer] -> Integer`**
    * Calcula a soma de todos os dígitos em uma lista de inteiros.
    * Note que números maiores que 9 devem ter seus próprios dígitos somados.
    * Exemplo: `sumDigits [16, 7, 12, 5]` deve resultar em `(1+6) + 7 + (1+2) + 5 = 22`.

4.  **`validate :: Integer -> Bool`**
    * A função principal que utiliza as outras três para realizar a validação completa.
    * Ela deve retornar `True` se o número for válido e `False` caso contrário.

5.  **`main :: IO ()`**
    * Uma ação de E/S que solicita um número de cartão de crédito ao usuário, chama a função `validate` e imprime se o cartão é "Válido" ou "Inválido".

---

## Exemplos de Execução do Programa Principal

```shellsession
Digite o número do cartão de crédito: 4012888888881881
Válido
````

```shellsession
Digite o número do cartão de crédito: 4012888888881882
Inválido
```

-----

## Desenvolvimento e Testes

Complete as definições para resolver o problema. O seu projeto deve passar em todos os testes fornecidos.

```shellsession
$ cabal build               # Compila o projeto
$ cabal repl luhn-validator # Carrega o projeto no REPL (use o nome do seu pacote)
$ cabal run luhn-validator  # Executa o programa
$ cabal test                # Executa os testes
```
