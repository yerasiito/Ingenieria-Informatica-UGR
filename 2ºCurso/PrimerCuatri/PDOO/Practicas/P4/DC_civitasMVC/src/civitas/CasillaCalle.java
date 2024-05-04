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
public class CasillaCalle extends Casilla{
    static final private float FACTORALQUILERCALLE = 1.0f;
    static final private float FACTORALQUILERCASA = 1.0f;
    static final private float FACTORALQUILERHOTEL = 4.0f;
    
    private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;
    private Jugador propietario;
    
    CasillaCalle(String titulo, float precioCompra, float precioEdificar, float precioBaseAlquiler){
        super(titulo);
        this.precioCompra = precioCompra;
        this.precioEdificar = precioEdificar;
        this.precioBaseAlquiler = precioBaseAlquiler;
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
    void recibeJugador(int iactual, ArrayList<Jugador> todos){
        
        Jugador jugador = todos.get(iactual);
        if(!tienePropietario())
            jugador.puedeComprarCasilla();
        else
            tramitarAlquiler(jugador);
    
        super.recibeJugador(iactual,todos);
    }
    @Override
    public String toString(){
        String cadena = "Calle " + super.toString() + ". ";

        if(tienePropietario())
            cadena += "Propiedad de " + propietario.getNombre();
        else
            cadena += "Sin propietario";
        
        cadena += ". Precios: " 
                + "Compra: " + precioCompra + ", " 
                + "Edificar: " + precioEdificar + ", "
                + "Alquiler base: " + precioBaseAlquiler + ", " 
                + "Casas: " + numCasas + ", " + "Hoteles: " + numHoteles;
        
        return cadena;
    }
}
