/**
 * @file CasillaCalle.java
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

    public float getPrecioBaseAlquiler() {
        return precioBaseAlquiler;
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

    public void setPropietario(Jugador propietario) {
        this.propietario = propietario;
    }

    public void setNumCasas(int numCasas) {
        this.numCasas = numCasas;
    }

    public void setNumHoteles(int numHoteles) {
        this.numHoteles = numHoteles;
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
    
    private float calcularPorcentajeInversionPorSostenibilidad(){
        float porcentajeInversion = 5;
        if(cantidadCasasHoteles() > 0)
            porcentajeInversion = 2;
       
        return porcentajeInversion;
    }
    
    public float getImporteHacermeSostenible(){
        float importeExtra = getPrecioCompra()*calcularPorcentajeInversionPorSostenibilidad()/100;
        return importeExtra;
    }
    
    public CasillaCalleSostenible hacermeSostenible(){
        CasillaCalleSostenible convertida = new CasillaCalleSostenible(getNombre(), precioCompra, precioEdificar ,precioBaseAlquiler,calcularPorcentajeInversionPorSostenibilidad());
        convertida.setPropietario(propietario);
        convertida.setNumCasas(numCasas);
        convertida.setNumHoteles(numHoteles);
        return convertida;
    }
    
    public boolean soySostenible(){
        return false;
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
