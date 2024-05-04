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
    
    private void aplicarAJugador_pagarCobrar(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor);
    }
    
    private void aplicarAJugador_porCasaHotel(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor*todos.get(actual).CantidadCasasHoteles());
    }
    
    private void informe(int actual, ArrayList<Jugador> todos){
        String evento = "El jugador " + todos.get(actual).getNombre() +
                " se le ha aplicado una SORPRESA: " + toString();
        Diario.getInstance().ocurreEvento(evento);
    }
    
    @Override
    public String toString(){
        return texto;
    }
}
