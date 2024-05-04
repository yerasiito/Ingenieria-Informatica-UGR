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
public class Casilla {
    private String nombre;

    public Casilla(String nombre) {
        this.nombre = nombre;
    }

    public String getNombre() {
        return nombre;
    }
    
    boolean recibeJugador(){
        System.out.print("\nHe recibido un jugador");
        return true;
    }
}
