/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author yerasito
 */
public class CasillaSorpresa extends Casilla{
    private MazoSorpresas mazo;
    public CasillaSorpresa() {
        super(null);

    }
    
    CasillaSorpresa(String nombre, MazoSorpresas mazo){
        super(nombre);
        this.mazo = mazo;
    }
    
    @Override
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        Sorpresa sorpresa = mazo.siguiente();
        informe(iactual, todos);
        sorpresa.aplicarAJugador(iactual, todos);
        super.recibeJugador(iactual, todos);
    }
    
    @Override
    public String toString(){
        String cadena = "Casilla Sopresa";
        
        return cadena;
    }
}
