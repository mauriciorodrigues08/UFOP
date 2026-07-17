package model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ErroValidacao {
    private int errosCoordenada;
    private int errosTemperatura;
    private int errosConsumo;
    private int errosFormato;
    private int linhasProcessadas;
    private int linhasValidas;
    private List<String> detalhesErros;
    
    public ErroValidacao() {
        detalhesErros = new ArrayList<>();
        resetar();
    }
    
    public void incrementarErroCoordenada() {
        errosCoordenada++;
    }
    
    public void incrementarErroTemperatura() {
        errosTemperatura++;
    }
    
    public void incrementarErroConsumo() {
        errosConsumo++;
    }
    
    public void incrementarErroFormato() {
        errosFormato++;
    }
    
    /*
     * Registra o motivo detalhado da rejeição de uma linha específica.
     * @param numeroLinha número da linha no arquivo (a linha 1 é o cabeçalho)
     * @param motivo descrição do motivo da rejeição
     */
    public void registrarErroDetalhado(int numeroLinha, String motivo) {
        detalhesErros.add("Linha " + numeroLinha + ": " + motivo);
    }
    
    public void incrementarLinhasProcessadas() {
        linhasProcessadas++;
    }
    
    public void incrementarLinhasValidas() {
        linhasValidas++;
    }
    
    public String getMensagemResumo() {
        StringBuilder sb = new StringBuilder();
        sb.append("=== RESUMO DE VALIDAÇÃO ===\n");
        sb.append("Linhas processadas: ").append(linhasProcessadas).append("\n");
        sb.append("Linhas válidas: ").append(linhasValidas).append("\n");
        sb.append("Linhas rejeitadas: ").append(linhasProcessadas - linhasValidas).append("\n\n");
        sb.append("Erros por tipo:\n");
        sb.append("- Erro de coordenada: ").append(errosCoordenada).append("\n");
        sb.append("- Erro de temperatura: ").append(errosTemperatura).append("\n");
        sb.append("- Erro de consumo: ").append(errosConsumo).append("\n");
        sb.append("- Erro de formato: ").append(errosFormato).append("\n");
        
        if (!detalhesErros.isEmpty()) {
            sb.append("\nDetalhes (até 20 primeiras rejeições):\n");
            int limite = Math.min(20, detalhesErros.size());
            for (int i = 0; i < limite; i++) {
                sb.append("  ").append(detalhesErros.get(i)).append("\n");
            }
            if (detalhesErros.size() > limite) {
                sb.append("  ... e mais ").append(detalhesErros.size() - limite).append(" linha(s) rejeitada(s).\n");
            }
        }
        
        return sb.toString();
    }
    
    public void resetar() {
        errosCoordenada = 0;
        errosTemperatura = 0;
        errosConsumo = 0;
        errosFormato = 0;
        linhasProcessadas = 0;
        linhasValidas = 0;
        if (detalhesErros != null) {
            detalhesErros.clear();
        }
    }
    
    public boolean temErros() {
        return (linhasProcessadas - linhasValidas) > 0;
    }
    
    public List<String> getDetalhesErros() {
        return Collections.unmodifiableList(detalhesErros);
    }
    
    // Getters adicionais
    public int getErrosCoordenada() { return errosCoordenada; }
    public int getErrosTemperatura() { return errosTemperatura; }
    public int getErrosConsumo() { return errosConsumo; }
    public int getErrosFormato() { return errosFormato; }
    public int getLinhasProcessadas() { return linhasProcessadas; }
    public int getLinhasValidas() { return linhasValidas; }
}