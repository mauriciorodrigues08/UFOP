# Documentação Técnica Complementar

**Sistema de Previsão de Consumo Energético com Regressão Linear**

Este documento resume, para uso no relatório técnico do trabalho:

1. Divergências encontradas entre os dados de teste fornecidos e as descrições do PDF "Casos de Testes"
2. Decisões de design tomadas diante de ambiguidades no enunciado
3. Bugs encontrados durante os testes manuais na interface e como foram corrigidos
4. Funcionalidades extras implementadas além do escopo obrigatório

---

## 1. Divergências entre dados de teste e descrições do PDF

Os 5 datasets de teste fornecidos nos materiais suplementares foram testados e validados com o sistema, mas alguns resultados numéricos não bateram exatamente com o que a descrição do "Casos de Testes.pdf" sugeria. Em todos os casos, verificou-se manualmente (inclusive com contagem independente via scripts auxiliares) que o sistema está calculando corretamente sobre os dados reais fornecidos — a diferença está no conteúdo dos arquivos de teste em relação à narrativa da descrição, não em erro de implementação.

### Caso de Teste 1 (Relação Linear Forte — Verão)

- **Esperado:** R² > 0,85
- **Obtido:** R² = 0,9984
- **Situação:** dentro do esperado, sem divergência.

### Caso de Teste 2 (Relação Linear Fraca — Inverno)

- **Esperado:** R² < 0,5
- **Obtido:** R² = 0,8334
- **Divergência:** o dataset apresenta uma relação linear muito mais forte do que a descrição sugere. O sistema identifica corretamente β₁ negativo (consumo cai com o aumento da temperatura, coerente com uso de aquecedores no inverno), porém o R² observado indica relação forte, não fraca como descrito.

### Caso de Teste 3 (Outlier — Anomalia de Consumo em Sabará)

- **Esperado:** R² deve cair significativamente devido a 4 medições anômalas em Sabará (evento extraordinário simulado); deve ser possível filtrar esses outliers pelo resíduo.
- **Obtido:** as 4 medições de Sabará existem no arquivo (confirmado por filtro de cidade), porém seus resíduos percentuais são pequenos (entre -2,20% e 1,04%) — não configuram outliers reais dentro do dataset. O maior resíduo do arquivo inteiro é de apenas 6,78%.
- **Validação da funcionalidade:** para confirmar que o mecanismo de exclusão de outliers funciona corretamente, testou-se com limiares de resíduo mais compatíveis com a escala real do arquivo:

  | Limite | Medições excluídas | R² resultante |
  |---|---|---|
  | 6% | 2 | 0,9816 → 0,9825 |
  | 4% | 7 | 0,9857 |
  | 3% | 16 | 0,9891 |

  Isso confirma que o mecanismo de detecção e exclusão de outliers está estatisticamente correto (excluir pontos de maior resíduo sempre melhora o ajuste), mesmo que este dataset específico não contenha uma anomalia tão extrema quanto a descrição sugere.

### Caso de Teste 4 (Poucos Dados)

- **Esperado** (segundo a descrição, com redundância/inconsistência no próprio PDF): ora "apenas 5 medições em 5 cidades diferentes", ora "apenas 2 medições válidas" — o PDF contém 3 versões repetidas e ligeiramente diferentes da descrição deste caso de teste.
- **Obtido:** o arquivo fornecido contém 5 medições válidas, e a regressão é calculada normalmente (N=5, R²=0,9950), sem acionar a mensagem de erro de dados insuficientes.
- **Validação da funcionalidade:** para confirmar que a validação de "mínimo de 2 medições" funciona, testou-se manualmente com um arquivo reduzido a 1 medição válida — o sistema corretamente nega o cálculo da regressão e exibe a mensagem de erro apropriada, além de zerar visualmente a barra de progresso de R² (ver [seção 3.2](#32-barra-de-progresso-do-r²-travava-em-valor-desatualizado)).

### Caso de Teste 5 (Validação de Dados e Tratamento de Erros)

- **Esperado:** "20 medições com erros" entre coordenada, temperatura e consumo.
- **Obtido:** 17 linhas rejeitadas (7 de coordenada, 4 de temperatura, 5 de consumo, 1 de formato — esta última por uma linha final do arquivo com vírgulas no lugar de tabulações, aparentemente um teste proposital de quebra de formato).
- **Verificação:** a contagem de 17 foi conferida de forma independente, linha a linha, usando um script auxiliar (`awk`) que varreu o arquivo procurando violações de faixa (latitude, longitude, temperatura, consumo) sem depender do código Java. O resultado bateu exatamente com o que o `MedicaoDAO` reportou, confirmando que a lógica de validação está correta; a divergência de 17 vs. 20 é do conteúdo do arquivo de teste, não da implementação.

---

## 2. Decisões de design diante de ambiguidades no enunciado

### 2.1. Escala de cores da JProgressBar do R²

O PDF especifica: *"Colorir a barra: Azul (R² <= 5), Amarelo (5 < R² <= 8), Vermelho (8 < R²)"*, sem indicar a unidade dos números 5 e 8.

**Decisão tomada:** interpretar como frações 0,5 e 0,8 (ou seja, 50% e 80%), e não como 5% e 8% literais.

**Motivo:** com R² expresso na escala 0–1 (como o resto do sistema já trata), um limiar de 0,05/0,08 faria a barra ficar sempre vermelha para qualquer regressão com correlação real (todos os datasets de teste fornecidos têm R² entre 0,83 e 0,99), esvaziando por completo o propósito de uma escala de 3 cores. Com limiares em 0,5 e 0,8, a barra tem, ao menos em teoria, condições de variar de cor conforme a qualidade do ajuste.

### 2.2. Checkboxes de ativação nos filtros (Tempo, Temperatura, Raio)

O PDF não menciona explicitamente controles de "ativar/desativar" para cada filtro, apenas os componentes de entrada (`JSpinner`, `JSlider`, `JTextField`). Como esses componentes sempre têm algum valor padrão (ex: o `JSpinner` de data sempre mostra a data/hora atual do sistema), aplicá-los diretamente — sem uma forma de "desligar" o critério — faria com que o filtro de tempo estivesse sempre ativo por padrão, escondendo todos os dados carregados (que são de datas passadas) assim que a tela abrisse.

**Decisão tomada:** adicionar um checkbox "Ativar" para cada grupo de filtro (Tempo, Temperatura, Raio), deixando explícito quando cada critério de fato está sendo aplicado.

Filtros e a configuração de outliers (slider/toggle na aba Regressão) foram mantidos como **controles independentes** entre si — o botão "Limpar todos os filtros" reseta apenas tempo/temperatura/raio, não mexe na configuração de outliers, propositalmente, por decisão do autor do projeto durante os testes da Fase 6.

---

## 3. Bugs encontrados durante os testes manuais e correções aplicadas

### 3.1. Timestamp exportado em formato incompatível com o parser

**Sintoma:** o TSV gerado por "Exportar Relatório TSV" gravava o timestamp usando o formato padrão do Java (ex: `2024-01-15T14:00`), diferente do formato exigido pelo parser de carregamento (`yyyy-MM-dd HH:mm:ss`). Um relatório exportado não podia ser recarregado de volta no sistema.

**Correção:** o timestamp passou a ser formatado explicitamente com o mesmo `DateTimeFormatter` usado no carregamento. Validado com teste de *round-trip*: exportar 100 medições e recarregar o arquivo gerado resultou em 100 de 100 medições recuperadas, 0 erros.

### 3.2. Barra de progresso do R² travava em valor desatualizado

**Sintoma:** quando a regressão falhava (menos de 2 medições após aplicar filtros e/ou exclusão de outliers), os rótulos de resultado (β₀, β₁, R², N) eram corretamente limpos, mas a barra de progresso na parte inferior da tela continuava mostrando o último valor de R² calculado com sucesso, sem indicar que os dados atuais eram insuficientes.

**Correção:** adicionado o método `limparProgressBarR2()` em `MainFrame`, chamado sempre que a regressão falha, zerando a barra e exibindo "R² indisponível (dados insuficientes)" em cinza.

### 3.3. Sliders de temperatura sem indicação visual do valor selecionado

**Sintoma:** ao testar o filtro de temperatura, os dois `JSlider`s (mín e máx) não mostravam nenhum valor numérico, tornando impossível saber visualmente qual faixa de temperatura estava selecionada. Isso levou a um teste inicial em que a faixa selecionada era, sem que o autor percebesse, extremamente estreita (ou até com o slider praticamente no zero absoluto), zerando a tabela e gerando a falsa impressão de um bug no filtro ou na exclusão de outliers.

**Correção:** os sliders passaram a exibir a régua numerada completa (`setPaintLabels`, com marcações a cada 20°C e ticks menores a cada 5°C), além de um rótulo dinâmico ao lado de cada slider mostrando o valor exato selecionado em tempo real (ex.: "Mín: 10°C").

---

## 4. Funcionalidades extras implementadas (além do escopo obrigatório)

Além do diferencial do gráfico 2D (já previsto no enunciado como critério de pontuação extra), foram implementadas as seguintes melhorias adicionais por iniciativa própria:

### 4.1. Tooltip interativo no gráfico de regressão

Ao passar o mouse sobre qualquer ponto plotado no gráfico Temperatura × Consumo, um tooltip exibe os detalhes completos daquela medição: cidade, timestamp, temperatura, consumo real, consumo previsto pela regressão, resíduo percentual, e uma marcação "(outlier)" quando aplicável.

A implementação usa o mecanismo padrão de tooltips do Swing (`getToolTipText` sobrescrito), localizando o ponto mais próximo do cursor dentro de um raio de detecção de 8 pixels, reaproveitando o mesmo sistema de coordenadas usado para desenhar os pontos e a reta de regressão.

### 4.2. Exportação do gráfico como imagem PNG

Adicionado um botão "Salvar gráfico como PNG" na aba Gráfico. A funcionalidade renderiza o painel de desenho atual (pontos, reta de regressão, eixos, legenda, equação) num `BufferedImage` e salva via `ImageIO`, permitindo usar o gráfico gerado diretamente em relatórios ou apresentações.

Testado com sucesso: arquivo PNG gerado, validado com releitura da imagem confirmando integridade e dimensões corretas.

### 4.3. Ordenação de colunas na tabela de medições

A tabela principal (aba Medições) agora permite ordenação por qualquer coluna ao clicar no cabeçalho correspondente (ex: ordenar por Temperatura, Consumo ou Resíduo Percentual), usando o mecanismo nativo de `RowSorter` do `JTable`. Implementado e testado com sucesso pelo autor do projeto.