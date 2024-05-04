/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package pruebasjava;
/**
 *
 * @author ylope
 */
public class PruebasJava {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Persona p = new Persona("Felipe");
        Persona p1 = new Persona("Maria");
        Persona p2 = new Persona("Maria");
        
        System.err.println(Persona.getNumPersonas());
    }
    
}
