/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

public class Casilla {
    private String nombre;
        
    //DESCANSO
    Casilla(String nombre){
        this.nombre = nombre;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    void informe(int actual, ArrayList<Jugador> todos){
        String informe = "El jugador " + todos.get(actual).getNombre() + 
                " ha caido en la " + toString();
        Diario.getInstance().ocurreEvento(informe);
    }
    
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        informe(iactual, todos);
    }
    
    @Override
    public String toString(){
        return nombre;
    }
}
