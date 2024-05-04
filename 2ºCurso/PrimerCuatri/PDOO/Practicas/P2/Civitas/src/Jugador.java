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
public class Jugador implements Comparable<Jugador>{
    private final static int CasasMax = 4;
    private final static int HotelesMax = 4;
    private final static int CasasPorHotel = 4;
    private final static float PasoporSalida = 1000f;
    private final static float SaldoInicial = 7500f;
    
    private int casillaActual;
    private String nombre;
    private boolean puedeComprar;
    private float saldo;
    private ArrayList<Casilla> propiedades;
    
    private void init(){
        casillaActual = 0;
        nombre = "";
        puedeComprar = false;
        saldo = SaldoInicial;
        propiedades = new ArrayList<>();
    }
    
    public Jugador(String nombre){
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
    
    public int CantidadCasasHoteles(){
        int total = 0;
        for(int i = 0; i < propiedades.size(); i++)
            total += propiedades.get(i).cantidadCasasHoteles();
        
        return total;
    }

    public static int getCasasMax(){
        return CasasMax;
    }
    
    public static int getCasasPorHotel(){
        return CasasPorHotel;
    }
    
    public int getCasillaActual(){
        return casillaActual;
    }
    
    public static int getHotelesMax(){
        return HotelesMax;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public static float getPremioPasoSalida(){
        return PasoporSalida;
    }

    public ArrayList<Casilla> getPropiedades() {
        return propiedades;
    }
    
    public boolean getPuedeComprar(){
        return puedeComprar;
    }
    
    public float getSaldo(){
        return saldo;
    }
        
    public int compareTo(Jugador otro){
        return Float.compare(otro.getSaldo(), saldo);
    }
    ////////////////////////////////////////////////////////////////////////////    
    public boolean comprar(Casilla titulo){
        //pendiente
        return true;
    }
    
    public boolean construirCasa(int i){
        //pendiente
        return true;
    }
    
    public boolean construirHotel(int i){
        //pendiente
        return true;
    }
    ////////////////////////////////////////////////////////////////////////////
    public boolean enBancarrota(){
        return saldo < 0;
    }
    
    public boolean existeLaPropiedad(int ip){
        boolean existe = false;
        if(ip > -1 && ip < propiedades.size())
            existe = true;
        return existe;
    }
    
    public boolean modificarSaldo(float cantidad){
        saldo+=cantidad;
        String evento = "El jugador " + nombre + " ha modificado su saldo en "
                + cantidad + " €";
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    public boolean moverACasilla(int numCasilla){
        casillaActual = numCasilla;
        puedeComprar = false;
        String evento = "El jugador " + nombre + " se ha movido a la casilla "
                + numCasilla;
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    public boolean paga(float cantidad){
        return modificarSaldo(cantidad*-1);
    }
    
    public boolean pagaAlquiler(float cantidad){
        return paga(cantidad);
    }
    
    public boolean pasaPorSalida(){
        recibe(PasoporSalida);
        String evento = "El jugador " + nombre + " ha pasado por la Salida";
        Diario.getInstance().ocurreEvento(evento);
        return true;
    }
    
    public boolean puedeComprarCasilla(){
        return saldo >= propiedades.get(casillaActual).getPrecioCompra();
    }
    
    public boolean puedoEdificarCasa(Casilla propiedad){
        boolean puedoEdificar = false;
        if(puedoGastar(propiedad.getPrecioEdificar()) 
                && propiedad.getNumCasas() < CasasMax)
            puedoEdificar = true;
        
        return puedoEdificar;
    }
    
    public boolean puedoEdificarHotel(Casilla propiedad){
        boolean puedoEdificar = false;
        if(puedoGastar(propiedad.getPrecioEdificar()*Casilla.getFACTORALQUILERHOTEL()) 
                && propiedad.getNumCasas() == CasasPorHotel
                && propiedad.getNumHoteles() < HotelesMax)
            puedoEdificar = true;
        
        return puedoEdificar;
    }
    
    public boolean puedoGastar(float precio){
        return saldo >= precio;
    }
    
    public boolean recibe(float cantidad){
        return modificarSaldo(cantidad);
    }
    
    public boolean tieneAlgoQueGestionar(){
        return !propiedades.isEmpty();
    }
    
    public String toString(){
         return ("Jugador: " +nombre
                + ", Casilla Actual: " + casillaActual
                + ", Saldo: " + saldo + "\n");
    }
}
