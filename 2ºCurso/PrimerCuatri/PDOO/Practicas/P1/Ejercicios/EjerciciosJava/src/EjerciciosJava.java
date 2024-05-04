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
public class EjerciciosJava {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        //Sesion 1 - Parte 1
        Parcela Numero1 = new Parcela("Primera", 500 , 100, 300);
        
        Numero1.Detalles();
        Numero1.construirCasa();
        Numero1.construirHotel();
        Numero1.Detalles();

        //Sesion 1 - Parte 3
        Parcela Numero2 = new Parcela("Primera", 500 , 100, 300);
        Numero2.construirCasa();
        Numero2.construirHotel();
        
        //Parcela1 == Parcela2, por tanto misma identidad
        System.out.println("¿Numero1 igual identidad Numero2?\n" + Numero1.igualdadIdentidad(Numero2));
        System.out.println("¿Numero1 igual estado Numero2?\n" + Numero1.igualdadEstado(Numero2));
    }
    
}
