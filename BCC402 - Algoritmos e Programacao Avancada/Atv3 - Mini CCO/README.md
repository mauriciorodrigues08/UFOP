# CostCCO

Trabalho Prático Final - projeto escolhido pelo grupo: CostCCO.
**Autores:** Maurício de Oliveira Santos Rodrigues e João Pedro Seabra Nogueira

Este projeto implementa uma variante do método **CCO (Constrained Constructive Optimization)** para geração de árvores arteriais, correspondente ao **Projeto 2 — CostCCO**, descrito no enunciado. A inovação proposta é a implementação e comparação de **quatro funções custo distintas** na etapa de otimização geométrica das bifurcações, avaliando o impacto de cada uma na morfologia final da árvore gerada.

## 1. Visão Geral do Método

A árvore arterial é construída de forma incremental: a cada novo terminal sorteado dentro do domínio de perfusão, o algoritmo:

1. gera um ponto candidato dentro do domínio, respeitando uma distância mínima (`epsilon`) em relação aos segmentos já existentes;
2. elege candidatos de conexão (pontos médios dos segmentos existentes), ordenados por proximidade euclidiana;
3. para cada candidato, insere uma bifurcação temporária e otimiza sua posição geométrica por meio de **busca em grade** em coordenadas baricêntricas dentro do triângulo formado pelo segmento antigo e o novo terminal;
4. recalcula a geometria física da árvore inteira (fluxos, raios, resistências, volumes) a cada posição candidata;
5. aceita a primeira conexão válida (sem interseções) que minimiza a função custo escolhida.

## 2. Funções Custo Implementadas

O núcleo da variante está em `Func.cpp` / `Func.h`, na função `funcaoCustoComposta`, controlada pelo enum `TipoCusto`:

| Modo | Fórmula                                             | Descrição                                   |
|------|------------------------------------------------------|----------------------------------------------|
| `J1` | `J = Vtotal`                                          | Volume intravascular total (custo padrão)     |
| `J2` | `J = Ltotal`                                          | Comprimento total da árvore                   |
| `J3` | `J = α·Vtotal + β·Ltotal`                             | Combinação linear de volume e comprimento     |
| `J4` | `J = α·Vtotal + β·Pθ`                                 | Volume + penalização angular nas bifurcações  |

A penalização angular (`Pθ`, usada em `J4`) é calculada em `calculaPenalizacaoAngular`, somando o quadrado dos ângulos (em radianos) entre o segmento pai e cada segmento filho recém-criado — penalizando bifurcações muito abertas.

## 3. Estrutura de Arquivos

```text
.
├── minicco.cpp          # programa principal: laço de geração da árvore CCO
├── viz.py               # script de visualização 3D utilizando PyVista
├── include/
│   ├── Func.h           # geometria, física (Poiseuille) e funções custo (J1-J4)
│   ├── Arvore.h         # estrutura de nó (No) e utilitários (numeroNos, numeroFolhas)
│   ├── Ponto.h          # classe Ponto (x, y, z)
│   ├── Segmento.h       # classe Segmento (par de pontos)
│   ├── Vetor.h          # classe Vetor (norma, produto escalar)
│   └── Dominio.h        # domínio circular de perfusão (raio + centro)
├── Func.cpp             # implementação das funções físicas e geométricas
└── Arvore.cpp           # implementação utilitária da árvore
```

## 4. Compilação

Supondo os cabeçalhos organizados em `include/`:

```bash
  g++ -std=c++17 -O2 -Wall minicco.cpp Func.cpp Arvore.cpp -o minicco
```

## 5. Execução

```bash
  ./minicco <N_terminais> <Raio> <gamma> <M> <modo> <alpha> <beta> <seed>
```

| Parâmetro     | Descrição                                                        |
|---------------|-------------------------------------------------------------------|
| `N_terminais` | Número de pontos terminais a gerar (≥ 2)                          |
| `Raio`        | Raio do domínio circular de perfusão                               |
| `gamma`       | Expoente da lei de bifurcação (recomendado: 3.0, ou {2.55, 2.7, 3.0}) |
| `M`           | Resolução da busca em grade (coordenadas baricêntricas)           |
| `modo`        | Função custo: `J1`, `J2`, `J3` ou `J4` (padrão: `J1`)              |
| `alpha`, `beta`| Pesos obrigatórios apenas quando `modo` é `J3` ou `J4`            |
| `seed`        | Semente do gerador aleatório para reprodutibilidade               |

**Exemplo:**

```bash
  ./minicco 100 0.05 3.0 20 J3 1.0 1.0 1
```

## 6. Saídas Geradas

O programa irá gerar as seguintes saídas e arquivos locais:
- **Console:** Métricas da execução como número total de nós, segmentos, comprimento total, volume, conexões testadas/rejeitadas e tempo computacional.
- **`arvore.csv`:** Arquivo com uma linha por segmento, detalhando propriedades físicas (id, pai, coordenadas, raio, comprimento, fluxo, resistencia, volume).
- **`metricas.csv`:** Arquivo consolidado com as métricas globais para análise estatística.
- **`execucao.log`:** Log detalhado do rastreio e aceitação/rejeição para cada terminal inserido.

## 7. Visualização (PyVista)

Após executar o programa C++, a árvore pode ser visualizada em um ambiente 3D gerado pelo Python. Certifique-se de instalar as dependências necessárias:

```bash
  pip install pyvista pandas numpy
```

Para rodar a visualização:

```bash
  python viz.py
```
O script solicitará o raio do domínio circular utilizado na execução para desenhar a fronteira corretamente.

## 8. Algoritmos Principais

- **Geração de terminais:** sorteio uniforme dentro do domínio circular, com distância mínima adaptativa `epsilon` (decrescente após tentativas mal sucedidas).
- **Seleção de candidatos:** percorre a árvore, calculando o ponto médio de cada segmento existente como possível ponto de bifurcação, ordenando por distância euclidiana.
- **Otimização geométrica:** varre uma grade de resolução `M` em coordenadas baricêntricas dentro do triângulo, testando interseções e recalculando a função custo a cada posição.
- **Atualização da geometria física:** recalcula, em cadeia, comprimentos, fluxos (pós-ordem), raios, resistências e volumes de toda a árvore.