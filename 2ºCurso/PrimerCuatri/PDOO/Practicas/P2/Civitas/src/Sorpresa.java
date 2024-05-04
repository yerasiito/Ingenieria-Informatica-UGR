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
public class Sorpresa {
    private String texto;
    private int valor;
    private TipoSorpresa tipo;

    Sorpresa(TipoSorpresa tipo, String texto, int valor) {
        this.texto = texto;
        this.valor = valor;
        this.tipo = tipo; 
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        if(tipo == TipoSorpresa.PAGARCOBRAR)
            aplicarAJugador_pagarCobrar(actual, todos);
        else if(tipo == TipoSorpresa.PORCASAHOTEL)
            aplicarAJugador_porCasaHotel(actual, todos);
    }
    
    void aplicarAJugador_pagarCobrar(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor);
    }
    
    void aplicarAJugador_porCasaHotel(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor*todos.get(actual).CantidadCasasHoteles());
    }
    
    void informe(int actual, ArrayList<Jugador> todos){
        String evento = "El jugador " + todos.get(actual).getNombre() +
                " se le ha aplicado una SORPRESA" + toString();
        Diario.getInstance().ocurreEvento(evento);
    }
    
    public String toString(){
        return texto;
    }
}
