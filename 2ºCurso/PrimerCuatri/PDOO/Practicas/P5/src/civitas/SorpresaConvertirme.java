/**
 * @file SorpresaConvertirme.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Hija de Sorpresa que gestiona la Sorpresa de conversion del
 * jugador en Especulador.
 */
public class SorpresaConvertirme extends Sorpresa{

    public SorpresaConvertirme(String nombre) {
        super(nombre, 0);
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        JugadorEspeculador jEsp = todos.get(actual).convertir();
        todos.set(actual, jEsp); //mete el jugador especulador en su lugar
        
        String cambios = "El jugador convertido paga la mitad y podrá construir " 
                + jEsp.getFactorEspeculador() + " veces más propiedades.";
        Diario.getInstance().ocurreEvento(cambios);  
    }
    
    @Override
    void informe(int actual, ArrayList<Jugador> todos){
        String evento = "¡El jugador " + todos.get(actual).getNombre() +
                " se le ha convertido en Especulador! " + toString();
        Diario.getInstance().ocurreEvento(evento);
    }
    
}
