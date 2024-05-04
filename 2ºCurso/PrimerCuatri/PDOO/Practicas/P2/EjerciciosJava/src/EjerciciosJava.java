/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package ejerciciosjava;

/**
 *
 * @author ylope
 */
public class EjerciciosJava {
    
    public static final int NUM_HOTELES_MAX = 3; 
    
    public static void main(String[] args) {
        //EJERCICIO 1
        Hotel h1 = new Hotel("La palma","Madrid",4);
        Hotel h2 = new Hotel("Paquito", "Jaen", 2);
        
        System.out.println("Número de hoteles: " + Hotel.getNUM_HOTELES());
        //EJERCICIO 2
        Director d = new Director("Don Oreo", 605549452);
        h1.setDirector(d);
        System.out.println(h1.getDirector().getNombre());
        
        //EJERCICIO 3
        Cliente c1 = new Cliente("26050768W", "Yeray Lopez Ramirez");
        h2.addReserva(c1, "01/01/2021", "08/01/2021");
        
        System.out.println("Fecha de entrada: " + c1.getReserva(0).getEntrada());
        
        System.out.println("\nReservas Hotel");
        /*for(int i = 0; i < h2.numReservas(); i++){
            System.out.println("Reserva " + i + ", Entrada: " + h2.getReserva().getEntrada() + ", Cliente: " + h2.getReserva().getCliente() + "\n");
        }*/
        System.out.println("\nReservas Cliente");
        for(int i = 0; i < c1.numReservas(); i++){
            System.out.println("Reserva " + i + ", Entrada: " + c1.getReserva(i).getEntrada() + "\n");   
        }
    
        //SESION 2
        //EJERCICIO 1
        Empleado e1 = new Empleado("Amador");
        h1.addEmpleado(e1);
        
        System.out.println("El hotel h1 tiene " + h1.numEmpleados() + " empleados");
        System.out.println(e1.getNombre());
        
        //EJERCICIO 2
        h1.addHabitacion(10, 2);
        System.out.println("Numero de habitacion para 2 personas: " + h1.buscarHabitacionCapacidad(3));
        h1.addHabitacion(92, 3);
        System.out.println("Numero de habitacion para 2 personas: " + h1.buscarHabitacionCapacidad(3));        
    }   
    
    
}
