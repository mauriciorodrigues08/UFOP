[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/R3tlZImN)
# Tarefa: Consulta de Popularidade de Nomes

## Descrição

Nesta tarefa, você implementará um programa em Haskell que permite ao usuário consultar a popularidade de nomes próprios a partir de dados fornecidos em arquivos. O programa lerá dois arquivos, um com nomes de garotos (`boynames.txt`) e outro com nomes de garotas (`girlnames.txt`), contendo os 1.000 nomes mais populares nos Estados Unidos para o ano de 2003, compilados pela Administração da Segurança Social.

Após carregar os dados, o programa entrará em um laço interativo, permitindo que o usuário digite um nome e veja sua classificação de popularidade e o número de registros, ou uma mensagem caso o nome não seja encontrado.

## Fluxo do Programa

1.  No início, o programa deve ler e processar os arquivos `boynames.txt` e `girlnames.txt` para criar as tabelas de dados em memória.
2.  Em seguida, o programa entra em um laço interativo que se repete:
    a. Exibe o prompt `Nome: ` e aguarda a entrada do usuário.
    b. Lê uma linha de texto.
    c. Se a linha estiver em branco, o programa deve terminar.
    d. Se um nome for digitado, o programa deve pesquisar este nome em **ambas** as listas (garotos e garotas) e exibir o resultado para cada uma.
    e. O laço então recomeça do passo (a).

---

## Formato dos Arquivos de Entrada

O repositório template incluirá os arquivos `boynames.txt` e `girlnames.txt`. Cada linha desses arquivos contém um nome, seguido por um espaço e o número de registros daquele nome no ano. A popularidade (ranking) é determinada pela posição da linha no arquivo (a primeira linha é o 1º mais popular, a segunda é o 2º, e assim por diante).

**Exemplo (`girlnames.txt`):**
```

Emily 25494
Emma 22532
Madison 19986
...

````

---

## Funções a Implementar

Recomenda-se fortemente que você divida seu programa nas seguintes funções, a serem implementadas em `src/Popularidade.hs`, conforme as dicas do livro-texto:

1.  **`tabela :: String -> [(Int, String, Int)]`**
    * Uma função **pura** que recebe o conteúdo de um dos arquivos como uma única `String` e o transforma em uma lista de tuplas. Cada tupla deve conter `(Ranking, Nome, Número de Registros)`.

2.  **`pesquisa :: String -> [(Int, String, Int)] -> String -> IO ()`**
    * Uma **ação de E/S** que recebe o tipo da lista ("garotos" ou "garotas"), a tabela de dados correspondente, e o nome a ser pesquisado. A ação deve imprimir o resultado formatado na tela (se o nome foi encontrado ou não).

3.  **`go :: [(Int, String, Int)] -> [(Int, String, Int)] -> IO ()`**
    * A **ação de E/S recursiva** principal que implementa o laço interativo. Ela recebe as duas tabelas de nomes (garotos e garotas), solicita a entrada do usuário e chama `pesquisa` para cada tabela.

4.  **`main :: IO ()`**
    * A **ação de E/S** que orquestra todo o programa. Ela deve:
        * Configurar o buffering de saída (`hSetBuffering stdout NoBuffering`).
        * Ler os dois arquivos (`readFile`).
        * Chamar a função `tabela` para processar o conteúdo de cada arquivo.
        * Iniciar o laço interativo chamando a ação `go` com as tabelas processadas.

---

## Exemplos de Execução

Seu programa deve replicar o comportamento dos exemplos abaixo:

**Exemplo 1:**
```shellsession
Nome: Justice
Justice classificado na posição 456 entre garotas com 655 registros
Justice classificado na posição 401 entre garotos com 653 registros
Nome: 
````

**Exemplo 2:**

```shellsession
Nome: Walter
Walter não encontrado entre garotas
Walter classificado na posição 356 entre garotos com 775 registros
Nome: 
```
