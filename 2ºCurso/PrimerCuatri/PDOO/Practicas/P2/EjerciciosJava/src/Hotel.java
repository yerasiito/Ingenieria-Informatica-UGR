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
public class Hotel {
    private static int NUM_HOTELES;
    private String nombre;
    private String ciudad;
    private int estrellas;
    private Director director;
    private ArrayList<Reserva> reservas;
    private ArrayList<Empleado> empleados;
    private ArrayList<Habitacion> habitaciones;
    
    public Hotel(String n, String c, int e){
        nombre = n;
        ciudad = c;
        estrellas = e;
        NUM_HOTELES++;
        reservas = new ArrayList<>();
        empleados = new ArrayList<>();
        habitaciones = new ArrayList<>();
    }

    public Hotel(String n, String c, int e, Director d){
        this(n,c,e); //llama al constructor de arriba
        director = d;
    }
    
    public static int getNUM_HOTELES(){
        return NUM_HOTELES;
    }
    
    public void setDirector(Director d){
        director = d;
    }
    
   public Director getDirector(){
       return director;
    }
    
   public void addReserva(Cliente cliente, String fEntrada, String fSalida){
       Reserva nueva = new Reserva(fEntrada, fSalida, cliente, this);
       reservas.add(nueva);
       cliente.addReserva(nueva);
       
   }

    public ArrayList<Reserva> getReserva() {
        return reservas;
    }

   public int numReservas(){
       return reservas.size();
   }
   
   public boolean addEmpleado(Empleado e){
       boolean permitido = false;
       if(numEmpleados() < EjerciciosJava.NUM_HOTELES_MAX){
            empleados.add(e);
            permitido = true;
       }
       
       return permitido;
   }
   
   public int numEmpleados(){
       return empleados.size();
   }
   
   public void addHabitacion(int num, int cap){
       Habitacion nueva = new Habitacion(num,cap);
       habitaciones.add(nueva);
   } 
   
   public int buscarHabitacionCapacidad(int capacidad){
       int numHabitacion = -1;
       for(int i = 0; i < habitaciones.size() && numHabitacion == -1 ;i++)
           if(capacidad <= habitaciones.get(i).getCapacidad())
               numHabitacion = habitaciones.get(i).getNumero();
       
        return numHabitacion;
   }
}
