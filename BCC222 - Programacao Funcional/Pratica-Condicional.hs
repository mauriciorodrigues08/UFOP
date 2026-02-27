-- verifica se o número é negativo
ehNegativo :: Int -> Bool
ehNegativo n =  if n<0 
                then True
                else False

-- calcula o sinal do integer utilizando if (-1, 0 ou 1)
sinal_if :: Integer -> Integer
sinal_if n =  if n > 0
              then 1
              else  if n == 0
                    then 0
                    else -1

-- calcula o sinal do integer utilizando guardas (-1, 0 ou 1)
sinal_guardas :: Integer -> Integer
sinal_guardas n
  | n < 0   = -1
  | n == 0  = 0
  | otherwise   = 1


-- define a faixa etária da idade digitada
categoriaIdade :: Integer -> String
categoriaIdade idade
  | idade <0     = "erro"
  | idade <= 12  = "crianca"
  | idade <= 17  = "adolescente"
  | idade <= 60  = "adulto"
  | otherwise    = "idoso"


-- calcula as raízes de uma equação usando guardas e uma definição local para o discriminante
numRaizes :: Double -> Double -> Double -> Int
numRaizes a b c
  | delta < 0   = 0
  | delta == 0  = 1
  | otherwise   = 2
  where
    delta = b^2 - 4*a*c