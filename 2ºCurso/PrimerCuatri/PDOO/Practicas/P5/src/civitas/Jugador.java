/**
 * @file Jugador.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Padre Jugador que gestiona sus atributos y propiedades.
 * Un jugador puede:
 *  -Moverse por el tablero.
 *  -Comprar propiedades(Casilla calle)
 *  -Construir casas y hoteles dentro de las reglas del juego
 *  -Pagar o Cobrar dinero de sorpresas y/o hipotecas de calles de otro jugador
 *  -Convertirse en un Especulador(Clase hija) que modifica ciertos atributos
 * 
 * El implements Comparable es necesario para el método CompareTo
 * necesario para el ranking de jugadores por saldo(compara saldos)
 * 
 * El jugador gana si el resto están en bancarrota y pierde si acaba en bancarrota
 */
public class Jugador implements Comparable<Jugador>{
    protected static int CasasMax = 4;
    protected static int HotelesMax = 4;
    protected static int CasasPorHotel = 4;
    protected static float PasoporSalida = 1000f;
    private static float SaldoInicial = 7500f;
    
    private int casillaActual;
    private String nombre;
    private boolean puedeComprar;
    private float saldo;
    private ArrayList<CasillaCalle> propiedades;
    
    private void init(){
        casillaActual = 0;
        nombre = "";
        puedeComprar = false;
        saldo = SaldoInicial;
        propiedades = new ArrayList<>();
    }
    
    Jugador(String nombre){
        init();
        this.nombre = nombre;
    }
    
    //constructor de copia
    protected Jugador(Jugador otro){
        this.nombre = otro.nombre;
        this.casillaActual = otro.casillaActual;
        this.saldo = otro.saldo;
        this.puedeComprar = otro.puedeComprar;
        this.propiedades = otro.propiedades;
    }
    
    int CantidadCasasHoteles(){
        int total = 0;
        for(int i = 0; i < propiedades.size(); i++)
            total += propiedades.get(i).cantidadCasasHoteles();
        
        return total;
    }

    private int getCasasMax(){
        return CasasMax;
    }
    
    int getCasasPorHotel(){
        return CasasPorHotel;
    }
    
    public static int getNumCasasPorHotel(){
        return CasasPorHotel;
    }
    
    public int getCasillaActual(){
        return casillaActual;
    }
    
    private int getHotelesMax(){
        return HotelesMax;
    }
    //vibilidad modificada, antes protected
    public String getNombre(){
        return nombre;
    }
    
    private float getPremioPasoSalida(){
        return PasoporSalida;
    }

    //Visibilidad Modificada, era Protected
    public ArrayList<CasillaCalle> getPropiedades() {
        return propiedades;
    }
    
    boolean getPuedeComprar(){
        return puedeComprar;
    }
    
    //visibilidad modificada, antes protected
    public float getSaldo(){
        return saldo;
    }
    
    @Override   
    public int compareTo(Jugador otro){
        return Float.compare(otro.getSaldo(), saldo);
    }
    ////////////////////////////////////////////////////////////////////////////    
    boolean comprar(CasillaCalle titulo){
        boolean result = false;
        if(puedeComprarCasilla()){ //puedeComprarCasilla?
            float precio = titulo.getPrecioCompra();

            if(puedoGastar(precio)){
                result = titulo.comprar(this);
                propiedades.add(titulo);
                Diario.getInstance().ocurreEvento(nombre + " compra la propiedad " + titulo.getNombre());
                puedeComprar = false;
            }
            else
                Diario.getInstance().ocurreEvento(nombre + " no tiene saldo para ocmprar la propiedad " + titulo);
        }
        
        return result;
    }
    
    boolean construirCasa(int ip){
        boolean result = false, existe = existeLaPropiedad(ip); 
        if(existe){
            CasillaCalle propiedad = propiedades.get(ip);
            boolean puedoEdificar = puedoEdificarCasa(propiedad);
            if(puedoEdificar){
                result = propiedad.construirCasa(this);
                Diario.getInstance().ocurreEvento(nombre+ " construye una casa en la propiedad " 
                        + propiedades.get(ip).getNombre());
            }
        }
        
        return result;
    }
    
    boolean construirHotel(int ip){
        boolean result = false;
        if(existeLaPropiedad(ip)){
            CasillaCalle propiedad = propiedades.get(ip);
            boolean puedoEdificarHotel = puedoEdificarHotel(propiedad);
            
            if(puedoEdificarHotel){
                result = propiedad.construirHotel(this);
                propiedad.derruirCasas(CasasPorHotel, this);
                Diario.getInstance().ocurreEvento(nombre+ " construye un hotel en propiedad " 
                        +  propiedades.get(ip).getNombre());
            }
        }
        
        return result;
    }
    ////////////////////////////////////////////////////////////////////////////
    boolean enBancarrota(){
        return saldo < 0;
    }
    
    private boolean existeLaPropiedad(int ip){
        boolean existe = false;
        if(ip > -1 && ip < propiedades.size())
            existe = true;
        return existe;
    }
    
    boolean modificarSaldo(float cantidad){
        String evento = "";
        saldo+=cantidad;
        if(cantidad>0)
             evento = nombre + " ha recibido " + cantidad + " €";
        else if(cantidad<0)
             evento = nombre + " ha gastado " + cantidad + " €";
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    boolean moverACasilla(int numCasilla){
        casillaActual = numCasilla;
        puedeComprar = false;
        String evento = nombre + " se ha movido a la casilla "
                + numCasilla;
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    boolean paga(float cantidad){
        return modificarSaldo(cantidad*-1);
    }
    
    boolean pagaAlquiler(float cantidad){
        return paga(cantidad);
    }
    
    boolean pasaPorSalida(){
        recibe(getPremioPasoSalida());
        String evento = nombre + " ha pasado por la Salida";
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    boolean puedeComprarCasilla(){
        puedeComprar = true;
        return puedeComprar;
    }
    
    private boolean puedoEdificarCasa(CasillaCalle propiedad){
        boolean puedoEdificar = false;
        if(!puedoGastar(propiedad.getPrecioEdificar()))
            Diario.getInstance().ocurreEvento(this.nombre + 
                    " ha intentado edificar una casa en " + propiedad.getNombre() +
                    " pero no tiene suficiente dinero." + "La casa vale " +
                    propiedad.getPrecioEdificar() + " y el jugador tiene " + saldo);
        else if(propiedad.getNumCasas() >= getCasasMax())
            Diario.getInstance().ocurreEvento(this.nombre + 
                    " ha intentado edificar una casa en " + propiedad.getNombre() +
                    " pero ha excedido el limite de casas");
        else
            puedoEdificar = true;
        
        return puedoEdificar;
    }
    
    private boolean puedoEdificarHotel(CasillaCalle propiedad){
        boolean puedoEdificar = false;
        float precioHotel = propiedad.getPrecioEdificar()*CasillaCalle.getFACTORALQUILERHOTEL();
        if(!puedoGastar(precioHotel)) 
            Diario.getInstance().ocurreEvento(this.nombre + 
                    " ha intentado edificar un hotel en " + propiedad.getNombre() +
                    " pero no tiene suficiente dinero." + "El hotel vale " +
                    precioHotel + " y el jugador tiene " + saldo);
        else if(propiedad.getNumCasas() < CasasPorHotel)
            Diario.getInstance().ocurreEvento(this.nombre + 
                    " ha intentado edificar un hotel en " + propiedad.getNombre() +
                    " pero no tiene suficientes casas. Necesita " + CasasPorHotel
                    + " y tiene " + propiedad.getNumCasas());
        else if(propiedad.getNumHoteles() >= getHotelesMax())
            Diario.getInstance().ocurreEvento(this.nombre + 
                    " ha intentado edificar un hotel en " + propiedad.getNombre() +
                    " pero ha excedido el limite de hoteles");
        else
            puedoEdificar = true;
        
        return puedoEdificar;
    }
    
    private boolean puedoGastar(float precio){
        return saldo >= precio;
    }
    
    boolean recibe(float cantidad){
        return modificarSaldo(cantidad);
    }
    
    boolean tieneAlgoQueGestionar(){
        return !propiedades.isEmpty();
    }
    
    JugadorEspeculador convertir(){
        return new JugadorEspeculador(this);
    }
    
    @Override
    public String toString(){
        String cadena = "Jugador: " +nombre
                + ", Casilla Actual: " + casillaActual
                + ", Saldo: " + saldo;
        if(!propiedades.isEmpty()){
            cadena += ". Propiedades de " + this.nombre + ":\n";
            for(int i = 0; i < propiedades.size(); i++)
                cadena += " -" + propiedades.get(i).toString();
        }
        else
            cadena += ". No tiene propiedades aún.";
        
        cadena += "\n";
        return cadena;
    }
}
