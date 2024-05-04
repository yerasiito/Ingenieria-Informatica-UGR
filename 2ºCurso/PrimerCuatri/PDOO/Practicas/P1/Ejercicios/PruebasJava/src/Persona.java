/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package pruebasjava;

/**
 *
 * @author ylope
 */
public class Persona {
    // Atributo y Método de clase
    static private int numPersonas = 0;
    static int getNumPersonas() {
        return numPersonas;
    }
    //Atributo de instancia 
    private String nombre;
    //Incializador
    Persona ( String unNombre) {
        nombre = unNombre;
        numPersonas++;
    }
    
}
