/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author ylope
 */
public class Civitas {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ArrayList<String> jugadores = new ArrayList<String>(){
            {
                add("Juan");
                add("Maria");
                add("Alberto");
                add("Eva");
            }
        };
        
        Dado.getInstance().getUltimoResultado();
        CivitasJuego juego = new CivitasJuego(jugadores, false);
        
        System.out.println("\nTablero");
        for(int i = 0; i < juego.getTablero().getCasillas().size(); i++)
            System.out.println("Casilla " + i + ": " + juego.getTablero().getCasilla(i).toString());
        
        System.out.println("\nCartas Sorpresa");
        for(int i = 0; i < juego.getMazo().getMazoSorpresas().size(); i++)
            System.out.println("Sorpresa " + i + ": " + juego.getMazo().getMazoSorpresas().get(i).toString());
        
        System.out.println("\nRanking jugadores:\n" + juego.Ranking().toString());
    }
}
