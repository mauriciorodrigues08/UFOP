[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/hsMZMF8d)
# Tarefa: Processador de Notas de Alunos

## Descrição

Nesta tarefa, você construirá uma ferramenta de linha de comando em Haskell que processa um arquivo contendo as notas dos alunos e gera um novo arquivo com as médias e a situação final de cada um.

O programa seguirá o padrão de design "Núcleo Funcional, Camada de E/S", onde a lógica de cálculo será pura e a manipulação de arquivos e argumentos será contida na ação `main`.

## Fluxo do Programa

1.  O programa deve ser executado a partir da linha de comando, recebendo exatamente **dois argumentos**:
    * O caminho para o **arquivo de entrada** com as notas.
    * O caminho para o **arquivo de saída** onde o resultado será salvo.
2.  Se o número de argumentos for diferente de dois, o programa deve terminar com um status de erro.
3.  O programa deve ler o conteúdo do arquivo de entrada.
4.  Cada linha do arquivo de entrada será processada para calcular a média das notas e determinar a situação do aluno.
5.  O resultado processado deve ser escrito no arquivo de saída, sobrescrevendo qualquer conteúdo anterior.

---

## Formato dos Arquivos

#### Arquivo de Entrada

O arquivo de entrada é um arquivo de texto simples onde cada linha representa um aluno e contém as seguintes informações, separadas por espaços:
`[matrícula] [nome] [nota1] [nota2]`

**Exemplo (`notas.txt`):**
```
1234 Pedro 1.5 1.7
1111 Carla 6.2 7.0
2121 Rafael 8.1 8.8
```

#### Arquivo de Saída

O arquivo de saída gerado deve conter as mesmas informações do arquivo de entrada, com a adição da **média** e da **situação** do aluno no final de cada linha.

A situação é determinada pela média:
* `media >= 7.0`: "aprovado"
* `3.0 <= media < 7.0`: "exame especial"
* `media < 3.0`: "reprovado"

**Exemplo de saída (`resultados.txt`):**
```
1234 Pedro 1.5 1.7 1.6 reprovado
1111 Carla 6.2 7.0 6.6 exame especial
2121 Rafael 8.1 8.8 8.45 aprovado
````
---

## Funções a Implementar

Você deve estruturar seu código no módulo `src/ProcessaNotas.hs` com as seguintes funções:

1.  **`processaAluno :: String -> String`**
    * Uma função **pura** que recebe uma única linha do arquivo de entrada e retorna a linha formatada para o arquivo de saída, com a média e a situação calculadas.

2.  **`processa :: String -> String`**
    * Uma função **pura** que recebe o conteúdo *completo* do arquivo de entrada como uma única `String`, processa cada linha usando `processaAluno`, e retorna o conteúdo *completo* a ser escrito no arquivo de saída.
    * **Dica:** Use as funções `lines`, `unlines` e `map`. A composição de funções (`.`) pode tornar esta definição muito elegante.

3.  **`main :: IO ()`**
    * A **ação de E/S** que orquestra o programa. Ela deve:
        * Ler os argumentos da linha de comando (`getArgs`).
        * Validar se o número de argumentos é 2. Se não for, encerrar (`exitFailure`).
        * Ler o conteúdo do arquivo de entrada (`readFile`).
        * Chamar a função pura `processa` para transformar o conteúdo.
        * Escrever o resultado no arquivo de saída (`writeFile`).

---

## Exemplo de Execução no Terminal

```shellsession
$ cabal run avaliacao-alunos -- notas.txt resultados.txt
````

Após a execução, um arquivo chamado `resultados.txt` deve ter sido criado com o conteúdo processado.
