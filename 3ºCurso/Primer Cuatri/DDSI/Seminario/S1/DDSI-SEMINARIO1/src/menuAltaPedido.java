import javax.swing.*;
import java.awt.event.*;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Savepoint;

public class menuAltaPedido extends JDialog {
    private JPanel contentPane;
    private JButton buttonDesconectar;
    private JButton añadirDetallesDeProductoButton;
    private JButton eliminarTodosLosDetallesButton;
    private JButton cancelarPedidoButton;

    public menuAltaPedido() {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonDesconectar);

        buttonDesconectar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                desconectar();
            }
        });

        // call desconectar() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                desconectar();
            }
        });

        // call desconectar() on ESCAPE
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                desconectar();
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);

        añadirDetallesDeProductoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    ddsiAPP.pstatement = ddsiAPP.conexion.prepareStatement(ddsiAPP.SQL_INSERT_DETALLES_PEDIDO);

                    aniadirDetalles dialog2 = new aniadirDetalles();
                    dialog2.pack();
                    dialog2.setVisible(true);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

            }
        });
        buttonDesconectar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if(ddsiAPP.hay_un_detalle) {
                    try {
                        ddsiAPP.finalizarPedido();
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }
                    ddsiAPP.quit = true;
                }
                else{
                    System.out.println("No existe ningún detalle de este pedido, introduce alguno o cancela el pedido.");
                }
            }
        });
        cancelarPedidoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    ddsiAPP.conexion.rollback(ddsiAPP.save1);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
                ddsiAPP.quit = true;
                ddsiAPP.hay_un_detalle = false;

                appGUI.actualizarTablas();
                dispose();
            }
        });
        eliminarTodosLosDetallesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                /*Muestra el dialogo de confirmacion*/
                menuConfirmacion dialog = new menuConfirmacion();
                dialog.pack();
                dialog.setVisible(true);

                /*Si se elige si, el codigo se ejecuta. En caso contrario, no hace nada*/
                if(appGUI.confirmacion) {
                    try {
                        ddsiAPP.conexion.rollback(ddsiAPP.save2);
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }

                    appGUI.confirmacion = false;
                    ddsiAPP.hay_un_detalle = false;
                    appGUI.actualizarTablas();
                }
            }
        });
    }

    private void desconectar() {
        if(ddsiAPP.quit)
            dispose();
        else
            JOptionPane.showMessageDialog(null, "No existe ningún detalle de este pedido, introduce alguno o cancela el pedido.");
    }

    public static void main(String[] args) {
        menuAltaPedido dialog = new menuAltaPedido();
        dialog.pack();
        dialog.setVisible(true);


//        boolean quit = false;
//        do{
//
//        }
//        while(!quit);

        System.exit(0);
    }

}
