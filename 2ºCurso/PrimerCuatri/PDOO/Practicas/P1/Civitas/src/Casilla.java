/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

/**
 *
 * @author ylope
 */
public class Casilla {
    
    static final private float FACTORALQUILERCALLE = 1.0f;
    static final private float FACTORALQUILERCASA = 1.0f;
    static final private float FACTORALQUILERHOTEL = 4.0f;
    
    final private TipoCasilla tipo;
    final private String nombre;
    final private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;

    public Casilla (TipoCasilla unTipo, String unNombre, float unPrecioCompra, 
            float unPrecioEdificar, float unPrecioAlquilerBase){
        tipo = unTipo;
        nombre = unNombre;
        precioCompra = unPrecioCompra;
        precioEdificar = unPrecioEdificar;
        precioBaseAlquiler = unPrecioAlquilerBase;
        numCasas = 0;
        numHoteles = 0;
    }
    public TipoCasilla getTipo() {
        return tipo;
    }
    
    public String getNombre() {
        return nombre;
    }

    public float getPrecioCompra() {
        return precioCompra;
    }

    public float getPrecioEdificar() {
        return precioEdificar;
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
    
    public boolean construirCasa(){
        numCasas++;
        return true;
    }
    
    public boolean construirHotel(){
        numHoteles++;
        return true;
    }
    
    public boolean igualdadIdentidad (Casilla otraCasilla){
        return otraCasilla == this;
    }
    public boolean igualdadEstado (Casilla otraCasilla){
        return nombre.equals(otraCasilla.getNombre())
            && precioCompra == otraCasilla.getPrecioCompra()
            && precioEdificar == otraCasilla.getPrecioEdificar()
            && getPrecioAlquilerCompleto() == otraCasilla.getPrecioAlquilerCompleto()
            && numCasas == otraCasilla.getNumCasas()
            && numHoteles == otraCasilla.getNumHoteles();
    }
    public String toString(){
        String resultado = tipo + " " + nombre + ". " + "Precios: " + 
            "Compra: " + precioCompra + ", " + "Edificar: " + precioEdificar + 
            ", " + "Alquiler base: " + precioBaseAlquiler + 
            ", " + "Casas: " + numCasas + ", " + "Hoteles: " + numHoteles; 
        return resultado;
    }
}
