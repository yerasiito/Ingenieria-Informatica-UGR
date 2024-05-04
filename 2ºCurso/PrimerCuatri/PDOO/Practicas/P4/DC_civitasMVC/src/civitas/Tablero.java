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
    private static final int TAMANIOTABLERO = 20;
    private boolean porSalida;
    private ArrayList<Casilla> casillas;
    
    public Tablero(){
        casillas = new ArrayList<>();
        porSalida = false;
    }
       
    private boolean correcto(int numCasilla){
        boolean esCorrecto = false;
        if(numCasilla > -1 && numCasilla < casillas.size())
            esCorrecto = true;
        
        return esCorrecto;
    }
    
    boolean computarPasoPorSalida (){
        boolean copia = porSalida;
        porSalida = false;
        return copia;
    }
    
    void añadeCasilla(Casilla casilla){
        casillas.add(casilla);
    }
    
    public Casilla getCasilla(int numCasilla){
        if(correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
    }
    
    public ArrayList<Casilla> getCasillas() {
        return casillas;
    }
    
    int nuevaPosicion (int actual, int tirada){
        int nueva = (actual+tirada)%TAMANIOTABLERO;
        if(nueva != actual+tirada){
            porSalida = true;
        }
        return nueva;
    }
}
