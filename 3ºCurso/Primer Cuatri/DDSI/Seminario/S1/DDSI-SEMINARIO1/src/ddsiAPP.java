/*
 * Archivo Principal
 */

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.*;
import java.sql.Date;
import java.text.ParseException;
import java.util.*;


public class ddsiAPP {

    static String url = "jdbc:oracle:thin:@//oracle0.ugr.es:1521/practbd.oracle0.ugr.es";

    //Nombre usuario y password
    static String usuario = ""; //Por defecto
    static String password = ""; //Por defecto

    //Guardar los nombres de las tablas en tiempo de ejecución
    static ArrayList<String> table_names = new ArrayList<String>();
    //Booleano de error
    static boolean error_encontrado = false;
    //Booleano al menos un detalle

    static boolean hay_un_detalle = false;
    static boolean quit = false;

    static boolean errorStock = false, errorNoProduct = false;
    static Connection conexion;
    static Statement statement;
    static PreparedStatement pstatement;

    static Savepoint save1, save2, save3;

    /*
    Strings para guardar la información de acciones recurrentes y de las tablas por defecto.
    */

    static final String crearTablaStock = "create table STOCK(\r\n" + "Cproducto NUMBER(5,0) NOT NULL,\r\n" +
            "cantidad NUMBER(5,0) NOT NULL,\r\n" + "PRIMARY KEY (Cproducto)\r\n" + ")";
    static final String crearTablaPedido = "create table Pedido(\r\n" + "Cpedido NUMBER(5,0) NOT NULL,\r\n" +
            "Ccliente NUMBER(5,0) UNIQUE NOT NULL,\r\n" + "Fecha_pedido DATE NOT NULL,\r\n" + "PRIMARY KEY (Cpedido)\r\n" +
            ")";
    static final String crearTablaDetalle_Pedido = "create table DETALLE_PEDIDO(\r\n" + "Cpedido_DP NUMBER(5,0) NOT NULL,\r\n" +
            "Cproducto_DP NUMBER(5,0) NOT NULL,\r\n" + "cantidad NUMBER NOT NULL,\r\n" +
            "PRIMARY KEY (Cpedido_DP, Cproducto_DP),\r\n" + "FOREIGN KEY (Cproducto_DP) REFERENCES Stock(Cproducto),\r\n" +
            "FOREIGN KEY (Cpedido_DP) REFERENCES Pedido(Cpedido)\r\n" + ")";
    /*
    Función para insertar las tuplas por defecto en la Tabla Pedido
    */
    static void insertarTuplas(){
        try {
            System.out.println("Insertando tuplas...");
            /*STOCK*/
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10000, 20000)"); //1
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10001, 20001)"); //2
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10002, 20002)"); //3
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10003, 20003)"); //4
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10004, 20004)"); //5
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10005, 20005)"); //6
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10006, 20006)"); //7
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10007, 20007)"); //8
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10008, 20008)"); //9
            statement.executeUpdate("INSERT INTO STOCK " + "VALUES (10009, 20009)"); //10
        } catch (SQLException ex) {
            System.out.println(ex.toString());
        }

        System.out.println("Tuplas insertadas con éxito");
        System.out.println("***********************************");
    }
    /*
    Función para obtener la información del fichero passwd ( Usuario y contraseña para acceder a la BD de la ETSIIT)
     */
    public static void getProperties(){
        Properties properties = new Properties();
        try {
            Path path = Paths.get("passwd.properties");
            String util = path.toAbsolutePath().toString();
            properties.load(new FileInputStream(util));
            usuario = properties.get("db.user").toString();
            password = properties.get("db.passwd").toString();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static void conectarBD() throws SQLException {
        getProperties();
        conexion = DriverManager.getConnection(url,usuario,password);
        statement = conexion.createStatement();
        System.out.println("Conexión con la BD realizada con éxito");
    }
    public static void main(String[] args) {
        //Obtiene el usuario y contraseña del fichero passwd.properties
        try {

            Class.forName("oracle.jdbc.driver.OracleDriver");
            conectarBD();
             /*
             Código del menu principal
             */
            System.out.println(" Este es el menu principal de la Interfaz: \n" +
                    " Seleccione una de las siguientes opciones para operar en la Base de Datos \n" +
                    " 1. Borrado de tablas y vuelta a la configuración por defecto\n"+
                    " 2. Dar de alta un nuevo pedido\n"+
                    " 3. Mostrar el contenido de todas las tablas de la DB\n"+
                    " Pulse 0 para cerrar la conexión con la DB y cerrar esta interfaz\n"
            );
            Scanner leer = new Scanner(System.in);
            int num = leer.nextInt();
            while( num != 0 ){
                // Si se quiere cerrar la conexión se marcará la opción 0 saliendo del bucle
                menu(num);
                num = leer.nextInt();
            }
            conexion.close();
            System.out.println( "Se ha cerrado la sesión. ¡Hasta pronto!");
        } catch (SQLException | ClassNotFoundException ex) {
            System.out.println(ex.toString());
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }

    }

    /*
      Función menu principal de la interfaz
    */
    static void menu(int num) throws SQLException, ParseException {
        switch(num) {
            //Opción 1: Borrado de tablas y creación/inserción
            case 1:
                Scanner in = new Scanner(System.in);
                System.out.println("¿Está seguro de querer volver a la configuración por defecto?\n" + "Esta acción es irreversible, perderá todas las tablas y tuplas que haya podido crear.\n"
                        + "Pulse S para Sí ó cualquier otra tecla para No.\n");
                char confirm = in.next().charAt(0);
                if (confirm == 'S' | confirm == 's') {
                    BorraryCrearTablas();
                } else {
                    System.out.println("Operación cancelada\n");
                }
                break;
            //Opción 2: Dar de alta nuevo pedido
            case 2:
                conexion.setAutoCommit(false);
                save1 = conexion.setSavepoint();
                pstatement = conexion.prepareStatement(SQL_INSERT_PEDIDO);
                int cpedido = DarAltaPedido(pstatement);

                Scanner read = new Scanner(System.in);
                save2 = conexion.setSavepoint();
                quit = false;
                do {
                    System.out.println("\n\n Este es el submenu de la interfaz de pedidos: \n" +
                            " Seleccione una de las siguientes opciones para operar en la Base de Datos \n" +
                            " 1. Añadir detalle de producto\n" +
                            " 2. Eliminar todos los detalles del producto\n" +
                            " 3. Cancelar pedido\n" +
                            " 4. Finalizar pedido\n"
                    );
                    int opt = read.nextInt();
                    switch (opt) {
                        // 1: Añadir detalle de producto
                        case 1:
                            aniadirDetalleProducto(cpedido);
                            break;
                        // 2: Eliminar todos los detalles del producto
                        case 2:
                            conexion.rollback(save2);
                            hay_un_detalle = false;
                            MostrarContenido();
                            break;
                        // 3: Cancelar pedido
                        case 3:
                            conexion.rollback(save1);
                            quit = true;
                            hay_un_detalle = false;

                            MostrarContenido();
                            System.out.println("***********************************");
                            System.out.println("Pedido cancelado con éxito");
                            break;
                        // 4: Finalizar pedido
                        case 4:
                            if(hay_un_detalle) {
                                finalizarPedido();
                                quit = true;
                            }
                            else{
                                System.out.println("No existe ningún detalle de este pedido, introduce alguno o cancela el pedido.");
                            }
                            break;
                        default:
                            System.out.println("***********************************");
                            System.out.println("El número introducido no es correcto");
                            break;
                    }
                } while (!quit);
                break;

            //Opción 3: Mostrar contenido de las tablas
            case 3:
                MostrarContenido();
                break;
            //Introducir un número no válido
            default:
                System.out.println("El número introducido no es correcto");
                break;
        }
    }

    static void finalizarPedido() throws SQLException {
        conexion.commit();
        System.out.println("***********************************");
        System.out.println("Pedido finalizado con éxito");
        hay_un_detalle = false;
    }
    static void aniadirDetalleProducto(int cpedido) throws SQLException {
        pstatement = conexion.prepareStatement(SQL_INSERT_DETALLES_PEDIDO);
        AddDetallesProducto(cpedido);
        pstatement.close();

        MostrarContenido();
        if(!error_encontrado) {
            conexion.commit();
            save3 = conexion.setSavepoint();
            System.out.println("Detalles del pedido añadidos con éxito");
            hay_un_detalle = true;
        }
        error_encontrado = false;
        System.out.println("***********************************");
    }

    static void crearTablas(){
        try{
            System.out.println("Tabla: STOCK creada");
            statement.executeUpdate(crearTablaStock);
            System.out.println("Tabla: PEDIDO creada");
            statement.executeUpdate(crearTablaPedido);
            System.out.println("Tabla: DETALLE_PEDIDO creada");
            statement.executeUpdate(crearTablaDetalle_Pedido);
        }catch (SQLException e) {
            e.printStackTrace();
        }
        System.out.println("***********************************");
    }
    static void borrarTablas(){
        try{
            while(table_names.size()>0){
                statement.executeUpdate("DROP TABLE " + table_names.get(0));
                String eliminado = table_names.remove(0);
                System.out.println("Tabla " + eliminado + " eliminada.");
            }
        }catch (SQLException e) {
            e.printStackTrace();
        }
        System.out.println("***********************************");
    }
    /*
    Función para borrar todas las tablas de la BD, crear las por defecto y insertar 10 tuplas a la tabla STOCK
     */
    static void BorraryCrearTablas() throws SQLException {
        //1. Consultar todas las tablas de la DB
        consultarTablas();
        //2. Borrar una a una
        borrarTablas();
        //3. Crear tablas de nuevo por defecto
        crearTablas();
        //4. Insertar 10 tuplas en STOCK
        insertarTuplas();

        System.out.println("1. Borrado de tablas y vuelta a la configuración por defecto: COMPLETADO");
    }

    static void consultarTablas(){
        System.out.println("***********************************");
        try{
            DatabaseMetaData metaData = conexion.getMetaData();
            ResultSet tablas = metaData.getTables(null, conexion.getSchema(), null, null);
            while(tablas.next()){
                table_names.add(tablas.getString(3));
            }
            System.out.println("Tablas leidas:" + table_names.size());
        }catch (SQLException e) {
            e.printStackTrace();
        }
    }
    /*
    Función para mostrar el contenido de las tablas por defecto de la DB
     */
    static void  MostrarContenido() throws SQLException {
        //Mostrar para la tabla STOCK
        ResultSet rs= statement.executeQuery("select * from STOCK");
        System.out.println("***** TABLA STOCK *****");
        System.out.println("Cproducto\tCantidad");
        while (rs.next()){
            int cod = rs.getInt("cproducto");
            int cant = rs.getInt("cantidad");
            System.out.println(cod + "\t\t" + cant);
        }
        //Mostrar para la tabla PEDIDO
        rs= statement.executeQuery("select * from PEDIDO");
        System.out.println("***** TABLA PEDIDO *****");
        System.out.println("Cpedido\tCcliente\tFecha_pedido");
        while (rs.next()){
            int cod = rs.getInt("cpedido");
            int cant = rs.getInt("ccliente");
            Date fecha = rs.getDate("fecha_pedido");
            System.out.println(cod + "\t\t" + cant + "\t\t" + fecha);
        }
        //Mostrar para la tabla DETALLE_PEDIDO
        rs= statement.executeQuery("select * from DETALLE_PEDIDO");
        System.out.println("***** TABLA DETALLE_PEDIDO *****");
        System.out.println("Cpedido_dp\tCproducto_dp\tCantidad");
        while (rs.next()){
            int cod = rs.getInt("cpedido_dp");
            int cod_p = rs.getInt("cproducto_dp");
            int cant = rs.getInt("cantidad");
            System.out.println(cod + "\t\t" + cod_p + "\t\t" + cant);
        }
    }

    /*
    Función para dar de alta un pedido.
    Se deben insertar: código de pedido, código de cliente y fecha de pedido
     */
    static int DarAltaPedido(PreparedStatement pstatement) throws SQLException {
        System.out.println("Introduzca los siguientes datos del pedido:\n" + "- Código de pedido (cadena de 5 dígitos)\n" +
                "- Código de cliente (cadena de 5 dígitos)\n" + "- Fecha de pedido (formato yyyy-MM-dd)\n");

        Scanner scn = new Scanner(System.in);
        System.out.println("Código de pedido: ");
        int codped = scn.nextInt();
        System.out.println("Código de cliente: ");
        int codcli = scn.nextInt();
        System.out.println("Fecha de pedido (yyyy-MM-dd): ");
        String fechaS = scn.next();

        addPedidoToDB(codped, codcli, fechaS);

        System.out.println("Pedido nuevo insertado con éxito");
        System.out.println("***********************************");

        return codped;
    }

    static void addPedidoToDB(int codped, int codcli, String fechaS) throws SQLException {
        Date fechaD = Date.valueOf(fechaS);
        try {
            pstatement.setInt(1,codped);
            pstatement.setInt(2,codcli);
            pstatement.setDate(3, fechaD);
            pstatement.execute();
        } catch (SQLException ex) {
            conexion.rollback();
            System.out.println(ex.toString());
        }
    }

    /*
   Función para definir una sentencia preparada que inserte las tuplas de pedidos
    */
    static final String SQL_INSERT_PEDIDO = "INSERT INTO PEDIDO (Cpedido, Ccliente, Fecha_pedido) VALUES (?,?,?)";

    /*
   Función para definir una sentencia preparada que inserte las tuplas de detalle de pedido
    */
    static final String SQL_INSERT_DETALLES_PEDIDO = "INSERT INTO DETALLE_PEDIDO (Cpedido_DP, Cproducto_DP, cantidad) VALUES (?,?,?)";

    /*
   Función para añadir detalles de un pedido.
   Se deben insertar: código de producto y cantidad de pedido.
    */
    static void AddDetallesProducto(int codped) throws SQLException {
        System.out.println("Introduzca los detalles del pedido:\n" + "- Código de producto (cadena de 5 dígitos)\n" +
                "- Cantidad del producto a pedir\n");

        Scanner sc = new Scanner(System.in);
        System.out.println("Código del producto: ");
        int codpro = sc.nextInt();
        System.out.println("Cantidad a pedir: ");
        int cantped = sc.nextInt();
        boolean transacc_posible = false;
        ResultSet rs= statement.executeQuery("select count(*) from STOCK where Cproducto= '"+codpro+"'");

        transacc_posible = existeProducto(rs, codpro, cantped);
        if (transacc_posible) {
            addDetalle(codped, codpro, cantped);
            save2 = conexion.setSavepoint();
        }
    }
    static boolean existeProducto(ResultSet rs, int codpro, int cantped) throws SQLException {
        boolean transacc_posible = false;
        int np = 0;
        if (rs.next()){
            np = rs.getInt(1);
        }
        if (np > 0) {
            rs = statement.executeQuery("select * from STOCK where Cproducto= '"+codpro+"'");
            rs.next();
            int cantstock = rs.getInt("cantidad");
            if (cantstock >= cantped){
                transacc_posible = true;
                statement.executeUpdate("update STOCK set cantidad = cantidad - '"+cantped+"' where Cproducto= '"+codpro+"'");
            }else{
                System.out.println("No hay suficientes unidades de dicho producto en el Stock");
                errorStock = true;
                error_encontrado = true;
                transacc_posible = false;
                conexion.rollback(save3);
            }
        }else{
            System.out.println("El producto solicitado no está disponible");
            errorNoProduct = true;
            error_encontrado = true;
            transacc_posible = false;
            conexion.rollback(save3);
        }
        return transacc_posible;
    }

    static void addDetalle(int codped, int  codpro, int cantped) throws SQLException {
        try {
            pstatement.setInt(1, codped);
            pstatement.setInt(2, codpro);
            pstatement.setInt(3, cantped);
            pstatement.execute();
        } catch (SQLException ex){
            conexion.rollback();
            System.out.println(ex.toString());
        }
    }
}
