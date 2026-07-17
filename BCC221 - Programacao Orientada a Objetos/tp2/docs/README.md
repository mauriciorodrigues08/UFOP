# Sistema de Previsão de Consumo Energético com Regressão Linear

Trabalho Prático 2 — BCC 221 (Programação Orientada a Objetos)

Sistema desktop em Java Swing que analisa a relação entre temperatura
externa e consumo de energia, permitindo filtrar medições por período,
temperatura e localização, recalcular a regressão linear sobre os
dados filtrados, identificar outliers pelo resíduo percentual e
visualizar tudo através de tabelas interativas e um gráfico 2D.

---

## Funcionalidades

- **Carregamento de dados** via TSV, com validação linha a linha
  (coordenadas, temperatura, consumo, formato) e relatório detalhado
  de rejeições.
- **Tabela interativa**: edição de temperatura/consumo direto na
  célula, adição e remoção de medições, com recálculo automático da
  regressão.
- **Filtros dinâmicos e combináveis**: intervalo de tempo, intervalo
  de temperatura e raio geográfico (fórmula de Haversine), cada um
  ativado/desativado independentemente.
- **Regressão linear** (mínimos quadrados) com β₀, β₁, R² e previsão
  de consumo, recalculada automaticamente a cada mudança de filtro ou
  edição de dado.
- **Detecção de outliers** por resíduo percentual, com destaque visual
  na tabela e opção de exclusão dinâmica (recalculando a regressão
  apenas com os dados "limpos").
- **Exportação de relatório TSV** com os dados atualmente filtrados,
  incluindo consumo previsto e resíduo.
- **Gráfico 2D** (Temperatura × Consumo) com pontos reais, outliers
  destacados, reta de regressão sobreposta, equação e R² exibidos, e
  **tooltip interativo** ao passar o mouse sobre qualquer ponto.
- **Ordenação de colunas** na tabela de medições (clique no cabeçalho).
- **Exportação do gráfico como imagem PNG**.
- **Geração de .jar executável** via `make jar`, para rodar a aplicação
  fora da IDE com `java -jar TP2.jar`.

---

## Estrutura do projeto

```
tp2/
├── src/
│   ├── Main.java
│   ├── controller/
│   │   └── SistemaController.java
│   ├── model/
│   │   ├── Medicao.java
│   │   ├── MedicaoDAO.java
│   │   ├── ErroValidacao.java
│   │   ├── Filtro.java
│   │   ├── RegressaoLinear.java
│   │   └── TabelaModel.java
│   ├── util/
│   │   ├── CalculoDistancia.java
│   │   └── FormatarNumero.java
│   ├── view/
│   │   ├── MainFrame.java
│   │   ├── MedicoesPanel.java
│   │   ├── FiltrosPanel.java
│   │   ├── RegressaoPanel.java
│   │   ├── GraficoPanel.java
│   │   └── renderers/
│   │       └── OutlierTableCellRenderer.java
│   ├── TesteCasos.java          (harness de validação com datasets reais)
│   ├── TesteFiltroRaio.java     (harness de validação do filtro por raio)
│   └── ...                       (outros harnesses de teste manual)
├── scripts/
│   ├── compile.sh
│   ├── run.sh
│   └── jar.sh
├── dados-teste/
│   ├── teste1_verao_linear_forte_tsv.tsv
│   ├── teste2_inverno_relacao_fraca.tsv
│   ├── teste3_outlier_anomalia.tsv
│   ├── teste4_poucos_dados.tsv
│   └── teste5_validacao_erros.tsv
├── docs/
│   ├── README.md                          (este arquivo)
│   └── divergencias_e_extras.txt          (documentação complementar)
├── Makefile
└── TP2.jar                                (gerado por `make jar`)
```

---

## Como compilar e rodar

Pré-requisitos: JDK 17+ instalado (`javac -version` para conferir).

### Usando o Makefile (recomendado)

Na raiz do projeto:

```bash
make compile   # compila o projeto
make run       # executa a aplicação (assume que já foi compilado)
make all       # compila e executa em sequência
make test      # roda os harnesses de teste contra os 5 datasets reais
make jar       # gera o .jar executável (TP2.jar)
make clean     # remove os arquivos gerados (pasta out/ e TP2.jar)
make help      # lista os comandos disponíveis
```

### Manualmente, via scripts

```bash
./scripts/compile.sh
./scripts/run.sh
```

Ambos os scripts funcionam independentemente de onde são chamados
(resolvem o caminho da raiz do projeto automaticamente) e lidam
corretamente com caminhos que contêm espaços.

---

## Gerando o .jar executável

Para atender ao requisito de entrega de um `.jar` executável, o projeto
inclui o script `scripts/jar.sh`, integrado ao `Makefile`:

```bash
make jar
```

Isso compila o projeto (se necessário) e gera `TP2.jar` na raiz do
projeto, com `Main-Class: Main` já configurado no manifesto — não é
preciso passar o classpath manualmente.

Para executar o `.jar` gerado:

```bash
java -jar TP2.jar
```

A aplicação deve abrir normalmente, igual a `make run`, mas de forma
totalmente independente da IDE — só precisa do `TP2.jar` e do Java
instalado (não precisa do `src/` nem do `out/` junto).

Alternativamente, sem o Makefile:

```bash
./scripts/compile.sh
./scripts/jar.sh
java -jar TP2.jar
```

---

## Testando com dados reais

A pasta `dados-teste/` contém os 5 Casos de Teste fornecidos no
enunciado. Duas formas de testar:

1. **Pela interface**: menu **Arquivo → Carregar TSV** e selecione um
   dos arquivos em `dados-teste/`.
2. **Via linha de comando** (mais rápido para validar a lógica sem
   abrir a interface):
   ```bash
   make test
   ```
   Isso compila o projeto e roda o harness `TesteCasos.java` contra os
   5 datasets, imprimindo medições válidas, resumo de erros de
   validação e os coeficientes da regressão (β₀, β₁, R², N) de cada
   um.

Os resultados obtidos com esses datasets, incluindo algumas
divergências entre os dados fornecidos e a descrição do PDF de Casos
de Teste, estão documentados em `docs/divergencias_e_extras.txt`.

---

## Decisões de design relevantes

Algumas decisões tomadas diante de ambiguidades do enunciado (detalhes
completos em `docs/divergencias_e_extras.txt`):

- **Escala de cores da barra de progresso do R²**: interpretada como
  frações 0,5 e 0,8 (50%/80%), não 0,05/0,08, para que a escala de
  3 cores realmente varie com dados reais.
- **Filtros com checkbox de ativação**: cada grupo de filtro (Tempo,
  Temperatura, Raio) tem um checkbox "Ativar" explícito, evitando que
  valores padrão dos componentes (ex: data atual no JSpinner) filtrem
  os dados sem o usuário pedir.
- **Filtros e configuração de outliers são independentes**: o botão
  "Limpar todos os filtros" não reseta o slider/toggle de exclusão de
  outliers (são conceitos separados no enunciado).

---

## Funcionalidades extras implementadas (além do escopo obrigatório)

Além do diferencial do gráfico 2D previsto no enunciado, foram implementados:

- Tooltip interativo no gráfico (detalhes da medição ao passar o mouse).
- Exportação do gráfico como imagem PNG.
- Ordenação de colunas na tabela de medições.

Detalhes de implementação e validação de cada um em
`docs/divergencias_e_extras.md`.

---

## Autores
Maurício Rodrigues
João Pedro Seabra
Luiz Felipe Bento
Gabriel Canuto
Lara de Andrade