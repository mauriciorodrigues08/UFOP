package view.renderers;

import model.Medicao;
import model.TabelaModel;
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import java.awt.*;

public class OutlierTableCellRenderer extends DefaultTableCellRenderer {

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
                                                   boolean isSelected, boolean hasFocus,
                                                   int row, int column) {
        Component c = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        
        TabelaModel model = (TabelaModel) table.getModel();
        // O JTable com RowSorter (ativado na Fase 11) chama o renderer com o
        // índice de VIEW, que difere do índice de MODEL quando a tabela está
        // ordenada. Sem essa conversão, o destaque de outlier (e a
        // formatação numérica abaixo) mostrariam a Medicao errada.
        int modelRow = table.convertRowIndexToModel(row);
        Medicao m = model.getMedicaoAt(modelRow);
        double limiteOutlier = model.getLimiteOutlierPercentual();
        
        if (m != null && Math.abs(m.getResiduoPercentual()) > limiteOutlier) {
            if (!isSelected) {
                c.setBackground(Color.RED);
                c.setForeground(Color.WHITE);
            } else {
                c.setBackground(Color.MAGENTA);
                c.setForeground(Color.BLACK);
            }
        } else {
            if (!isSelected) {
                // Fundo alternado ou padrão
                if (row % 2 == 0) {
                    c.setBackground(new Color(240, 248, 255)); // AliceBlue
                } else {
                    c.setBackground(Color.WHITE);
                }
                c.setForeground(Color.BLACK);
            } else {
                c.setBackground(table.getSelectionBackground());
                c.setForeground(table.getSelectionForeground());
            }
        }
        
        // Formatação para colunas numéricas
        if (column == 4) { // Temperatura
            setText(String.format("%.2f°C", (Double) value));
        } else if (column == 5 || column == 6) { // Consumo
            setText(String.format("%.2f", (Double) value));
        } else if (column == 7) { // Resíduo
            setText(String.format("%.2f%%", (Double) value));
        }
        
        return c;
    }
}