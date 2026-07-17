package model;

import javax.swing.table.AbstractTableModel;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.function.Consumer;

/**
 * Modelo de tabela para exibição de medições.
 *
 * Esta classe é intencionalmente "burra": ela apenas exibe a lista de
 * medições que lhe é passada via {@link #setDados(List)}. Toda a lógica de
 * filtragem (tempo, temperatura, raio) e exclusão de outliers é de
 * responsabilidade do SistemaController, que decide o que deve estar
 * visível e repassa a lista final para cá. Isso evita ter duas fontes de
 * verdade divergentes sobre quais dados estão sendo exibidos.
 */
public class TabelaModel extends AbstractTableModel {
    private List<Medicao> dados;
    private final String[] colunas;

    private static final DateTimeFormatter FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    private static final double TEMP_MIN = -50.0;
    private static final double TEMP_MAX = 60.0;

    // Limite de resíduo percentual usado para destacar outliers na tabela
    // (lido pelo OutlierTableCellRenderer). Fonte única de verdade para
    // que todas as colunas/renderers usem sempre o mesmo valor atual.
    private double limiteOutlierPercentual = 10.0;

    // Callbacks para desacoplar a TabelaModel de componentes Swing/Controller
    private Runnable onDadosAlterados;
    private Consumer<String> onErroValidacao;

    public TabelaModel() {
        this.dados = new ArrayList<>();
        this.colunas = new String[]{
            "Timestamp", "Cidade", "Latitude", "Longitude",
            "Temperatura (°C)", "Consumo (kWh)",
            "Consumo Previsto (kWh)", "Resíduo Percentual (%)"
        };
    }

    @Override
    public int getRowCount() {
        return dados.size();
    }

    @Override
    public int getColumnCount() {
        return colunas.length;
    }

    @Override
    public String getColumnName(int column) {
        return colunas[column];
    }

    /**
     * Informa ao JTable o tipo real de cada coluna. Sem isso, o
     * RowSorter padrão (ativado na Fase 11) ordenaria as colunas
     * numéricas como texto (ex: "9" depois de "10"), o que é incorreto
     * para Temperatura, Consumo e Resíduo Percentual.
     */
    @Override
    public Class<?> getColumnClass(int columnIndex) {
        switch (columnIndex) {
            case 0: // Timestamp (já formatado como String)
            case 1: // Cidade
                return String.class;
            case 2: case 3: case 4: case 5: case 6: case 7:
                return Double.class;
            default:
                return Object.class;
        }
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Medicao m = dados.get(rowIndex);

        switch (columnIndex) {
            case 0: return m.getTimestamp().format(FORMATTER);
            case 1: return m.getCidade();
            case 2: return m.getLatitude();
            case 3: return m.getLongitude();
            case 4: return m.getTemperatura();
            case 5: return m.getConsumoKwh();
            case 6: return m.getConsumoPrevisto();
            case 7: return m.getResiduoPercentual();
            default: return null;
        }
    }

    @Override
    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        if (rowIndex < 0 || rowIndex >= dados.size()) {
            return;
        }
        if (columnIndex != 4 && columnIndex != 5) {
            return; // outras colunas não são editáveis
        }

        double novoValor;
        try {
            if (value instanceof Number) {
                novoValor = ((Number) value).doubleValue();
            } else {
                novoValor = Double.parseDouble(value.toString().trim().replace(',', '.'));
            }
        } catch (NumberFormatException e) {
            notificarErro("Valor inválido: informe um número.");
            return;
        }

        Medicao m = dados.get(rowIndex);

        if (columnIndex == 4) { // Temperatura
            if (novoValor < TEMP_MIN || novoValor > TEMP_MAX) {
                notificarErro(String.format(
                        "Temperatura fora da faixa permitida [%.0f, %.0f] °C.", TEMP_MIN, TEMP_MAX));
                return;
            }
            m.setTemperatura(novoValor);
        } else { // Consumo (columnIndex == 5)
            if (novoValor < 0) {
                notificarErro("Consumo não pode ser negativo.");
                return;
            }
            m.setConsumoKwh(novoValor);
        }

        fireTableCellUpdated(rowIndex, columnIndex);

        if (onDadosAlterados != null) {
            onDadosAlterados.run();
        }
    }

    private void notificarErro(String mensagem) {
        if (onErroValidacao != null) {
            onErroValidacao.accept(mensagem);
        }
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return columnIndex == 4 || columnIndex == 5;
    }

    public Medicao getMedicaoAt(int row) {
        if (row >= 0 && row < dados.size()) {
            return dados.get(row);
        }
        return null;
    }

    /**
     * Substitui os dados atualmente exibidos na tabela.
     * Ponto único de entrada de dados — quem decide o que deve estar
     * visível (após filtros e exclusão de outliers) é o SistemaController.
     */
    public void setDados(List<Medicao> dados) {
        this.dados = new ArrayList<>(dados);
        fireTableDataChanged();
    }

    public List<Medicao> getDados() {
        return dados;
    }

    public double getLimiteOutlierPercentual() {
        return limiteOutlierPercentual;
    }

    public void setLimiteOutlierPercentual(double limiteOutlierPercentual) {
        this.limiteOutlierPercentual = limiteOutlierPercentual;
        fireTableDataChanged(); // força repintura para refletir o novo destaque
    }

    public void setOnDadosAlterados(Runnable onDadosAlterados) {
        this.onDadosAlterados = onDadosAlterados;
    }

    public void setOnErroValidacao(Consumer<String> onErroValidacao) {
        this.onErroValidacao = onErroValidacao;
    }
}