package controller;

import model.*;
import view.MainFrame;
import view.GraficoPanel;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class SistemaController {
    private MedicaoDAO dao;
    private TabelaModel tableModel;
    private Filtro filtroAtual;
    private RegressaoLinear regressaoAtual;
    private List<Medicao> dadosOriginais;
    private List<Medicao> dadosFiltrados;
    private MainFrame view;

    private static final DateTimeFormatter FORMATTER_ENTRADA =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    public SistemaController(MainFrame view) {
        this.view = view;
        this.dao = new MedicaoDAO();
        this.tableModel = new TabelaModel();
        this.filtroAtual = new Filtro();
        this.regressaoAtual = new RegressaoLinear();
        this.dadosOriginais = new ArrayList<>();
        this.dadosFiltrados = new ArrayList<>();

        // TabelaModel notifica o controller quando uma célula é editada
        // com sucesso (recalcular regressão) ou quando uma edição é
        // rejeitada por validação (exibir mensagem ao usuário).
        tableModel.setOnDadosAlterados(this::recalcularRegressao);
        tableModel.setOnErroValidacao(view::exibirMensagemErro);

        // FiltrosPanel notifica o controller sempre que algum filtro muda,
        // para reaplicação dinâmica sobre os dados carregados.
        view.getFiltrosPanel().setOnFiltroAlterado(this::filtrosAlterados);
        view.getFiltrosPanel().setOnErroValidacao(view::exibirMensagemErro);

        inicializarEventos();

        view.getMedicoesPanel().setTableModel(tableModel);
    }

    private void inicializarEventos() {
        view.getMedicoesPanel().getBtnAdicionar().addActionListener(e -> adicionarMedicao());
        view.getMedicoesPanel().getBtnRemover().addActionListener(e -> removerMedicoesSelecionadas());
        view.getFiltrosPanel().getBtnLimparFiltros().addActionListener(e -> limparTodosFiltros());

        view.getRegressaoPanel().getSliderOutlierPercentual().addChangeListener(e -> atualizarOutliers());
        view.getRegressaoPanel().getToggleExcluirOutliers().addActionListener(e -> atualizarOutliers());

        view.getItemCarregar().addActionListener(e -> carregarArquivoTSV());
        view.getItemExportar().addActionListener(e -> exportarRelatorioTSV());
        view.getItemSair().addActionListener(e -> sair());
        view.getItemLimparFiltros().addActionListener(e -> limparTodosFiltros());

        view.getBtnSalvarGrafico().addActionListener(e -> salvarGraficoComoImagem());
    }

    public void carregarArquivoTSV() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new FileNameExtensionFilter("Arquivos TSV", "tsv"));

        if (fileChooser.showOpenDialog(view) == JFileChooser.APPROVE_OPTION) {
            try {
                dadosOriginais = dao.carregarDeTSV(fileChooser.getSelectedFile());

                exibirResumoErros();
                aplicarFiltros();

                view.exibirMensagemInfo("Arquivo carregado com sucesso!");
            } catch (IOException e) {
                view.exibirMensagemErro("Erro ao carregar arquivo: " + e.getMessage());
            }
        }
    }

    public void exportarRelatorioTSV() {
        if (dadosFiltrados == null || dadosFiltrados.isEmpty()) {
            view.exibirMensagemErro(
                    "Não há medições para exportar. Carregue um arquivo TSV (ou ajuste os " +
                    "filtros) antes de exportar o relatório.");
            return;
        }

        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new FileNameExtensionFilter("Arquivos TSV", "tsv"));

        if (fileChooser.showSaveDialog(view) == JFileChooser.APPROVE_OPTION) {
            File arquivo = fileChooser.getSelectedFile();
            String path = arquivo.getAbsolutePath();
            if (!path.endsWith(".tsv")) {
                path += ".tsv";
                arquivo = new File(path);
            }

            try (PrintWriter writer = new PrintWriter(arquivo)) {
                writer.println("timestamp\tcidade\tlatitude\tlongitude\ttemperatura\tconsumoKwh\tconsumoPrevisto\tresiduoPercentual");

                for (Medicao m : dadosFiltrados) {
                    writer.printf("%s\t%s\t%.6f\t%.6f\t%.2f\t%.2f\t%.4f\t%.2f%n",
                            m.getTimestamp().format(FORMATTER_ENTRADA), m.getCidade(),
                            m.getLatitude(), m.getLongitude(),
                            m.getTemperatura(), m.getConsumoKwh(),
                            m.getConsumoPrevisto(), m.getResiduoPercentual());
                }

                view.exibirMensagemInfo("Relatório exportado com sucesso!");
            } catch (FileNotFoundException e) {
                view.exibirMensagemErro("Erro ao exportar: " + e.getMessage());
            }
        }
    }

    /**
     * Renderiza o GraficoPanel atual num BufferedImage e salva como PNG,
     * capturando exatamente o que está sendo exibido na tela (pontos,
     * reta de regressão, eixos, legenda).
     */
    public void salvarGraficoComoImagem() {
        if (dadosFiltrados == null || dadosFiltrados.isEmpty()) {
            view.exibirMensagemErro(
                    "Não há gráfico para exportar. Carregue um arquivo TSV antes de salvar o gráfico.");
            return;
        }

        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new FileNameExtensionFilter("Imagem PNG", "png"));

        if (fileChooser.showSaveDialog(view) == JFileChooser.APPROVE_OPTION) {
            File arquivo = fileChooser.getSelectedFile();
            String path = arquivo.getAbsolutePath();
            if (!path.toLowerCase().endsWith(".png")) {
                path += ".png";
                arquivo = new File(path);
            }

            GraficoPanel grafico = view.getGraficoPanel();
            int largura = grafico.getWidth() > 0 ? grafico.getWidth() : grafico.getPreferredSize().width;
            int altura = grafico.getHeight() > 0 ? grafico.getHeight() : grafico.getPreferredSize().height;

            BufferedImage imagem = new BufferedImage(largura, altura, BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2 = imagem.createGraphics();
            grafico.paint(g2);
            g2.dispose();

            try {
                ImageIO.write(imagem, "png", arquivo);
                view.exibirMensagemInfo("Gráfico exportado com sucesso!");
            } catch (IOException e) {
                view.exibirMensagemErro("Erro ao exportar gráfico: " + e.getMessage());
            }
        }
    }

    /**
     * Ponto central do fluxo de dados: parte de dadosOriginais, aplica os
     * filtros ativos e delega a exibição/regressão para recalcularRegressao(),
     * que também considera o estado atual do slider/toggle de outliers.
     */
    public void aplicarFiltros() {
        if (dadosOriginais == null) return;

        dadosFiltrados = filtroAtual.aplicar(dadosOriginais);
        recalcularRegressao();
    }

    /**
     * Único ponto de cálculo de regressão + exibição. Considera o estado
     * atual do slider/toggle de outliers:
     *
     * 1. Calcula a regressão sobre TODOS os dados filtrados, para obter
     *    o resíduo percentual de cada medição.
     * 2. Se "excluir outliers" estiver ativo, filtra as medições cujo
     *    resíduo excede o limite e recalcula a regressão apenas sobre o
     *    conjunto "limpo" (isso é o que faz o R² melhorar de fato ao
     *    excluir outliers, e não apenas escondê-los visualmente).
     * 3. Atualiza tabela, painel de resultados, progress bar e gráfico.
     */
    public void recalcularRegressao() {
        if (dadosFiltrados == null) return;

        double limite = view.getRegressaoPanel().getLimiteOutlierPercentual();
        boolean excluir = view.getRegressaoPanel().isExcluirOutliers();

        tableModel.setLimiteOutlierPercentual(limite);

        List<Medicao> conjuntoFinal = dadosFiltrados;

        if (excluir) {
            boolean sucessoBase = regressaoAtual.calcular(dadosFiltrados);
            if (sucessoBase) {
                conjuntoFinal = dadosFiltrados.stream()
                        .filter(m -> Math.abs(m.getResiduoPercentual()) <= limite)
                        .collect(Collectors.toList());
            }
        }

        boolean sucesso = regressaoAtual.calcular(conjuntoFinal);
        tableModel.setDados(conjuntoFinal);

        if (sucesso) {
            view.getRegressaoPanel().atualizarResultados(
                    regressaoAtual.getBeta0(),
                    regressaoAtual.getBeta1(),
                    regressaoAtual.getR2(),
                    regressaoAtual.getN()
            );
            view.atualizarProgressBarR2(regressaoAtual.getR2());
            tableModel.fireTableDataChanged();
        } else {
            view.getRegressaoPanel().limparResultados();
            view.limparProgressBarR2();
            view.getRegressaoPanel().exibirMensagensValidacao(
                    "Atenção: É necessário pelo menos 2 medições para calcular a regressão.\n" +
                    "Dados considerados atualmente: " + conjuntoFinal.size() + " medição(ões)."
            );
        }

        atualizarGrafico();
    }

    public void adicionarMedicao() {
        Medicao nova = solicitarNovaMedicao();
        if (nova == null) {
            return; // usuário cancelou
        }

        if (dadosOriginais == null) {
            dadosOriginais = new ArrayList<>();
        }
        dadosOriginais.add(nova);
        aplicarFiltros();
    }

    /**
     * Abre um diálogo pedindo os dados da nova medição, validando cada
     * campo com as mesmas regras usadas no carregamento de TSV
     * (MedicaoDAO). Repete o diálogo até os dados serem válidos ou o
     * usuário cancelar.
     */
    private Medicao solicitarNovaMedicao() {
        JTextField txtTimestamp = new JTextField(LocalDateTime.now().format(FORMATTER_ENTRADA));
        JTextField txtCidade = new JTextField();
        JTextField txtLatitude = new JTextField();
        JTextField txtLongitude = new JTextField();
        JTextField txtTemperatura = new JTextField();
        JTextField txtConsumo = new JTextField();

        JPanel painel = new JPanel(new java.awt.GridLayout(0, 2, 5, 5));
        painel.add(new JLabel("Timestamp (yyyy-MM-dd HH:mm:ss):"));
        painel.add(txtTimestamp);
        painel.add(new JLabel("Cidade:"));
        painel.add(txtCidade);
        painel.add(new JLabel("Latitude (-90 a 90):"));
        painel.add(txtLatitude);
        painel.add(new JLabel("Longitude (-180 a 180):"));
        painel.add(txtLongitude);
        painel.add(new JLabel("Temperatura em °C (-50 a 60):"));
        painel.add(txtTemperatura);
        painel.add(new JLabel("Consumo em kWh (≥ 0):"));
        painel.add(txtConsumo);

        while (true) {
            int resultado = JOptionPane.showConfirmDialog(
                    view, painel, "Adicionar Medição",
                    JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

            if (resultado != JOptionPane.OK_OPTION) {
                return null; // usuário cancelou
            }

            try {
                LocalDateTime timestamp = LocalDateTime.parse(txtTimestamp.getText().trim(), FORMATTER_ENTRADA);
                String cidade = txtCidade.getText().trim();
                double latitude = Double.parseDouble(txtLatitude.getText().trim().replace(',', '.'));
                double longitude = Double.parseDouble(txtLongitude.getText().trim().replace(',', '.'));
                double temperatura = Double.parseDouble(txtTemperatura.getText().trim().replace(',', '.'));
                double consumo = Double.parseDouble(txtConsumo.getText().trim().replace(',', '.'));

                if (cidade.isEmpty()) {
                    view.exibirMensagemErro("A cidade não pode ficar vazia.");
                    continue;
                }
                if (!dao.validarCoordenada(latitude, longitude)) {
                    view.exibirMensagemErro("Coordenada inválida (latitude -90 a 90, longitude -180 a 180).");
                    continue;
                }
                if (!dao.validarTemperatura(temperatura)) {
                    view.exibirMensagemErro("Temperatura fora da faixa permitida (-50 a 60 °C).");
                    continue;
                }
                if (!dao.validarConsumo(consumo)) {
                    view.exibirMensagemErro("Consumo não pode ser negativo.");
                    continue;
                }

                return new Medicao(timestamp, cidade, latitude, longitude, temperatura, consumo);

            } catch (DateTimeParseException e) {
                view.exibirMensagemErro("Timestamp inválido. Use o formato yyyy-MM-dd HH:mm:ss.");
            } catch (NumberFormatException e) {
                view.exibirMensagemErro("Latitude, longitude, temperatura e consumo devem ser números válidos.");
            }
        }
    }

    public void removerMedicoesSelecionadas() {
        int[] linhas = view.getMedicoesPanel().getLinhasSelecionadas();
        if (linhas.length == 0) {
            return;
        }

        List<Medicao> aRemover = new ArrayList<>();
        for (int linha : linhas) {
            Medicao m = tableModel.getMedicaoAt(linha);
            if (m != null) {
                aRemover.add(m);
            }
        }

        if (dadosOriginais != null) {
            dadosOriginais.removeAll(aRemover);
        }

        aplicarFiltros();
    }

    /**
     * Reconstrói o Filtro atual a partir do estado da UI (FiltrosPanel)
     * e reaplica sobre os dados. Chamado automaticamente sempre que
     * qualquer componente de filtro é alterado.
     */
    private void filtrosAlterados() {
        this.filtroAtual = view.getFiltrosPanel().getFiltro();
        aplicarFiltros();
    }

    public void limparTodosFiltros() {
        view.getFiltrosPanel().limparCampos();
        this.filtroAtual = new Filtro();
        aplicarFiltros();
    }

    /**
     * Chamado quando o slider de limite de outlier ou o toggle de
     * exclusão são alterados pelo usuário. Toda a lógica de fato está
     * em recalcularRegressao(), que já considera o estado atual desses
     * componentes.
     */
    public void atualizarOutliers() {
        recalcularRegressao();
    }

    private void atualizarGrafico() {
        view.getGraficoPanel().atualizarDados(
                dadosFiltrados,
                regressaoAtual,
                view.getRegressaoPanel().getLimiteOutlierPercentual()
        );
    }

    private void exibirResumoErros() {
        ErroValidacao erros = dao.getErros();
        view.getRegressaoPanel().exibirMensagensValidacao(erros.getMensagemResumo());

        // Requisito 7 do PDF: apresentar em JOptionPane quantas linhas
        // foram rejeitadas e por qual motivo (só exibe se houve rejeição,
        // para não incomodar o usuário em arquivos sem erros).
        if (erros.temErros()) {
            JOptionPane.showMessageDialog(
                    view,
                    erros.getMensagemResumo(),
                    "Resumo de Validação do Arquivo",
                    JOptionPane.WARNING_MESSAGE
            );
        }
    }

    public void sair() {
        System.exit(0);
    }
}