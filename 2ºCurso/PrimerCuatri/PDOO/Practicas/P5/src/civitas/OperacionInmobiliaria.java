/**
 * @file OperacionInmobiliaria.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;
/**
 * @brief Enumerado OperacionInmobiliaria que gestiona las operaciones de las calles.
 * Utilizado por @c Controlador y @c VistaTextual
 */
public enum OperacionInmobiliaria{
    CONSTRUIR_CASA, CONSTRUIR_HOTEL, TERMINAR;
    
    /**
     * @brief Convierte el enumerado en ArrayList de String necesario para el menú
     * de @¢ VistaTextual
     * @return el enumerado en forma de ArrayList de String
     */
    public static ArrayList<String> operaciones(){
        /*ArrayList<String> operaciones = new ArrayList<String> (){{
            for(int i = 0; i < OperacionInmobiliaria.values().length; i++)
                add(OperacionInmobiliaria.values()[i].toString());
        }};*/
        
        ArrayList<String> operaciones = new ArrayList<String> (){{
            for (OperacionInmobiliaria value : OperacionInmobiliaria.values()) {
                add(value.toString() + ",");
            }
        }};
        return operaciones;
    }
    
    public static OperacionInmobiliaria eleccion(int opcion){
        OperacionInmobiliaria eleccion = null;
        switch(opcion){
            case 0:
                eleccion = OperacionInmobiliaria.CONSTRUIR_CASA;
                break;
            case 1:
                eleccion = OperacionInmobiliaria.CONSTRUIR_HOTEL;
                break;
            case 2:
                eleccion = OperacionInmobiliaria.TERMINAR;
        }
        return eleccion;
    }
}
