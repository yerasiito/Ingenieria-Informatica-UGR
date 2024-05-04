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
    private boolean porSalida;
    private ArrayList<Casilla> casillas;
    
    public Tablero(){
        casillas = new ArrayList<>();
        porSalida = false;
    }
    
    public boolean getPasoPorSalida(){
        return porSalida;
    }
    
    public boolean correcto(int numCasilla){
        boolean esCorrecto = false;
        if(numCasilla > -1 && numCasilla < casillas.size())
            esCorrecto = true;
        
        return esCorrecto;
    }
    
    public boolean computarPasoPorSalida (){
        boolean copiaSalida = porSalida;
        porSalida = false;
        return copiaSalida;
    }
    
    public void aniadeCasilla(Casilla casilla){
        casillas.add(casilla);
    }

    public ArrayList<Casilla> getCasillas() {
        return casillas;
    }
    
    public Casilla getCasilla(int numCasilla){
        if(correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
    }
    
    public int nuevaPosicion (int actual, int tirada){
        int nueva = (actual+tirada)%CivitasJuego.TAMANIOTABLERO;
        if(nueva != actual+tirada){
            porSalida = true;
        }
        return nueva;
    }
}
