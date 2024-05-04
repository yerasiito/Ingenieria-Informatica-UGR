/**
 * @file Dado.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;
import java.util.Random;

/**
 * @brief Clase Dado que gestiona las posiciones del jugador en el tablero.
 * Devuelve numeros pseudoaleatorios.
 * Es un singleton por lo que no puede ser instanciada(No hay constructor)
 * Igualmente se pueden crear objetos dado para no escribir dado.getInstance()
 * Puede ponerse en modo debug para que siempre tire 1.
 */
public class Dado {
    private static final int VALORESDADO = 6;
    private static final int VALORESDEBUG = 1;
    
    private final Random random;
    private int ultimoResultado;
    private boolean debug;
    private static final Dado instance = new Dado();

    private Dado(){
        random = new Random();
        ultimoResultado = 0;
        debug = false;
    }
    
    public static Dado getInstance(){
        return instance;
    }
    
    public int getUltimoResultado(){
        return ultimoResultado;
    }
    
    public boolean getDebug(){
        return debug;
    }
    
    int quienEmpieza(int n){
        return random.nextInt(n);
    }
     
    public void setDebug(boolean d){
        debug = d;
        Diario.getInstance().ocurreEvento("El Dado ha cambiado debug a " + debug + ".");
    }
        
    int tirar(){
        int resultado = VALORESDEBUG;
        if(!debug)
            resultado = random.nextInt(VALORESDADO)+1;
        
        ultimoResultado = resultado; 
        return resultado;
    }
}