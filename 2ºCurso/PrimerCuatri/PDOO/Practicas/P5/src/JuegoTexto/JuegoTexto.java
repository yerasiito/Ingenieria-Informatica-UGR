/**
 * @file JuegoTexto.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package JuegoTexto;

import controladorCivitas.Controlador;
import civitas.CivitasJuego;

import java.util.ArrayList;
import java.util.Scanner;
import GUI.VistaTextual;

/**
 * @brief Clase Principal donde se juega al Civitas en Modo Texto
 */
public class JuegoTexto {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        final int MINJUGADORES = 2, MAXJUGADORES = 4;
        
        Scanner in = new Scanner (System.in); //El objeto que leerá el teclado
        
        //Leemos los jugadores
        ArrayList<String> jugadores = new ArrayList<String>(){
            {
                System.out.println("¿Cuantos jugadores van a jugar?");
                int numJugadores = in.nextInt();
                while(numJugadores > MAXJUGADORES || numJugadores < MINJUGADORES){
                    System.out.println("¿Cuantos jugadores van a jugar?");        
                    numJugadores = in.nextInt();    
                }
                int contador = 0;
                System.out.println("Introduce el nombre de los jugadores:");
                while(contador < numJugadores){
                    add(in.next());
                    contador++;
                }
            }
        };
        
        CivitasJuego juego = new CivitasJuego(jugadores, false);
        VistaTextual vista = new VistaTextual(juego);
        //Controlador controlador = new Controlador(juego,vista);
        //controlador.juega();
    }
}
