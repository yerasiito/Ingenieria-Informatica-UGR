/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;
/**
 *
 * @author ylope
 */
public class Tablero {
    static final public int TAMANIOTABLERO = 20;
    final private ArrayList<Casilla> casillas;
    private boolean porSalida;
    
    Tablero(){
        casillas = new ArrayList<>();
        porSalida = false;
    }
    
    public boolean getPasoPorSalida(){
        return porSalida;
    }
    
    private boolean correcto(int numCasilla){
        boolean esCorrecto = false;
        if(numCasilla > -1 && numCasilla < casillas.size())
            esCorrecto = true;
        
        return esCorrecto;
    }
    
    boolean computarPasoPorSalida (){
        boolean salida = porSalida;
        porSalida = false;
        return salida;
    }
    
    void aniadeCasilla(Casilla casilla){
        casillas.add(casilla);
    }
    
    Casilla getCasilla(int numCasilla){
        if(correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
    }
    
    int nuevaPosicion (int actual, int tirada){
        int nueva = (actual+tirada)%TAMANIOTABLERO;
        if(nueva != actual+tirada){
            porSalida = true;
        }
        return nueva;
    }
}
