package view;

import model.Filtro;
import java.awt.FlowLayout;
import javax.swing.*;
import javax.swing.event.ChangeListener;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.function.Consumer;

public class FiltrosPanel extends JPanel {
    private JCheckBox chkTempo;
    private JSpinner spinnerDataInicio;
    private JSpinner spinnerDataFim;

    private JCheckBox chkTemperatura;
    private JSlider sliderTempMin;
    private JSlider sliderTempMax;

    private JCheckBox chkRaio;
    private JTextField txtLatitude;
    private JTextField txtLongitude;
    private JSpinner spinnerRaio;

    private JButton btnLimparFiltros;

    // Notifica o controller quando qualquer filtro muda, para reaplicação dinâmica
    private Runnable onFiltroAlterado;
    // Notifica o controller de erros de validação (ex: coordenada inválida)
    private Consumer<String> onErroValidacao;

    public FiltrosPanel() {
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        add(criarPainelTempo());
        add(criarPainelTemperatura());
        add(criarPainelRaio());

        btnLimparFiltros = new JButton("Limpar todos os filtros");
        add(btnLimparFiltros);

        atualizarHabilitacaoComponentes();
    }

    private JPanel criarPainelTempo() {
        JPanel painel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        painel.setBorder(BorderFactory.createTitledBorder("Intervalo de Tempo"));

        chkTempo = new JCheckBox("Ativar");
        chkTempo.addActionListener(e -> {
            atualizarHabilitacaoComponentes();
            notificarFiltroAlterado();
        });

        spinnerDataInicio = new JSpinner(new SpinnerDateModel());
        spinnerDataInicio.setEditor(new JSpinner.DateEditor(spinnerDataInicio, "yyyy-MM-dd HH:mm:ss"));

        spinnerDataFim = new JSpinner(new SpinnerDateModel());
        spinnerDataFim.setEditor(new JSpinner.DateEditor(spinnerDataFim, "yyyy-MM-dd HH:mm:ss"));

        ChangeListener listenerData = e -> notificarFiltroAlterado();
        spinnerDataInicio.addChangeListener(listenerData);
        spinnerDataFim.addChangeListener(listenerData);

        painel.add(chkTempo);
        painel.add(new JLabel("Início:"));
        painel.add(spinnerDataInicio);
        painel.add(new JLabel("Fim:"));
        painel.add(spinnerDataFim);

        return painel;
    }

    private JPanel criarPainelTemperatura() {
        JPanel painel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        painel.setBorder(BorderFactory.createTitledBorder("Intervalo de Temperatura"));

        chkTemperatura = new JCheckBox("Ativar");
        chkTemperatura.addActionListener(e -> {
            atualizarHabilitacaoComponentes();
            notificarFiltroAlterado();
        });

        sliderTempMin = new JSlider(-50, 60, -50);
        sliderTempMax = new JSlider(-50, 60, 60);
        sliderTempMin.setMajorTickSpacing(20);
        sliderTempMin.setMinorTickSpacing(5);
        sliderTempMin.setPaintTicks(true);
        sliderTempMin.setPaintLabels(true);
        sliderTempMax.setMajorTickSpacing(20);
        sliderTempMax.setMinorTickSpacing(5);
        sliderTempMax.setPaintTicks(true);
        sliderTempMax.setPaintLabels(true);

        // Mostram o valor numérico atual selecionado em cada slider, já que
        // a régua de ticks sozinha não deixa claro o valor exato arrastado.
        JLabel lblValorMin = new JLabel(sliderTempMin.getValue() + "°C");
        JLabel lblValorMax = new JLabel(sliderTempMax.getValue() + "°C");
        lblValorMin.setPreferredSize(new java.awt.Dimension(45, lblValorMin.getPreferredSize().height));
        lblValorMax.setPreferredSize(new java.awt.Dimension(45, lblValorMax.getPreferredSize().height));

        // Evita faixa invertida (mín > máx): ao mover um, empurra o outro junto
        sliderTempMin.addChangeListener(e -> {
            if (sliderTempMin.getValue() > sliderTempMax.getValue()) {
                sliderTempMax.setValue(sliderTempMin.getValue());
            }
            lblValorMin.setText(sliderTempMin.getValue() + "°C");
            notificarFiltroAlterado();
        });
        sliderTempMax.addChangeListener(e -> {
            if (sliderTempMax.getValue() < sliderTempMin.getValue()) {
                sliderTempMin.setValue(sliderTempMax.getValue());
            }
            lblValorMax.setText(sliderTempMax.getValue() + "°C");
            notificarFiltroAlterado();
        });

        painel.add(chkTemperatura);
        painel.add(new JLabel("Mín:"));
        painel.add(sliderTempMin);
        painel.add(lblValorMin);
        painel.add(new JLabel("Máx:"));
        painel.add(sliderTempMax);
        painel.add(lblValorMax);

        return painel;
    }

    private JPanel criarPainelRaio() {
        JPanel painel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        painel.setBorder(BorderFactory.createTitledBorder("Raio a partir de coordenada"));

        chkRaio = new JCheckBox("Ativar");
        chkRaio.addActionListener(e -> {
            atualizarHabilitacaoComponentes();
            notificarFiltroAlterado();
        });

        txtLatitude = new JTextField(10);
        txtLongitude = new JTextField(10);
        spinnerRaio = new JSpinner(new SpinnerNumberModel(0.0, 0.0, 1000.0, 10.0));

        // Validação só ao sair do campo (evita erro a cada tecla digitada)
        txtLatitude.addFocusListener(new java.awt.event.FocusAdapter() {
            @Override
            public void focusLost(java.awt.event.FocusEvent e) {
                notificarFiltroAlterado();
            }
        });
        txtLongitude.addFocusListener(new java.awt.event.FocusAdapter() {
            @Override
            public void focusLost(java.awt.event.FocusEvent e) {
                notificarFiltroAlterado();
            }
        });
        spinnerRaio.addChangeListener(e -> notificarFiltroAlterado());

        painel.add(chkRaio);
        painel.add(new JLabel("Latitude:"));
        painel.add(txtLatitude);
        painel.add(new JLabel("Longitude:"));
        painel.add(txtLongitude);
        painel.add(new JLabel("Raio (km):"));
        painel.add(spinnerRaio);

        return painel;
    }

    private void atualizarHabilitacaoComponentes() {
        spinnerDataInicio.setEnabled(chkTempo.isSelected());
        spinnerDataFim.setEnabled(chkTempo.isSelected());

        sliderTempMin.setEnabled(chkTemperatura.isSelected());
        sliderTempMax.setEnabled(chkTemperatura.isSelected());

        txtLatitude.setEnabled(chkRaio.isSelected());
        txtLongitude.setEnabled(chkRaio.isSelected());
        spinnerRaio.setEnabled(chkRaio.isSelected());
    }

    private void notificarFiltroAlterado() {
        if (onFiltroAlterado != null) {
            onFiltroAlterado.run();
        }
    }

    private void notificarErro(String mensagem) {
        if (onErroValidacao != null) {
            onErroValidacao.accept(mensagem);
        }
    }

    /**
     * Monta um objeto Filtro a partir do estado atual dos componentes da UI.
     * Só considera cada critério se o respectivo checkbox estiver marcado —
     * caso contrário aquele critério fica nulo (sem filtragem), evitando
     * que valores padrão dos componentes (ex: data atual do JSpinner)
     * filtrem os dados sem o usuário ter pedido isso.
     */
    public Filtro getFiltro() {
        Filtro filtro = new Filtro();

        if (chkTempo.isSelected()) {
            filtro.setDataInicio(converterParaLocalDateTime((Date) spinnerDataInicio.getValue()));
            filtro.setDataFim(converterParaLocalDateTime((Date) spinnerDataFim.getValue()));
        }

        if (chkTemperatura.isSelected()) {
            filtro.setTempMin((double) sliderTempMin.getValue());
            filtro.setTempMax((double) sliderTempMax.getValue());
        }

        if (chkRaio.isSelected()) {
            aplicarFiltroRaioNoObjeto(filtro);
        }

        return filtro;
    }

    private void aplicarFiltroRaioNoObjeto(Filtro filtro) {
        String textoLat = txtLatitude.getText().trim().replace(',', '.');
        String textoLon = txtLongitude.getText().trim().replace(',', '.');

        if (textoLat.isEmpty() || textoLon.isEmpty()) {
            notificarErro("Informe latitude e longitude para filtrar por raio.");
            return;
        }

        try {
            double lat = Double.parseDouble(textoLat);
            double lon = Double.parseDouble(textoLon);

            if (lat < -90 || lat > 90 || lon < -180 || lon > 180) {
                notificarErro("Coordenada de centro inválida (latitude -90 a 90, longitude -180 a 180).");
                return;
            }

            double raio = ((Number) spinnerRaio.getValue()).doubleValue();

            filtro.setLatitudeCentro(lat);
            filtro.setLongitudeCentro(lon);
            filtro.setRaioKm(raio);
        } catch (NumberFormatException e) {
            notificarErro("Latitude e longitude devem ser números válidos.");
        }
    }

    private LocalDateTime converterParaLocalDateTime(Date date) {
        return LocalDateTime.ofInstant(date.toInstant(), ZoneId.systemDefault());
    }

    /**
     * Restaura todos os componentes visuais para o estado inicial
     * (checkboxes desmarcados, sliders no range completo, campos vazios).
     */
    public void limparCampos() {
        chkTempo.setSelected(false);
        chkTemperatura.setSelected(false);
        chkRaio.setSelected(false);

        spinnerDataInicio.setValue(new Date());
        spinnerDataFim.setValue(new Date());

        sliderTempMin.setValue(-50);
        sliderTempMax.setValue(60);

        txtLatitude.setText("");
        txtLongitude.setText("");
        spinnerRaio.setValue(0.0);

        atualizarHabilitacaoComponentes();
    }

    public void setOnFiltroAlterado(Runnable onFiltroAlterado) {
        this.onFiltroAlterado = onFiltroAlterado;
    }

    public void setOnErroValidacao(Consumer<String> onErroValidacao) {
        this.onErroValidacao = onErroValidacao;
    }

    public double getTempMin() {
        return sliderTempMin.getValue();
    }

    public double getTempMax() {
        return sliderTempMax.getValue();
    }

    public JButton getBtnLimparFiltros() { return btnLimparFiltros; }
    public JSpinner getSpinnerDataInicio() { return spinnerDataInicio; }
    public JSpinner getSpinnerDataFim() { return spinnerDataFim; }
    public JSlider getSliderTempMin() { return sliderTempMin; }
    public JSlider getSliderTempMax() { return sliderTempMax; }
    public JTextField getTxtLatitude() { return txtLatitude; }
    public JTextField getTxtLongitude() { return txtLongitude; }
    public JSpinner getSpinnerRaio() { return spinnerRaio; }
    public JCheckBox getChkTempo() { return chkTempo; }
    public JCheckBox getChkTemperatura() { return chkTemperatura; }
    public JCheckBox getChkRaio() { return chkRaio; }
}