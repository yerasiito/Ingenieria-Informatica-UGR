/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejercicios;

/**
 *
 * @author yerasito
 */
public class CasillaCalle extends Casilla{
    private int numCasas;
    
    CasillaCalle(String nombre, int numCasas){
        super(nombre);  //Obligatorio en la primera linea
        
        this.numCasas = numCasas;
    }

    public int getNumCasas() {
        return numCasas;
    }
    /*
    @Override
    //Anulando al padre
    boolean recibeJugador(){
        System.out.println("Soy una casilla calle y he recibido un jugador");
        return true;
    }*/
    
    //Reutilizando codigo del padre
    @Override
    boolean recibeJugador(){
        if(super.recibeJugador()){
            System.out.print(" y ademas soy una casilla calle\n");
            return true;
        }
        return false;
    }
    
    void construirCasa(){
        numCasas++;
        System.out.println("La calle " + getNombre() + " ha construido y tiene "
            + numCasas + " casas");
    }
}
