/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;
import java.util.Random;

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
    
    int getUltimoResultado(){
        return ultimoResultado;
    }
    
    int quienEmpieza(int n){
        return random.nextInt(n);
    }
     
    public void setDebug(boolean d){
        debug = d;
        Diario.getInstance().ocurreEvento("El Dado ha cambiado debug a " + debug);
    }
        
    int tirar(){
        int resultado = VALORESDEBUG;
        if(!debug)
            resultado = random.nextInt(VALORESDADO)+1;
        
        ultimoResultado = resultado; 
        return resultado;
    }
}