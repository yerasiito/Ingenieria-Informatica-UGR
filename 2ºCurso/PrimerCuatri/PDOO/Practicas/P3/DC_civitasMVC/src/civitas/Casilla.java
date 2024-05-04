/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

public class Casilla {
    
    static final private float FACTORALQUILERCALLE = 1.0f;
    static final private float FACTORALQUILERCASA = 1.0f;
    static final private float FACTORALQUILERHOTEL = 4.0f;

    private String nombre;
    private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;
    private TipoCasilla tipo;
    private MazoSorpresas mazo;
    private Jugador propietario;

    private void init(){
        nombre = "";
        precioCompra = 0;
        precioEdificar = 0;
        precioBaseAlquiler = 0;
        numCasas = 0;
        numHoteles = 0;
        tipo = null;
        mazo = null;
        propietario = null;
    }
        
    //DESCANSO
    Casilla(TipoCasilla tipo, String nombre){
        init();
        this.tipo = tipo;
        this.nombre = nombre;
    }
    
    //CALLE
    Casilla(TipoCasilla tipo, String titulo, float precioCompra, float precioEdificar, float precioBaseAlquiler){
        init();
        this.tipo = tipo;
        nombre = titulo;
        this.precioCompra = precioCompra;
        this.precioEdificar = precioEdificar;
        this.precioBaseAlquiler = precioBaseAlquiler;
    }
    
    //SORPRESA
    Casilla(TipoCasilla tipo, String nombre, MazoSorpresas mazo){
        init();
        this.tipo = tipo;
        this.nombre = nombre;
        this.mazo = mazo;
        
    }
    
    public String getNombre(){
        return nombre;
    }
    int getNumCasas() {
        return numCasas;
    }

    int getNumHoteles() {
        return numHoteles;
    }
    
    float getPrecioAlquilerCompleto(){
        return precioBaseAlquiler* (FACTORALQUILERCALLE + numCasas*FACTORALQUILERCASA + numHoteles*FACTORALQUILERHOTEL);
    }
    
    float getPrecioCompra() {
        return precioCompra;
    }

    float getPrecioEdificar() {
        return precioEdificar;
    }

    public static float getFACTORALQUILERCALLE() {
        return FACTORALQUILERCALLE;
    }

    public static float getFACTORALQUILERCASA() {
        return FACTORALQUILERCASA;
    }

    public static float getFACTORALQUILERHOTEL() {
        return FACTORALQUILERHOTEL;
    }
    
    public int cantidadCasasHoteles(){
        return numCasas + numHoteles;
    }
    
    void informe(int actual, ArrayList<Jugador> todos){
        String informe = "El jugador " + todos.get(actual).getNombre() + 
                " ha caido en la " + toString();
        Diario.getInstance().ocurreEvento(informe);
    }

    boolean comprar(Jugador jugador){
        boolean puedeComprar = jugador.puedeComprarCasilla();
        if(puedeComprar){
            jugador.paga(precioCompra);
            propietario = jugador;
        }
        
        return puedeComprar;
    }
    
    boolean construirCasa(Jugador jugador){
         if(jugador.paga(precioEdificar)) numCasas++;
        return true;
    }
    
    boolean construirHotel(Jugador jugador){
        if(jugador.paga(precioEdificar*FACTORALQUILERHOTEL)) numHoteles++;
        return true;
    }
    /////////////////////////////////////////////////
    
    boolean derruirCasas(int n, Jugador jugador){
        boolean esDerruida = false;
        if(esEsteElPropietario(jugador) && numCasas >= n){
            numCasas -= n;
            esDerruida = true;
        }
        return esDerruida;
    }
    
    public boolean esEsteElPropietario(Jugador jugador){
        boolean esPropietario = false;
        if(this.propietario == jugador)
            esPropietario = true;
        return esPropietario;
        
    }
    
    public boolean tienePropietario(){
        return propietario != null;
    }
    
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        switch(tipo){
            case CALLE:
                recibeJugador_calle(iactual, todos);
                break;
            case SORPRESA:
                recibeJugador_sorpresa(iactual, todos);
                break;
            case DESCANSO:
                informe(iactual, todos);
                break;
        }
    }
    
    private void recibeJugador_calle(int iactual, ArrayList<Jugador> todos){
        informe(iactual, todos);
        Jugador jugador =todos.get(iactual);
        if(!tienePropietario())
            jugador.puedeComprarCasilla();
        else
            tramitarAlquiler(jugador);
    }
    
    private void recibeJugador_sorpresa(int iactual, ArrayList<Jugador> todos){
        Sorpresa sorpresa = mazo.siguiente();
        informe(iactual, todos);
        sorpresa.aplicarAJugador(iactual, todos);
    }
    
    public void tramitarAlquiler(Jugador jugador){
        if(tienePropietario() && !esEsteElPropietario(jugador)){
            float importe = getPrecioAlquilerCompleto();
            jugador.pagaAlquiler(importe);
            this.propietario.recibe(importe);
            Diario.getInstance().ocurreEvento(jugador.getNombre() + 
                    " paga un alquiler de " + importe + "€ a " + propietario.getNombre());
        }
    }
    
    @Override
    public String toString(){
        String cadena;
        if(tipo == TipoCasilla.CALLE){
            cadena = tipo + " " + nombre + ". ";
            if(tienePropietario())
                cadena += "Propiedad de " + propietario.getNombre();
            else
                cadena += "Sin propietario";
            cadena += ". Precios: " + "Compra: " + precioCompra + ", " + "Edificar: " + 
            precioEdificar + ", " + "Alquiler base: " + precioBaseAlquiler + 
            ", " + "Casas: " + numCasas + ", " + "Hoteles: " + numHoteles;
        }
        else
            cadena = tipo + " " + nombre;
        
        return cadena;
    }
}
