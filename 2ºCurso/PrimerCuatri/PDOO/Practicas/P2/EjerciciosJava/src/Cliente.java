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
public class Cliente {
   private String dni;
   private String nombre;
   private ArrayList<Reserva> reservas;
   
   public Cliente(String d, String n){
       dni = d;
       nombre = n;
       reservas = new ArrayList<>();
   }
   
   public String getNombre(){
       return nombre;
   }
   
   public void addReserva(Reserva reserva){
       reservas.add(reserva);
   }
   
   public Reserva getReserva(int indice){
       return reservas.get(indice);
   }
   
   public int numReservas(){
       return reservas.size();
   }
}
