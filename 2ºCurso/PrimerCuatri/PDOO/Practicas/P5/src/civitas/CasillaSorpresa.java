/**
 * @file CasillaSorpresa.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Hija de Casilla que gestiona las Casillas sorpresas del @c Tablero. 
 * Las Casillas de Sorpresa pertenecen a esta clase.
 */
public class CasillaSorpresa extends Casilla{
    private MazoSorpresas mazo;
    public CasillaSorpresa() {
        super(null);

    }
    
    CasillaSorpresa(String nombre, MazoSorpresas mazo){
        super(nombre);
        this.mazo = mazo;
    }
    
    @Override
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        super.recibeJugador(iactual, todos);
        Sorpresa sorpresa = mazo.siguiente();
        sorpresa.aplicarAJugador(iactual, todos);
    }
    
    @Override
    public String toString(){
        String cadena = "una casilla Sorpresa";
        
        return cadena;
    }
}
