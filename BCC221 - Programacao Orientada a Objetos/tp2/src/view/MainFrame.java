package view;
import model.TabelaModel;

import controller.SistemaController;
import javax.swing.*;
import java.awt.*;

public class MainFrame extends JFrame {
    private JTabbedPane tabbedPane;
    private MedicoesPanel medicoesPanel;
    private FiltrosPanel filtrosPanel;
    private RegressaoPanel regressaoPanel;
    private GraficoPanel graficoPanel;
    private JProgressBar progressBarR2;
    private JMenuBar menuBar;
    private JMenuItem itemCarregar;
    private JMenuItem itemExportar;
    private JMenuItem itemSair;
    private JMenuItem itemLimparFiltros;
    private JButton btnSalvarGrafico;
    private SistemaController controller;
    
    public MainFrame() {
        setTitle("Sistema de Análise Energética");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1200, 800);
        setLocationRelativeTo(null);
        
        inicializarComponentes();
        criarMenuBar();
        
        controller = new SistemaController(this);
        
        setJMenuBar(menuBar);
        setVisible(true);
    }
    
    private void inicializarComponentes() {
        tabbedPane = new JTabbedPane();
        
        medicoesPanel = new MedicoesPanel(null); // TableModel será setado depois
        filtrosPanel = new FiltrosPanel();
        regressaoPanel = new RegressaoPanel();
        graficoPanel = new GraficoPanel();
        
        tabbedPane.addTab("Medições", medicoesPanel);
        tabbedPane.addTab("Filtros", filtrosPanel);
        tabbedPane.addTab("Regressão e Previsão", regressaoPanel);
        tabbedPane.addTab("Gráfico", criarPainelGraficoComExportacao());
        
        progressBarR2 = new JProgressBar(0, 100);
        progressBarR2.setStringPainted(true);
        
        add(tabbedPane, BorderLayout.CENTER);
        add(progressBarR2, BorderLayout.SOUTH);
    }

    /**
     * Envolve o GraficoPanel (superfície de desenho) num container com uma
     * barra de ferramentas contendo o botão de exportar o gráfico como PNG,
     * mantendo o GraficoPanel focado apenas em desenhar.
     */
    private JPanel criarPainelGraficoComExportacao() {
        JPanel container = new JPanel(new BorderLayout());

        JPanel barraFerramentas = new JPanel(new FlowLayout(FlowLayout.LEFT));
        btnSalvarGrafico = new JButton("Salvar gráfico como PNG");
        barraFerramentas.add(btnSalvarGrafico);

        container.add(barraFerramentas, BorderLayout.NORTH);
        container.add(graficoPanel, BorderLayout.CENTER);

        return container;
    }
    
    private void criarMenuBar() {
        menuBar = new JMenuBar();
        
        JMenu menuArquivo = new JMenu("Arquivo");
        itemCarregar = new JMenuItem("Carregar TSV");
        itemExportar = new JMenuItem("Exportar Relatório TSV");
        itemSair = new JMenuItem("Sair");
        
        menuArquivo.add(itemCarregar);
        menuArquivo.add(itemExportar);
        menuArquivo.addSeparator();
        menuArquivo.add(itemSair);
        
        JMenu menuFiltros = new JMenu("Filtros");
        itemLimparFiltros = new JMenuItem("Limpar todos filtros");
        menuFiltros.add(itemLimparFiltros);
        
        menuBar.add(menuArquivo);
        menuBar.add(menuFiltros);
        
        // Actions conectadas pelo SistemaController.inicializarEventos()
    }
    
    /**
     * DECISÃO DE DESIGN: o PDF do trabalho especifica a coloração da barra
     * como "Azul (R² <= 5), Amarelo (5 < R² <= 8), Vermelho (8 < R²)", sem
     * indicar a unidade desses números. Interpretamos como 50% e 80%
     * (frações 0,5 e 0,8) — e não 5% e 8% — porque com R² expresso como
     * fração 0–1 (como o resto do sistema já faz), um limiar de 0,05/0,08
     * faria a barra ficar vermelha para praticamente qualquer regressão
     * com correlação real, esvaziando o propósito da escala de 3 cores.
     * Com 0,5/0,8 a barra realmente varia conforme a qualidade do ajuste
     * observada nos datasets de teste do trabalho.
     */
    public void atualizarProgressBarR2(double r2) {
        int valor = (int) (r2 * 100);
        progressBarR2.setValue(valor);
        progressBarR2.setString(String.format("R² = %.4f", r2));
        
        // Colorir a barra conforme R² (ver decisão de design acima)
        if (r2 <= 0.5) {
            progressBarR2.setForeground(Color.BLUE);
        } else if (r2 <= 0.8) {
            progressBarR2.setForeground(Color.YELLOW);
        } else {
            progressBarR2.setForeground(Color.RED);
        }
    }
    
    public void limparProgressBarR2() {
        progressBarR2.setValue(0);
        progressBarR2.setString("R² indisponível (dados insuficientes)");
        progressBarR2.setForeground(Color.GRAY);
    }

    public void exibirMensagemErro(String msg) {
        JOptionPane.showMessageDialog(this, msg, "Erro", JOptionPane.ERROR_MESSAGE);
    }
    
    public void exibirMensagemInfo(String msg) {
        JOptionPane.showMessageDialog(this, msg, "Informação", JOptionPane.INFORMATION_MESSAGE);
    }


    // Getters para os componentes
    public MedicoesPanel getMedicoesPanel() { return medicoesPanel; }
    public FiltrosPanel getFiltrosPanel() { return filtrosPanel; }
    public RegressaoPanel getRegressaoPanel() { return regressaoPanel; }
    public GraficoPanel getGraficoPanel() { return graficoPanel; }
    public JMenuItem getItemCarregar() { return itemCarregar; }
    public JMenuItem getItemExportar() { return itemExportar; }
    public JMenuItem getItemSair() { return itemSair; }
    public JMenuItem getItemLimparFiltros() { return itemLimparFiltros; }
    public JButton getBtnSalvarGrafico() { return btnSalvarGrafico; }
}