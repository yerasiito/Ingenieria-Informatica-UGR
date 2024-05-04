/**
 * @file Controlador.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package controladorCivitas;

import GUI.CivitasView;
import civitas.CivitasJuego;
import civitas.GestionInmobiliaria;
import civitas.OperacionInmobiliaria;
import civitas.OperacionJuego;
import GUI.VistaTextual;

/**
 * @brief Clase Controlador que comunica @c CivitasJuego con @c VistaTextual
 * Permite la comunicacion entre paquetes sin violar el acceso a variables o 
 */
public class Controlador {
    private final CivitasJuego juego;
    private final CivitasView vista;
    
    //Visibilidad Modificada , antes era de paquete
    public Controlador(CivitasJuego juego, CivitasView civitasVista){
        this.juego = juego;
        this.vista = civitasVista;
    }
    
    public void juega(){
        OperacionJuego opcionJuego;
        vista.mostrarEventos();
        while(!juego.finalDelJuego()){                
            vista.actualiza();
            vista.pausa();
            opcionJuego = juego.siguientePaso();
            vista.mostrarSiguienteOperacion(opcionJuego);
            if(opcionJuego != OperacionJuego.PASAR_TURNO){
                vista.mostrarEventos();
            }
            
            if(!juego.finalDelJuego()){
                switch(opcionJuego){
                    
                    case COMPRAR:
                            if(vista.comprar() == Respuesta.SI)
                                juego.comprar();
                        juego.siguientePasoCompletado(opcionJuego);
                        vista.mostrarEventos();
                        break;
                    case GESTIONAR:
                        int numPropiedad;
                        OperacionInmobiliaria opcion = vista.elegirOperacion();
                        if( opcion != OperacionInmobiliaria.TERMINAR){
                            numPropiedad = vista.elegirPropiedad();
                            GestionInmobiliaria gestion = new GestionInmobiliaria(opcion, numPropiedad);
                            
                            switch(gestion.getOperacion()){
                                
                                case CONSTRUIR_CASA:
                                    juego.construirCasa(numPropiedad);
                                    break;
                                    
                                case CONSTRUIR_HOTEL: 
                                    juego.construirHotel(numPropiedad);
                                    break;
                            }
                        }     
                        juego.siguientePasoCompletado(opcionJuego);
                        vista.mostrarEventos();
                        break;
                }
            }
            else{
                System.out.println("Un jugador entró en bancarrota! Esto son los resultados:");
                vista.actualiza();
            }
        }
    }
}
