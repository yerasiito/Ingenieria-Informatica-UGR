/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;
import java.util.Random;

/**
 *
 * @author ylope
 */
public class Dado {
    static final private int CARASDADO = 6;
    final private Random random = new Random();
    private int ultimoResultado;
    private boolean debug;
    static final private Dado instance = new Dado();

    private Dado(){
        ultimoResultado = 0;
        debug = false;
    }
    
    static Dado getInstance(){
        return instance;
    }

    int tirar(){
        int resultado = 1;
        if(!debug){
            resultado = random.nextInt(CARASDADO)+1;
        }
        ultimoResultado = resultado; 
        return resultado;
    }
    
    int quienEmpieza(int n){
        return random.nextInt(n);
    }
    void setDebug(boolean d){
        debug = d;
        Diario.getInstance().ocurreEvento("El Dado ha cambiado debug a " + debug);
    }
    
    int getUltimoResultado(){
        return ultimoResultado;
    }
}