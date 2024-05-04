import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class menuConfirmacion extends JDialog {
    private JPanel contentPane;
    private JButton buttonNO;
    private JButton ButtonSI;
    private JTextField estosCambiosSonIrreversiblesTextField;

    public menuConfirmacion(){
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonNO);

        buttonNO.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        ButtonSI.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                appGUI.confirmacion = true;
                dispose();
            }
        });
    }
}
