import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.sql.ResultSet;
import java.sql.SQLException;

public class aniadirDetalles extends JDialog {

    private JPanel contentPane;
    private JButton buttonDesconectar;
    private JTextField codigoProducto;
    private JTextField cantidadAPedir;

    public aniadirDetalles(){
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonDesconectar);
        buttonDesconectar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    confirmar();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    confirmar();
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);

    }

    private void confirmar() throws SQLException {
        int codpro = Integer.parseInt(codigoProducto.getText());
        int cantped = Integer.parseInt(cantidadAPedir.getText());

        ResultSet rs= ddsiAPP.statement.executeQuery("select count(*) from STOCK where Cproducto= '"+codpro+"'");
        boolean transacc_posible = false;

        transacc_posible = ddsiAPP.existeProducto(rs, codpro, cantped);
        if (transacc_posible) {
            ddsiAPP.addDetalle(pedido.codped, codpro, cantped);
            ddsiAPP.save3 = ddsiAPP.conexion.setSavepoint();
            ddsiAPP.hay_un_detalle = true;
        }
        else{
            if(ddsiAPP.errorStock){
                JOptionPane.showMessageDialog(null, "No hay suficiente stock del producto");
                ddsiAPP.errorStock = false;
            }
            else if(ddsiAPP.errorNoProduct){
                JOptionPane.showMessageDialog(null, "No se ha encontrado el producto solicitado");
                ddsiAPP.errorNoProduct = false;
            }
        }
        appGUI.actualizarTablas();
        ddsiAPP.pstatement.close();

        dispose();
    }
}
