/**
 * @file Sorpresa.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase ABSTRACTA sorpresa que hace de base para los 3 tipos de sorpresa.
 * Hay 3 tipos de sorpresas hasta la fecha:
 *  -PAGARCOBRAR: paga o cobra una cantidad fija
 *  -PORCASAHOTEL: paga o cobra una cantidad en funcion de sus propiedades
 *  -CONVERTIRME: convierte un jugador en especulador
 */
public abstract class Sorpresa {
    final private String texto;
    final int valor;

    Sorpresa(String texto, int valor) {
        this.texto = texto;
        this.valor = valor;
    }
    
    abstract void aplicarAJugador(int actual, ArrayList<Jugador> todos);
    
    abstract void informe(int actual, ArrayList<Jugador> todos);
    
    @Override
    public String toString(){
        if(valor > 0){
            return texto + " Ganas " + valor + "€";
        }
        else if(valor < 0)
            return texto + " Pierdes " + valor + "€";
        else
            return texto;
    }
}
