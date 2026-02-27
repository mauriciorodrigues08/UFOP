module Exercicios where

import Data.Char (toLower)

-- Definições de tipo para o Exercício 3
type Venda = (String, Double)
type Aluno = (String, Double, Double) -- nome, nota1, nota2

--
-- Exercício 1: Refatorando para Lambdas
--

-- 1.1: Refatorado para usar lambdas no map e filter
somaQuadradosParesLambda :: [Int] -> Int
somaQuadradosParesLambda xs = sum (map (\x -> x * x) (filter (\x -> even x) xs))

-- 1.2: Refatorado para usar lambda no filter
stringsMaioresQue5Lambda :: [String] -> [String]
stringsMaioresQue5Lambda xs = filter (\s -> length s > 5) xs

-- 1.3: Refatorado para usar lambdas no map e filter
adicionaExclamacaoParLambda :: [String] -> [String]
adicionaExclamacaoParLambda xs = map (\s -> s ++ "!") (filter (\s -> even (length s)) xs)


--
-- Exercício 2: Funções Especializadas com Aplicação Parcial e Seções
--

-- 2.1: Usa a seção (`elem` "aeiou") para verificar vogais minúsculas
ehVogal :: Char -> Bool
ehVogal = (`elem` "aeiou")

-- 2.2: Usa a seção (++ ".com") para concatenar o sufixo
adicionaCom :: String -> String
adicionaCom = (++ ".com")

-- 2.3: Seção de operador para calcular 10 - x
subtraiDe10 :: Int -> Int
subtraiDe10 = (10 -)


--
-- Exercício 3: Processamento de Dados com Lambdas e Padrões
--

-- 3.1: Usa lambda com pattern matching para verificar preço e aplicar taxa
aplicaTaxa :: [Venda] -> [Venda]
aplicaTaxa = map (\(item, preco) -> if preco > 50.0 then (item, preco * 1.1) else (item, preco))

-- 3.2: Filtra pela média e então mapeia para extrair apenas o nome
alunosAprovados :: [Aluno] -> [String]
alunosAprovados alunos = map (\(nome, _, _) -> nome) (filter (\(_, n1, n2) -> (n1 + n2) / 2 >= 7.0) alunos)

-- 3.3: Aplica desconto de 5% em todos os itens usando pattern matching na lambda
aplicaDesconto :: [Venda] -> [(String, Double)]
aplicaDesconto = map (\(item, preco) -> (item, preco * 0.95))

-- Ação main para exemplos
main :: IO ()
main = do
    putStrLn "Executando exemplos..."
    print $ somaQuadradosParesLambda [1..4]
    print $ ehVogal 'a'
    print $ subtraiDe10 15
    print $ aplicaTaxa [("A", 100.0), ("B", 40.0)]
