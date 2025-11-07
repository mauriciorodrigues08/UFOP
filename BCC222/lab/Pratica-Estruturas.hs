import Data.Maybe

-- inverte os pares
type ParIntString = (Int, String)
invertePar :: ParIntString -> (String, Int)
invertePar par = (snd(par), fst(par))

-- retorna o primeiro elemento, se existir
primeiroElemento :: [a] -> Maybe a
primeiroElemento lista =  if head(lista)
                          then Just fst(lista)
                          else Nothing