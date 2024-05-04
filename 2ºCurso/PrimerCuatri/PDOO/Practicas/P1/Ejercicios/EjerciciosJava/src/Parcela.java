/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejercicios;
/**
 *
 * @author ylope
 */
public class Parcela {
    private static float FACTORALQUILERCALLE = 1.0f;
    private static float FACTORALQUILERCASA = 1.0f;
    private static float FACTORALQUILERHOTEL = 4.0f;
    private String nombre;
    private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles;
    
    //Constructor Publico
    public Parcela (String n, float pCompra, float pEdificar, float pBaseAlquiler){
        nombre = n;
        precioCompra = pCompra;
        precioEdificar = pEdificar;
        precioBaseAlquiler = pBaseAlquiler;
        numCasas = 0;
        numHoteles = 0;
    }
    
    void Detalles(){
        System.out.println("Parcela: " +nombre
                            + "\nPrecio de Compra: " +precioCompra
                            + "\nPrecio Edificar: " +precioEdificar
                            + "\nPrecio Base de Alquiler: " +precioBaseAlquiler
                            + "\nNumero de casas: " +numCasas
                            + "\nNumero de hoteles: " +numHoteles
                            + "\nPrecio de Alquiler Completo:" +getPrecioAlquilerCompleto() +"\n\n"
        );
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
        return precioBaseAlquiler*(FACTORALQUILERCALLE + numCasas*FACTORALQUILERCASA + numHoteles*FACTORALQUILERHOTEL);
    }
 
    public boolean construirCasa(){
        numCasas++;
        return true;
    }
    
    public boolean construirHotel(){
        numHoteles++;
        return true;
    }
    
    public boolean igualdadIdentidad (Parcela otraParcela){
        return otraParcela == this;
    }
    public boolean igualdadEstado (Parcela otraParcela){
        return nombre.equals(otraParcela.getNombre())
            && precioCompra == otraParcela.getPrecioCompra()
            && precioEdificar == otraParcela.getPrecioEdificar()
            && getPrecioAlquilerCompleto() == otraParcela.getPrecioAlquilerCompleto()
            && numCasas == otraParcela.getNumCasas()
            && numHoteles == otraParcela.getNumHoteles();
    }
}
