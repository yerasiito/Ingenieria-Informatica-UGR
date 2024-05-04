/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejercicios;

import java.util.ArrayList;

/**
 *
 * @author yerasito
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //Ejercicios 1,2,3
        Casilla casilla = new Casilla("Nueva");
        CasillaCalle calle = new CasillaCalle("Real",10);
        
        casilla.recibeJugador();
        calle.recibeJugador();
        
        //Ejercicio 4
        //casilla.construirCasas();
        calle.construirCasa();
        
        //Ejercicio 5
        ArrayList<Casilla> tablero = new ArrayList();
        tablero.add(casilla);
        tablero.add(calle);
        
        
        //tablero.get(0).construirCasas(); //Da error
        ((CasillaCalle)tablero.get(1)).construirCasa();
        
        /*
        CasillaCalle casilla1 = new CasillaCalle("casilla1",0);
        Casilla casilla2 = new Casilla("casilla2");
        casilla2 = (CasillaCalle)casilla1;
        
        casilla1.recibeJugador();
        casilla2.recibeJugador();
    
        casilla1.construirCasa();
        ((CasillaCalle)casilla2).construirCasa();
        */
    }
    
}
