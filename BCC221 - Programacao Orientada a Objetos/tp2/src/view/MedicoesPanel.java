package view;

import model.Medicao;
import model.TabelaModel;
import view.renderers.OutlierTableCellRenderer;
import javax.swing.*;
import javax.swing.table.TableColumnModel;
import java.awt.*;

public class MedicoesPanel extends JPanel {
    private JTable tabela;
    private TabelaModel tableModel;
    private JButton btnAdicionar;
    private JButton btnRemover;
    private JScrollPane scrollPane;
    
    public MedicoesPanel(TabelaModel model) {
        this.tableModel = model != null ? model : new TabelaModel();
        inicializarComponentes();
    }
    
    private void inicializarComponentes() {
        setLayout(new BorderLayout());
        
        tabela = new JTable(tableModel);
        tabela.setFillsViewportHeight(true);
        // Fase 11: permite ordenar a tabela clicando no cabeçalho das colunas.
        // Isso faz o JTable passar a usar índices de "view" (posição visual,
        // que muda conforme a ordenação) diferentes dos índices de "model"
        // (posição real nos dados). Todo ponto que converte uma linha da
        // tabela em uma Medicao precisa converter view -> model antes.
        tabela.setAutoCreateRowSorter(true);
        
        aplicarRenderers();
        
        scrollPane = new JScrollPane(tabela);
        
        JPanel panelBotoes = new JPanel(new FlowLayout(FlowLayout.LEFT));
        btnAdicionar = new JButton("Adicionar linha");
        btnRemover = new JButton("Remover linha(s) selecionada(s)");
        
        panelBotoes.add(btnAdicionar);
        panelBotoes.add(btnRemover);
        
        add(scrollPane, BorderLayout.CENTER);
        add(panelBotoes, BorderLayout.SOUTH);
    }
    
    private void aplicarRenderers() {
        TableColumnModel colModel = tabela.getColumnModel();
        for (int i = 0; i < tabela.getColumnCount(); i++) {
            colModel.getColumn(i).setCellRenderer(new OutlierTableCellRenderer());
        }
    }
    
    public void atualizarTabela() {
        tableModel.fireTableDataChanged();
    }
    
    public int[] getLinhasSelecionadas() {
        // getSelectedRows() retorna índices de VIEW (posição visual, sujeita
        // à ordenação atual do RowSorter). Convertemos para índices de MODEL
        // para que o controller sempre remova/consulte a Medicao correta,
        // independente de como a tabela está ordenada no momento.
        int[] linhasView = tabela.getSelectedRows();
        int[] linhasModel = new int[linhasView.length];
        for (int i = 0; i < linhasView.length; i++) {
            linhasModel[i] = tabela.convertRowIndexToModel(linhasView[i]);
        }
        return linhasModel;
    }

    /**
     * Retorna a Medicao correspondente a uma linha da VIEW (ex: linha sob o
     * cursor do mouse ou clicada), convertendo corretamente para o índice
     * de model antes de consultar o TabelaModel.
     */
    public Medicao getMedicaoNaLinhaView(int linhaView) {
        if (linhaView < 0) return null;
        int linhaModel = tabela.convertRowIndexToModel(linhaView);
        return tableModel.getMedicaoAt(linhaModel);
    }
    
    public void limparSelecao() {
        tabela.clearSelection();
    }
    
    public TabelaModel getTableModel() {
        return tableModel;
    }
    
    public JButton getBtnAdicionar() { return btnAdicionar; }
    public JButton getBtnRemover() { return btnRemover; }

    /*
     * Substitui o TabelaModel usado pela tabela (ex: quando o
     * SistemaController injeta o model "oficial" compartilhado após a
     * MainFrame já ter instanciado este painel com um model provisório).
     */
    public void setTableModel(TabelaModel tableModel) {
        this.tableModel = tableModel;
        tabela.setModel(tableModel);
        aplicarRenderers();
    }
    
}