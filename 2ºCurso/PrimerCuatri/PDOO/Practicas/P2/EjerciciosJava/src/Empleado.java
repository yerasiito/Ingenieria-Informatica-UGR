/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ejerciciosjava;
import java.util.ArrayList;
/**
 *
 * @author ylope
 */
public class Empleado {
    private String nombre;
    private ArrayList<Hotel> hoteles;
    
    public Empleado(String n){
        nombre = n;
        hoteles = new ArrayList<>();
    }

    public String getNombre() {
        return nombre;
    }
    
    public boolean addTrabajo(Hotel hotel){
        boolean permitido = false;
        if(hoteles.size() < EjerciciosJava.NUM_HOTELES_MAX){
            hotel.addEmpleado(this);
            permitido = true;
        }
        return permitido;
    }
}
