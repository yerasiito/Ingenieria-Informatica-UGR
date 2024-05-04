/**
 * @file Respuesta.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package controladorCivitas;

import java.util.ArrayList;

/**
 * @brief Enumerado Respuesta que gestiona las decisiones del usuario.
 * Utilizada por el @c Controlador y la @c vistaTextual
 */
public enum Respuesta{
    NO, SI;
    
    /**
     * @brief Convierte el enumerado en ArrayList String necesario para el menú
     * de @¢ VistaTextual
     * @return el enumerado en forma de ArrayList de String
     */
    public static ArrayList<String> respuestas(){
        /*ArrayList<String> respuestas = new ArrayList<String> (){{
            for(int i = 0; i < Respuesta.values().length; i++)
                add(Respuesta.values()[i].toString());
        }};*/
        ArrayList<String> respuestas = new ArrayList<String> (){{
            for (Respuesta value : Respuesta.values()) {
                add(value.toString());
            }
        }};
        
        return respuestas;
    }
}