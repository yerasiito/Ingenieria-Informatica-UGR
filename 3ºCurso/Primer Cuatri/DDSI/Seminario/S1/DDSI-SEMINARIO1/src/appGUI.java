import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.*;
import java.sql.*;

public class appGUI extends JDialog {
    private JPanel contentPane;
    private JButton buttonDesconectar;
    private JTable tableStock;
    private JTable tablePedido;
    private JTable tableDetallePedido;
    private JButton insertarTuplasButton;
    private JButton actualizarTablasButton;
    private JButton darDeAltaPedidoButton;
    private JButton borrarTablasButton;
    private JButton crearTablasButton;

    private static DefaultTableModel model;
    private static DefaultTableModel model1;
    private static DefaultTableModel model2;

    static boolean confirmacion = false;

    public appGUI() {
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

        //Borra y crea tablas. Ademas añade 10 tuplas por defecto
        insertarTuplasButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                /*Muestra el dialogo de confirmacion*/
                menuConfirmacion dialog = new menuConfirmacion();
                dialog.pack();
                dialog.setVisible(true);

                /*Si se elige si, el codigo se ejecuta. En caso contrario, no hace nada*/
                if(confirmacion){
                    try{
                        ddsiAPP.BorraryCrearTablas();
                    } catch (SQLException ex) {
                        System.out.println(ex.toString());
                    }
                    actualizarTablas();
                    confirmacion = false;
                }

            }
        });
        actualizarTablasButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                actualizarTablas();
                System.out.println("3-Mostrar contenido de las tablas de la BD");
            }
        });
        darDeAltaPedidoButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    ddsiAPP.pstatement = ddsiAPP.conexion.prepareStatement(ddsiAPP.SQL_INSERT_PEDIDO);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

                pedido dialog = new pedido();
                dialog.pack();
                dialog.setVisible(true);
            }
        });
    }

    private void desconectar() {
        try{
            ddsiAPP.conexion.close();
            System.out.println("4-Conexion cerrada. Hasta pronto!");
        } catch (SQLException ex) {
            System.out.println(ex.toString());
        }
        dispose();
    }

    public static void main(String[] args) throws SQLException {
        ddsiAPP.conectarBD();
        appGUI dialog = new appGUI();
        dialog.pack();
        dialog.setVisible(true);

        System.exit(0);
    }

    String headerStock[] = {"Cproducto", "cantidad"};
    String headerPedido[] = {"Cpedido", "Ccliente", "Fecha_pedido"};
    String headerDetallesPedido[] = {"Cpedido_dp", "Cproducto_dp", "cantidad"};
    private void createUIComponents() {
        //Crear tabla y mostrarla
        model = new DefaultTableModel(0, 2);
        model1 = new DefaultTableModel(0, 3);
        model2 = new DefaultTableModel(0, 3);

        model.setColumnIdentifiers(headerStock);
        model1.setColumnIdentifiers(headerPedido);
        model2.setColumnIdentifiers(headerDetallesPedido);

        tableStock = new JTable(model);
        tablePedido = new JTable(model1);
        tableDetallePedido = new JTable(model2);

        //Muestra el contenido de las tablas de la base de datos
        actualizarTablas();

    }

    static void actualizarTablas(){
        //Mostrar Datos de las tablas
        try{
            //Datos tabla STOCK
            ResultSet rs= ddsiAPP.statement.executeQuery("select * from STOCK");
            model.setRowCount(0);
            while (rs.next()){
                Object[] row= {rs.getInt("cproducto"), rs.getInt("cantidad")};
                model.addRow(row);
            }

            //Datos tabla PEDIDO
            rs = ddsiAPP.statement.executeQuery("select * from PEDIDO");
            model1.setRowCount(0);
            while (rs.next()){
                Object[] row= {rs.getInt("cpedido"), rs.getInt("ccliente"), rs.getDate("fecha_pedido")};
                model1.addRow(row);
            }

            //Datos tabla DETALLES_PEDIDO
            rs = ddsiAPP.statement.executeQuery("select * from DETALLE_PEDIDO");
            model2.setRowCount(0);
            while (rs.next()){
                Object[] row= {rs.getInt("cpedido_dp"), rs.getInt("cproducto_dp"), rs.getInt("cantidad")};
                model2.addRow(row);
            }
        } catch (SQLException ex) {
            System.out.println(ex.toString());
        }


        System.out.println("\nActualizar Tablas");
    }
}
