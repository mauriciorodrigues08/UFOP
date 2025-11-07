--Definição de sinônimos
type Nome = String
type Idade = Int
type Pessoa = (Nome, Idade)

--Vamos criar uma função que calcula a distância euclidiana entre dois pontos no plano cartesiano. Esta tarefa irá praticar a definição de funções auxiliares e a composição.
areaCirculo :: Double -> Double
areaCirculo raio = pi * raio^2

quadrado :: Double -> Double
quadrado valor = valor^2

distancia :: (Double, Double) -> (Double, Double) -> Double
distancia p q = 
  sqrt ( quadrado(xq-xp) + quadrado(yq-yp) )
  
  where
    xp = fst p
    yp = snd p
    xq = fst q
    yq = snd q


--Vamos definir uma função para calcular a área da superfície de um cilindro. A fórmula se decompõe naturalmente em partes, o que a torna um exemplo perfeito para o uso de definições locais com where.
areaCilindro :: Double -> Double -> Double
areaCilindro raio altura = areaLateral + 2 * areaBase
  where
    areaLateral = 2 * pi * raio * altura
    areaBase = areaCirculo raio


--Vamos criar uma função para calcular o montante final de um investimento a juros compostos, usando definições locais para tornar a fórmula mais clara.
montanteJurosCompostos :: Double -> Double -> Int -> Double
montanteJurosCompostos principal taxaAnual anos =
  principal * fatorAcumulacao

  where
    fatorAcumulacao = (1+taxaAnual) ^ anos


--Defina uma função que calcula as raízes de uma equação quadrática (𝑎𝑥2+𝑏𝑥+𝑐 = 0). A natureza local do cálculo de Δ torna esta uma boa oportunidade para usar let...in
raizes :: Double -> Double -> Double -> (Double, Double)
raizes a b c =
  let 
    delta = b^2 - 4 * a * c
    raiz1 = (-b + sqrt delta) / (2*a)
    raiz2 = (-b - sqrt delta) / (2*a)
  in 
    (raiz1, raiz2)


-- Vamos usar tipos sinônimos para documentar melhor a intenção de uma função que manipula dados de um usuário.
criaPessoa :: Nome -> Idade -> Pessoa
criaPessoa nome idade = (nome, idade)


--Vamos criar uma função que calcula a posição de um projétil num instante 𝑡, dado um ângulo de lançamento 𝜃 e uma velocidade inicial 𝑣0. A natureza interdependente das componentes da velocidade torna este um ótimo caso de uso para let...in.
grausParaRadianos :: Double -> Double
grausParaRadianos graus = graus * pi / 180

posicaoProjetil :: Double -> Double -> Double -> (Double, Double)
posicaoProjetil angulo v0 t =
  let
    g = 9.81
    theta = grausParaRadianos angulo
    vx = v0 * cos theta
    vy = v0 * sin theta
    x = vx * t
    y = (vy * t) - (0.5 * (g* t^2))
  in
    (x,y)
