import javax.swing.*;
import java.awt.event.*;
import java.sql.SQLException;
import java.sql.Savepoint;
import java.text.ParseException;

public class pedido extends JDialog {
    private JButton buttonDesconectar;

    static int codped;
    public pedido() {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonDesconectar);

        buttonDesconectar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    desconectar();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });

        // call desconectar() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });


        // call desconectar() on ESCAPE
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    desconectar();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    }

    private void desconectar() throws SQLException {
        ddsiAPP.hay_un_detalle = false;
        ddsiAPP.conexion.setAutoCommit(false);
        ddsiAPP.save1 = ddsiAPP.conexion.setSavepoint();

        codped = Integer.parseInt(codPedido.getText());
        int codprod = Integer.parseInt(codProd.getText());
        String fecha = fechaPedido.getText();

        ddsiAPP.addPedidoToDB(codped, codprod, fecha); //Obtiene los datos del pedido
        appGUI.actualizarTablas();
        ddsiAPP.save2 = ddsiAPP.conexion.setSavepoint();

        dispose();

        menuAltaPedido dialog2 = new menuAltaPedido();
        dialog2.pack();
        dialog2.setVisible(true);

    }

    private JPanel contentPane;
    private JTextField codPedido;
    private JTextField codProd;
    private JTextField fechaPedido;
    private JButton desconectar;
}
