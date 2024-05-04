/**
 * @file Casilla.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Padre Casilla por las que está formada @c Tablero. Los Descansos
 * pertenecen a esta clase.
 */
public class Casilla {
    private final String nombre;
        
    //DESCANSO
    Casilla(String nombre){
        this.nombre = nombre;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    void informe(int actual, ArrayList<Jugador> todos){
        String informe = "El jugador " + todos.get(actual).getNombre() + 
                " ha caido en " + nombre;
        Diario.getInstance().ocurreEvento(informe);
    }
    
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        informe(iactual, todos);
    }
    
    @Override
    public String toString(){
        return nombre;
    }
}
