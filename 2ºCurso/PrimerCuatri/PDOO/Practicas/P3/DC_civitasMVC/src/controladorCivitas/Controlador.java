/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controladorCivitas;

import civitas.CivitasJuego;
import civitas.GestionInmobiliaria;
import civitas.OperacionInmobiliaria;
import civitas.OperacionJuego;
import vistaTextualCivitas.VistaTextual;

/**
 *
 * @author yerasito
 */
public class Controlador {
    private CivitasJuego juego;
    private VistaTextual vista;
    
    //Visibilidad Modificada , antes era de paquete
    public Controlador(CivitasJuego juego, VistaTextual vista){
        this.juego = juego;
        this.vista = vista;
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
                        int numPropiedad = -1;
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
