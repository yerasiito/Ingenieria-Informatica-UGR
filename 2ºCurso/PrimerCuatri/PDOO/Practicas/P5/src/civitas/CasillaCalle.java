/**
 * @file CasillaCalle.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Hija de Casilla que gestiona las calles del @c Tablero. Las Calles
 * pertenecen a esta clase.
 */
public class CasillaCalle extends Casilla{
    static final private float FACTORALQUILERCALLE = 1.0f;
    static final private float FACTORALQUILERCASA = 1.0f;
    static final private float FACTORALQUILERHOTEL = 4.0f;
    
    private final float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;
    private Jugador propietario;
    
    CasillaCalle(String titulo, float precioCompra, float precioEdificar, float precioBaseAlquiler){
        super(titulo);
        this.precioCompra = precioCompra;
        this.precioEdificar = precioEdificar;
        this.precioBaseAlquiler = precioBaseAlquiler;
    }
    
    public int getNumCasas() {
        return numCasas;
    }

    public int getNumHoteles() {
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
            Diario.getInstance().ocurreEvento(jugador.getNombre() + 
                    " paga un alquiler de " + importe + "€ a " + propietario.getNombre()
                    + " por la propiedad " + getNombre());
            jugador.pagaAlquiler(importe);
            this.propietario.recibe(importe);
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
    
    void actualizaPropietarioPorConversion(JugadorEspeculador convertido){
        Jugador antiguo = propietario;
        propietario = convertido;
        Diario.getInstance().ocurreEvento("La propiedad " + getNombre()
                + " pasa de " + antiguo.getNombre() + " " + antiguo.getClass() 
                + " a " + propietario.getNombre() + " " + propietario.getClass());
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
