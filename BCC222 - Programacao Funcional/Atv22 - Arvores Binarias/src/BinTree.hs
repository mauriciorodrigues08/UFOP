module BinTree
  ( BinTree(..), -- Exporta o tipo e seus construtores (V, N)
    btLength,
    btDepth,
    btElem
  )
where

-- Tarefa 1: Defina o tipo de dado BinTree a
-- Uma árvore binária (BinTree a) pode ser:
-- Vazia (use o construtor 'V'), OU
-- um Nó (use o construtor 'N') que contém um valor do tipo 'a' e duas sub-árvores.
-- Não se esqueça de derivar Show e Eq.

data BinTree a = V 
               | N a (BinTree a) (BinTree a)
  deriving (Show, Eq)

-- Tarefa 2.1: Implemente a função btLength
-- Recebe uma árvore e retorna o número de nós.
btLength :: BinTree a -> Int
btLength V = 0
btLength (N _ esq dir) = 1 + btLength esq + btLength dir

-- Tarefa 2.2: Implemente a função btDepth
-- Recebe uma árvore e retorna a sua profundidade.
-- A profundidade é o número de nós no caminho mais longo da raiz até uma folha vazia.
btDepth :: BinTree a -> Int
btDepth V = 0
btDepth (N _ esq dir) = 1 + max (btDepth esq) (btDepth dir)

-- Tarefa 2.3: Implemente a função btElem
-- Verifica se um elemento está presente na árvore.
btElem :: (Eq a) => a -> BinTree a -> Bool
btElem _ V = False
btElem x (N val esq dir) 
  | x == val  = True
  | otherwise = btElem x esq || btElem x dir