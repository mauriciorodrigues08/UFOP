# MiniCCO-1 — Escala dos Raios e Otimização Geométrica de Bifurcações

Continuação do MiniCCO-0. Os nomes de arquivo (`minicco.cpp`, `viz.py`, `Arvore.h`,
`Func.h`, `Func.cpp`) foram mantidos iguais aos da primeira parte para facilitar o
reaproveitamento em um repositório próprio desta etapa.

## Arquivos
  include/
    Arvore.h          -> classe No, com raio, comprimento, fluxo, resistencia, volume, qtdTermDistal
    Dominio.h         -> domínio circular (inalterado)
    Func.h            -> funções geométricas + funções das Partes A-G
    Ponto.h           -> struct Ponto (inalterado)
    Segmento.h        -> struct Segmento (inalterado)
  resultados/
    teste1_arvore.csv -> arvore gerada pelo teste 1
    teste1_saida.txt  -> saida gerada pelo teste 1
    ...
  Arvore.cpp          -> numeroNos / numeroFolhas (inalterado)
  Func.cpp            -> implementações geométricas + Partes A-G
  minicco.cpp         -> programa principal (MiniCCO-1)
  viz.py              -> visualização com tubos proporcionais ao raio
  Relatorio.pdf       -> Relatório técnico com a análise de complexidade e discussão dos testes
  testeX_...          -> Arquivos .csv e .txt contendo as saídas e árvores geradas para os testes 1 a 6
```

## Compilação

```bash
g++ -std=c++17 -O2 -Wall -o minicco minicco.cpp Func.cpp Arvore.cpp
```

## Execução

```
./minicco <Nterm> <R> <gamma> <M>
```

Exemplo do enunciado:

```bash
./minicco 50 0.05 3.0 20
```

Gera `arvore.csv` com as colunas `id,pai,x0,y0,x1,y1,raio,comprimento,fluxo,resistencia,volume`
e imprime no terminal: número de nós, segmentos, terminais, comprimento total, volume
intravascular total, raio da raiz, raio médio, conexões testadas/rejeitadas e tempo de execução.

## Visualização

```bash
pip install pyvista pandas numpy   # se necessário
python3 viz.py
```

## Mapeamento com o enunciado

| Seção do PDF | Onde está |
|---|---|
| Parte A (comprimento, resistência, volume) | `distancia`, `calculaComprimento`, `calculaResistencia`, `calculaVolume`, `calculaVolumeTotal` em `Func.cpp` |
| Parte B (terminais distais) | `atualizaQtdTerminaisDistais` |
| Parte C (fluxo por segmento) | `atualizaFluxos` |
| Parte D (escala dos raios) | `atualizaRaiosPorFluxo`, `atualizaGeometriaFisica` |
| Parte E (função custo) | `funcaoCustoVolume` |
| Parte F (grade / coordenadas baricêntricas) | `pontoBaricentrico`, `pontoDentroTriangulo`, `otimizaBifurcacaoPorGrade` |
| Parte G (avaliação da bifurcação temporária) | laço principal de `minicco.cpp`, que insere a bifurcação temporariamente, chama `otimizaBifurcacaoPorGrade` e só efetiva a inserção na melhor posição válida |

### Assinatura de `otimizaBifurcacaoPorGrade`

O enunciado sugere `Point otimizaBifurcacaoPorGrade(ptrNo raiz, Point A, Point B, Point C, int M, double *melhorCusto)`.
Ela foi estendida para receber também os nós temporários (bifurcação/alvo/terminal) e Qterm/gamma/mu,
pois cada ponto candidato exige recalcular toda a árvore (fluxo, raio, volume) e checar interseções —
informação que não cabe apenas no ponteiro da bifurcação.

### Estratégia de candidatos e complexidade (Seção 18)

Em vez de rodar a busca em grade para todos os segmentos existentes (O(K·M²·N) por terminal),
o programa reordena os candidatos por distância euclidiana (como no MiniCCO-0) e tenta a
otimização geométrica completa um candidato de cada vez, aceitando o primeiro que resultar em
posição válida — normalmente já no primeiro ou segundo candidato. Isso mantém o tempo de execução
baixo mesmo com M = 50.

## Testes numéricos (Seção 16)

Execução de referência (os valores variam levemente entre execuções, pois a geração dos
terminais é estocástica):

| Teste | Nterm | γ | M | Nós | Volume total | Raio raiz | Raio médio | Testadas | Rejeitadas | Tempo (s) |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 10 | 3.0 | 10 | 20 | 0.404901 | 1 | 0.59671 | 9 | 543 | 0.000924 |
| 2 | 30 | 3.0 | 20 | 60 | 0.431611 | 1 | 0.444757 | 29 | 1963 | 0.016695 |
| 3 | 50 | 3.0 | 20 | 100 | 0.473498 | 1 | 0.391555 | 49 | 3433 | 0.093433 |
| 4 | 50 | 2.7 | 20 | 100 | 0.385891 | 1 | 0.362514 | 49 | 3624 | 0.024009 |
| 5 | 50 | 3.0 | 50 | 100 | 0.472704 | 1 | 0.378615 | 49 | 3374 | 0.130711 |
| 6 | 200 | 3.0 | 100 | 400 | 0.518289 | 1 | 0.261574 | 199 | 15174 | 6.86817 |

O raio da raiz aparece normalizado em 1.0 porque, conforme a Parte D, adotamos C = 1 e
normalizamos todos os raios pelo raio do tronco (a Seção 8 do enunciado descreve como,
opcionalmente, escalar esse valor a partir de Δp = pperf − pterm).