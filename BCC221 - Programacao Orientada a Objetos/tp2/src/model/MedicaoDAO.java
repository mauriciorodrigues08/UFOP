package model;

import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class MedicaoDAO {
    private ErroValidacao erros;
    private static final DateTimeFormatter FORMATTER = 
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    
    // Limites de validação
    private static final double LAT_MIN = -90.0;
    private static final double LAT_MAX = 90.0;
    private static final double LON_MIN = -180.0;
    private static final double LON_MAX = 180.0;
    private static final double TEMP_MIN = -50.0;
    private static final double TEMP_MAX = 60.0;
    
    public MedicaoDAO() {
        this.erros = new ErroValidacao();
    }
    
    public List<Medicao> carregarDeTSV(File arquivo) throws IOException {
        List<Medicao> medicacoes = new ArrayList<>();
        erros.resetar();
        
        try (BufferedReader reader = new BufferedReader(new FileReader(arquivo))) {
            String linha;
            boolean primeiraLinha = true;
            int numeroLinha = 0;
            
            while ((linha = reader.readLine()) != null) {
                numeroLinha++;
                
                if (primeiraLinha) {
                    primeiraLinha = false;
                    continue; // pula cabeçalho (não conta como linha de dados processada)
                }
                
                if (linha.trim().isEmpty()) {
                    continue; // ignora linhas em branco silenciosamente
                }
                
                erros.incrementarLinhasProcessadas();
                
                Medicao m = parseLinha(linha, numeroLinha);
                if (m != null) {
                    medicacoes.add(m);
                    erros.incrementarLinhasValidas();
                }
            }
        }
        
        return medicacoes;
    }
    
    private Medicao parseLinha(String linha, int numeroLinha) {
        String[] campos = linha.split("\t");
        if (campos.length < 6) {
            erros.incrementarErroFormato();
            erros.registrarErroDetalhado(numeroLinha,
                    "formato inválido (esperado 6 colunas, encontrado " + campos.length + ")");
            return null;
        }
        
        LocalDateTime timestamp;
        try {
            timestamp = LocalDateTime.parse(campos[0].trim(), FORMATTER);
        } catch (Exception e) {
            erros.incrementarErroFormato();
            erros.registrarErroDetalhado(numeroLinha,
                    "timestamp inválido '" + campos[0].trim() + "' (esperado yyyy-MM-dd HH:mm:ss)");
            return null;
        }
        
        String cidade = campos[1].trim();
        if (cidade.isEmpty()) {
            erros.incrementarErroFormato();
            erros.registrarErroDetalhado(numeroLinha, "cidade vazia");
            return null;
        }
        
        double latitude, longitude, temperatura, consumoKwh;
        try {
            latitude = Double.parseDouble(campos[2].trim());
            longitude = Double.parseDouble(campos[3].trim());
            temperatura = Double.parseDouble(campos[4].trim());
            consumoKwh = Double.parseDouble(campos[5].trim());
        } catch (NumberFormatException e) {
            erros.incrementarErroFormato();
            erros.registrarErroDetalhado(numeroLinha, "valor numérico inválido (" + e.getMessage() + ")");
            return null;
        }
        
        // Validações de domínio
        if (!validarCoordenada(latitude, longitude)) {
            erros.incrementarErroCoordenada();
            erros.registrarErroDetalhado(numeroLinha,
                    "coordenada fora da faixa (lat=" + latitude + ", lon=" + longitude + ")");
            return null;
        }
        
        if (!validarTemperatura(temperatura)) {
            erros.incrementarErroTemperatura();
            erros.registrarErroDetalhado(numeroLinha,
                    "temperatura fora da faixa [" + TEMP_MIN + ", " + TEMP_MAX + "] (valor=" + temperatura + ")");
            return null;
        }
        
        if (!validarConsumo(consumoKwh)) {
            erros.incrementarErroConsumo();
            erros.registrarErroDetalhado(numeroLinha,
                    "consumo negativo (valor=" + consumoKwh + ")");
            return null;
        }
        
        return new Medicao(timestamp, cidade, latitude, longitude, temperatura, consumoKwh);
    }
    
    public boolean validarCoordenada(double lat, double lon) {
        return lat >= LAT_MIN && lat <= LAT_MAX && lon >= LON_MIN && lon <= LON_MAX;
    }
    
    public boolean validarTemperatura(double temp) {
        return temp >= TEMP_MIN && temp <= TEMP_MAX;
    }
    
    public boolean validarConsumo(double consumo) {
        return consumo >= 0;
    }
    
    public ErroValidacao getErros() {
        return erros;
    }
}