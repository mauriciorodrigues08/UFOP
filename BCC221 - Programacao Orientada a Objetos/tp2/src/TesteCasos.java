import model.Medicao;
import model.MedicaoDAO;
import model.ErroValidacao;
import model.RegressaoLinear;
import java.io.File;
import java.util.List;

public class TesteCasos {
    public static void main(String[] args) throws Exception {
        for (String nome : args) {
            System.out.println("################################################");
            System.out.println("Arquivo: " + nome);
            MedicaoDAO dao = new MedicaoDAO();
            List<Medicao> medicoes = dao.carregarDeTSV(new File(nome));
            ErroValidacao erros = dao.getErros();

            System.out.println("Medições válidas: " + medicoes.size());
            System.out.println(erros.getMensagemResumo());

            RegressaoLinear reg = new RegressaoLinear();
            boolean ok = reg.calcular(medicoes);
            if (ok) {
                System.out.printf("beta0=%.4f beta1=%.4f R2=%.4f N=%d%n",
                        reg.getBeta0(), reg.getBeta1(), reg.getR2(), reg.getN());
            } else {
                System.out.println("Regressão NÃO calculada (menos de 2 medições válidas).");
            }
            System.out.println();
        }
    }
}