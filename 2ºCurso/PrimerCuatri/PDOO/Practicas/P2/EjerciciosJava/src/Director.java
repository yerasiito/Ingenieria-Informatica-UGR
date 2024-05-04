/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ejerciciosjava;

/**
 *
 * @author ylope
 */
public class Director {
    private String nombre;
    private long telefono;
    
    Director(String n, long tlf){
        nombre = n;
        telefono = tlf;
    }
    
    String getNombre(){
        return nombre;
    }
}
