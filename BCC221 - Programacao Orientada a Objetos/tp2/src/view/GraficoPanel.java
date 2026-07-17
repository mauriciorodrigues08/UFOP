package view;

import model.Medicao;
import model.RegressaoLinear;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class GraficoPanel extends JPanel {
    private List<Medicao> dados;
    private RegressaoLinear regressao;
    private double limiteOutlier;
    private int largura, altura;
    private int margemEsquerda = 60;
    private int margemDireita = 40;
    private int margemTopo = 40;
    private int margemBase = 60;

    // Limites de escala (com margem de 5%) usados tanto para plotar os
    // pontos quanto a reta de regressão, garantindo que ambos usem
    // exatamente o mesmo sistema de coordenadas.
    private double minTempEscala, maxTempEscala;
    private double minConsumoEscala, maxConsumoEscala;

    // Posições em tela de cada ponto plotado (recalculado a cada
    // paintComponent), usado para localizar o ponto mais próximo do
    // cursor do mouse e exibir o tooltip correspondente.
    private final List<PontoTela> pontosTela = new ArrayList<>();
    private static final int RAIO_DETECCAO_MOUSE = 8; // pixels
    private static final DateTimeFormatter FORMATTER_TOOLTIP =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    /** Associa a posição em tela de um ponto plotado à medição que ele representa. */
    private static class PontoTela {
        final int x, y;
        final Medicao medicao;
        PontoTela(int x, int y, Medicao medicao) {
            this.x = x;
            this.y = y;
            this.medicao = medicao;
        }
    }
    
    public GraficoPanel() {
        setBackground(Color.WHITE);
        setPreferredSize(new Dimension(800, 500));
        setToolTipText(""); // registra o painel no ToolTipManager para habilitar getToolTipText()
    }
    
    public void atualizarDados(List<Medicao> dados, RegressaoLinear regressao, double limiteOutlier) {
        this.dados = dados;
        this.regressao = regressao;
        this.limiteOutlier = limiteOutlier;
        repaint();
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        largura = getWidth();
        altura = getHeight();
        
        if (dados == null || dados.isEmpty()) {
            desenharMensagemSemDados(g2);
            return;
        }
        
        calcularEscala();
        desenharEixos(g2);
        desenharPontos(g2);
        
        if (regressao != null && regressao.getN() >= 2) {
            desenharRetaRegressao(g2);
            desenharEquacao(g2);
        }
        
        desenharLegenda(g2);
    }

    /**
     * Calcula os limites de escala (com margem de 5%) usados tanto para os
     * eixos quanto para plotar pontos e a reta de regressão, garantindo que
     * tudo use exatamente o mesmo sistema de coordenadas.
     */
    private void calcularEscala() {
        double minTemp = getMinTemperatura();
        double maxTemp = getMaxTemperatura();
        double minConsumo = getMinConsumo();
        double maxConsumo = getMaxConsumo();

        double margemTemp = Math.max((maxTemp - minTemp) * 0.05, 0.5);
        double margemConsumo = Math.max((maxConsumo - minConsumo) * 0.05, 0.5);

        minTempEscala = minTemp - margemTemp;
        maxTempEscala = maxTemp + margemTemp;
        minConsumoEscala = minConsumo - margemConsumo;
        maxConsumoEscala = maxConsumo + margemConsumo;
    }
    
    private void desenharEixos(Graphics2D g2) {
        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(2));
        
        // Eixo X
        g2.drawLine(margemEsquerda, altura - margemBase, 
                    largura - margemDireita, altura - margemBase);
        
        // Eixo Y
        g2.drawLine(margemEsquerda, margemTopo, 
                    margemEsquerda, altura - margemBase);

        desenharMarcacoesEixos(g2);
        
        // Rótulos dos eixos
        g2.setFont(new Font("Arial", Font.BOLD, 12));
        g2.drawString("Temperatura (°C)", largura / 2, altura - 10);
        
        g2.rotate(-Math.PI / 2);
        g2.drawString("Consumo (kWh)", -altura / 2, 20);
        g2.rotate(Math.PI / 2);
    }

    /** Desenha marcações numéricas ao longo dos eixos X e Y (5 divisões cada). */
    private void desenharMarcacoesEixos(Graphics2D g2) {
        g2.setColor(Color.DARK_GRAY);
        g2.setStroke(new BasicStroke(1));
        g2.setFont(new Font("Arial", Font.PLAIN, 10));

        int divisoes = 5;

        // Marcações do eixo X (temperatura)
        for (int i = 0; i <= divisoes; i++) {
            double valor = minTempEscala + (maxTempEscala - minTempEscala) * i / divisoes;
            int x = escalaX(valor);
            int yEixo = altura - margemBase;
            g2.drawLine(x, yEixo, x, yEixo + 4);
            String texto = String.format("%.1f", valor);
            g2.drawString(texto, x - texto.length() * 3, yEixo + 16);
        }

        // Marcações do eixo Y (consumo)
        for (int i = 0; i <= divisoes; i++) {
            double valor = minConsumoEscala + (maxConsumoEscala - minConsumoEscala) * i / divisoes;
            int y = escalaY(valor);
            g2.drawLine(margemEsquerda - 4, y, margemEsquerda, y);
            String texto = String.format("%.0f", valor);
            g2.drawString(texto, margemEsquerda - 10 - texto.length() * 6, y + 4);
        }
    }
    
    private void desenharPontos(Graphics2D g2) {
        pontosTela.clear();
        int raio = 4;
        for (Medicao m : dados) {
            int x = escalaX(m.getTemperatura());
            int y = escalaY(m.getConsumoKwh());

            boolean outlier = Math.abs(m.getResiduoPercentual()) > limiteOutlier;
            g2.setColor(outlier ? Color.RED : Color.BLACK);
            g2.fillOval(x - raio, y - raio, raio * 2, raio * 2);

            pontosTela.add(new PontoTela(x, y, m));
        }
    }

    /**
     * Retorna o texto do tooltip para a medição cujo ponto plotado esteja
     * mais próximo do cursor do mouse, dentro de um raio de detecção.
     * Retorna null (sem tooltip) se nenhum ponto estiver próximo o
     * suficiente.
     */
    @Override
    public String getToolTipText(MouseEvent event) {
        PontoTela maisProximo = null;
        double menorDistancia = Double.MAX_VALUE;

        for (PontoTela p : pontosTela) {
            double dx = p.x - event.getX();
            double dy = p.y - event.getY();
            double distancia = Math.sqrt(dx * dx + dy * dy);
            if (distancia <= RAIO_DETECCAO_MOUSE && distancia < menorDistancia) {
                menorDistancia = distancia;
                maisProximo = p;
            }
        }

        if (maisProximo == null) {
            return null;
        }

        Medicao m = maisProximo.medicao;
        boolean outlier = Math.abs(m.getResiduoPercentual()) > limiteOutlier;

        return String.format(
                "<html><b>%s</b>%s<br>%s<br>" +
                "Temperatura: %.2f °C<br>" +
                "Consumo real: %.2f kWh<br>" +
                "Consumo previsto: %.2f kWh<br>" +
                "Resíduo: %.2f%%</html>",
                m.getCidade(), outlier ? " <font color='red'>(outlier)</font>" : "",
                m.getTimestamp().format(FORMATTER_TOOLTIP),
                m.getTemperatura(), m.getConsumoKwh(),
                m.getConsumoPrevisto(), m.getResiduoPercentual()
        );
    }

    /** Converte uma temperatura para a coordenada X em pixels no painel. */
    private int escalaX(double temperatura) {
        if (maxTempEscala == minTempEscala) {
            return (margemEsquerda + (largura - margemDireita)) / 2;
        }
        double proporcao = (temperatura - minTempEscala) / (maxTempEscala - minTempEscala);
        return margemEsquerda + (int) Math.round(proporcao * (largura - margemEsquerda - margemDireita));
    }

    /** Converte um consumo para a coordenada Y em pixels no painel (eixo Y invertido). */
    private int escalaY(double consumo) {
        if (maxConsumoEscala == minConsumoEscala) {
            return (margemTopo + (altura - margemBase)) / 2;
        }
        double proporcao = (consumo - minConsumoEscala) / (maxConsumoEscala - minConsumoEscala);
        return (altura - margemBase) - (int) Math.round(proporcao * (altura - margemBase - margemTopo));
    }
    
    private void desenharRetaRegressao(Graphics2D g2) {
        if (regressao == null) return;

        g2.setColor(Color.BLUE);
        g2.setStroke(new BasicStroke(2));

        // Desenha a reta y = beta0 + beta1*x cobrindo toda a faixa de
        // temperatura visível (incluindo a margem), usando exatamente a
        // mesma escala usada para os pontos.
        double x1 = minTempEscala;
        double x2 = maxTempEscala;
        double y1 = regressao.preverConsumo(x1);
        double y2 = regressao.preverConsumo(x2);

        int px1 = escalaX(x1);
        int py1 = escalaY(y1);
        int px2 = escalaX(x2);
        int py2 = escalaY(y2);

        g2.drawLine(px1, py1, px2, py2);
    }
    
    private void desenharEquacao(Graphics2D g2) {
        if (regressao == null) return;
        
        g2.setColor(Color.BLACK);
        g2.setFont(new Font("Monospaced", Font.PLAIN, 12));
        
        String eq = String.format("y = %.4f x + %.4f", regressao.getBeta1(), regressao.getBeta0());
        String r2 = String.format("R² = %.4f", regressao.getR2());
        
        g2.drawString(eq, margemEsquerda + 10, margemTopo + 20);
        g2.drawString(r2, margemEsquerda + 10, margemTopo + 40);
    }
    
    private void desenharLegenda(Graphics2D g2) {
        int x = largura - margemDireita - 100;
        int y = margemTopo;
        
        g2.setFont(new Font("Arial", Font.PLAIN, 10));
        
        g2.setColor(Color.BLACK);
        g2.fillOval(x, y, 8, 8);
        g2.drawString("Normal", x + 12, y + 8);
        
        g2.setColor(Color.RED);
        g2.fillOval(x, y + 20, 8, 8);
        g2.drawString("Outlier", x + 12, y + 28);
        
        g2.setColor(Color.BLUE);
        g2.drawLine(x, y + 45, x + 20, y + 45);
        g2.drawString("Regressão", x + 24, y + 49);
    }
    
    private void desenharMensagemSemDados(Graphics2D g2) {
        g2.setColor(Color.GRAY);
        g2.setFont(new Font("Arial", Font.BOLD, 14));
        g2.drawString("Sem dados para exibir", largura / 2 - 80, altura / 2);
    }
    
    private double getMinTemperatura() {
        if (dados == null || dados.isEmpty()) return 0;
        return dados.stream().mapToDouble(Medicao::getTemperatura).min().orElse(0);
    }
    
    private double getMaxTemperatura() {
        if (dados == null || dados.isEmpty()) return 0;
        return dados.stream().mapToDouble(Medicao::getTemperatura).max().orElse(0);
    }
    
    private double getMinConsumo() {
        if (dados == null || dados.isEmpty()) return 0;
        return dados.stream().mapToDouble(Medicao::getConsumoKwh).min().orElse(0);
    }
    
    private double getMaxConsumo() {
        if (dados == null || dados.isEmpty()) return 0;
        return dados.stream().mapToDouble(Medicao::getConsumoKwh).max().orElse(0);
    }
}