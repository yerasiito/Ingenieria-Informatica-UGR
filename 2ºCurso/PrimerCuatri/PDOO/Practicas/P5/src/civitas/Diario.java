/**
 * @file Diario.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Diario que gestiona los eventos del juego.
 * Es un singleton por lo que no puede ser instanciada(No hay constructor)
 * Igualmente se pueden crear objetos diario para no escribir Diario.getInstance()
 */
public class Diario {
  static final private Diario instance = new Diario(); //Declaracion Singleton
  
  private final ArrayList<String> eventos;
  
  static public Diario getInstance() {
    return instance;
  }

  public ArrayList<String> getEventos() {
      return eventos;
  }
  
  private Diario () {
      eventos = new ArrayList<>();
  }
  
  public void ocurreEvento (String e) {
      eventos.add (e + ".");
  }
  
  //Visibilidad modificada, antes era de Paquete
  public boolean eventosPendientes () {
      return !eventos.isEmpty();
  }
  
  public String leerEvento () {
      String salida = "";
      if (!eventos.isEmpty())
          salida = eventos.remove(0);
      
      return salida;
  }
}
