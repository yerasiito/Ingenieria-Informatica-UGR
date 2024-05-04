/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ejerciciosjava;

/**
 *
 * @author ylope
 */
public class Reserva {
    private String fechaEntrada;
    private String fechaSalida;
    private Cliente cliente;
    private Hotel hotel;
    
    public Reserva(String fEntrada, String fSalida, Cliente c, Hotel h){
        fechaEntrada = fEntrada;
        fechaSalida = fSalida;
        cliente = c;
        hotel = h;
        
    }
    
    public String getEntrada(){
        return fechaEntrada;
    }
    
    public String getSalida(){
        return fechaSalida;
    }
    
    public Cliente getCliente(){
        return cliente;
    }
    
    public Hotel getHotel(){
        return hotel;
    }
}
