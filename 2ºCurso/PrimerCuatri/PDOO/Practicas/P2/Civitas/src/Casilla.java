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
public class Casilla {
    
    static final private float FACTORALQUILERCALLE = 1.0f;
    static final private float FACTORALQUILERCASA = 1.0f;
    static final private float FACTORALQUILERHOTEL = 4.0f;

    private String nombre;
    private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;
    private TipoCasilla tipo;
    private MazoSorpresas mazo;
    private Jugador jugador;

    private void init(){
        nombre = "";
        precioCompra = 0;
        precioEdificar = 0;
        precioBaseAlquiler = 0;
        numCasas = 0;
        numHoteles = 0;
        tipo = null;
        mazo = null;
        jugador = null;
    }
        
    //DESCANSO
    public Casilla(String nombre){
        init();
        tipo = TipoCasilla.DESCANSO;
        this.nombre = nombre;
    }
    
    //CALLE
    public Casilla(String titulo, float precioCompra, float precioEdificar, float precioBaseAlquiler){
        init();
        tipo = TipoCasilla.CALLE;
        nombre = titulo;
        this.precioCompra = precioCompra;
        this.precioEdificar = precioBaseAlquiler;
        this.precioBaseAlquiler = precioBaseAlquiler;
    }
    
    //SORPRESA
    public Casilla(String nombre, MazoSorpresas mazo){
        init();
        tipo = TipoCasilla.SORPRESA;
        this.nombre = nombre;
        this.mazo = mazo;
        
    }
    
    public String getNombre(){
        return nombre;
    }

    public int getNumCasas() {
        return numCasas;
    }

    public int getNumHoteles() {
        return numHoteles;
    }
    
    public float getPrecioAlquilerCompleto(){
        return precioBaseAlquiler* (FACTORALQUILERCALLE + numCasas*FACTORALQUILERCASA + numHoteles*FACTORALQUILERHOTEL);
    }
    
    public float getPrecioCompra() {
        return precioCompra;
    }

    public float getPrecioEdificar() {
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
    
    public void informe(int actual, ArrayList<Jugador> todos){
        String informe = "El jugador: " + todos.get(actual).getNombre() + 
                " ha caido en la " + toString();
        Diario.getInstance().ocurreEvento(informe);
    }

    //////////////////////////////////////////////////
    public boolean comprar(Jugador jugador){
        //pendiente
        return true;
    }
    
    public boolean construirCasa(Jugador jugador){
        //pendiente
        numCasas++;
        return true;
    }
    
    public boolean construirHotel(Jugador jugador){
        //pendiente
        numHoteles++;
        return true;
    }
    /////////////////////////////////////////////////
    
    public boolean derruirCasas(int n, Jugador jugador){
        boolean esDerruida = false;
        if(esEsteElPropietario(jugador) && numCasas >= n){
            numCasas -= n;
            esDerruida = true;
        }
        return esDerruida;
    }
    
    public boolean esEsteElPropietario(Jugador jugador){
        boolean esPropietario = false;
        if(this.jugador == jugador)
            esPropietario = true;
        return esPropietario;
        
    }
    
    public boolean tienePropietario(){
        return jugador != null;
    }
    
    public void recibeJugador(int iactual, ArrayList<Jugador> todos){
        //pendiente
    }
    
    public void recibeJugador_calle(int iactual, ArrayList<Jugador> todos){
        //pendiente
    }
    
    public void recibeJugador_sorpresa(int iactual, ArrayList<Jugador> todos){
        //pendiente
    }
    
    public void tramitarAlquiler(Jugador jugador){
        if(tienePropietario() && !esEsteElPropietario(jugador)){
            float importe = getPrecioAlquilerCompleto();
            jugador.pagaAlquiler(importe);
            this.jugador.recibe(importe);
        }
    }
    
    public String toString(){
        String cadena;
        if(tipo == TipoCasilla.CALLE){
            cadena = tipo + " " + nombre + ". ";
            if(tienePropietario())
                cadena += ". Propiedad de " + jugador.getNombre();
            else
                cadena += "Sin propietario. ";
            cadena += "Precios: " + "Compra: " + precioCompra + ", " + "Edificar: " + 
            precioEdificar + ", " + "Alquiler base: " + precioBaseAlquiler + 
            ", " + "Casas: " + numCasas + ", " + "Hoteles: " + numHoteles;
        }
        else
            cadena = tipo + " " + nombre;
        
        return cadena;
    }
}
