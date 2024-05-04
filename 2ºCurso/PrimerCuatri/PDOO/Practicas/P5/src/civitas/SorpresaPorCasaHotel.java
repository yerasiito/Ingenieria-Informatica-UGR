/**
 * @file SorpresaPorCasaHotel.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Hija de Sorpresa que gestiona la Sorpresa de PORCASAHOTEL
 */
public class SorpresaPorCasaHotel extends Sorpresa {

    public SorpresaPorCasaHotel(String texto, int valor) {
        super(texto, valor);
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor*todos.get(actual).CantidadCasasHoteles());
    }
    
    @Override
    void informe(int actual, ArrayList<Jugador> todos){
        String evento = "El jugador " + todos.get(actual).getNombre() +
                " se le ha aplicado una Sorpresa de PORCASAHOTEL: " + toString();
        Diario.getInstance().ocurreEvento(evento);
    }
    
    @Override
    public String toString(){
        return super.toString() + " por propiedad";
    }
}
