package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

/**
 * Implementación de A* en primer lugar
 * 
 *  Est_abiertos.insertar(Estado inicial)
    Actual �? Est_abiertos.primero()
    mientras no es_final?(Actual) y no Est_abiertos.vacía?() hacer
        Est_abiertos.borrar_primero()
        Est_cerrados.insertar(Actual)
        hĳos �? generar_sucesores (Actual)
        hĳos �? tratar_repetidos (Hĳos, Est_cerrados, Est_abiertos)
        Est_abiertos.insertar(Hĳos)
        Actual �? Est_abiertos.primero()
    fin
 * 
 */

public class AgentAstar extends AbstractPlayer{
	
	//Atributos de la clase
    private ArrayList<Nodo> listaCerrados;
    private ArrayList<Nodo> listaAbiertos;
    protected ArrayList<Nodo> frontera;
    
    private boolean rutaEncontrada;
    private ArrayList<ACTIONS> camino;
    private ACTIONS accion;
    
    Vector2d portalFin;
    Vector2d fescala;
    
	//StateObservation.getGameWinner() if WINNER.PLAYER_WINS
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgentAstar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
        //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        //Seleccionamos el portal mas proximo
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
        
        listaCerrados = new ArrayList<Nodo>();
		listaAbiertos = new ArrayList<Nodo>();
		frontera = new ArrayList<Nodo>();
		
		rutaEncontrada = false;

		accion = ACTIONS.ACTION_NIL;
		
		camino = new ArrayList<ACTIONS>();
		
	}
	
	//Implementacion del Algoritmo A*
	/*
	 * Algoritmo A*
	 * Est_Abiertos.insertar(EstadoInicial)
	 * Actual <- Est_Abiertos.primero()
	 * MIENTRAS NO es_final(actual) Y NO Est_Abiertos.vacia() DO
	 * 		Est_Abiertos.borrar_primero()
	 * 		Est_Cerrados.insertar(Actual)
	 * 		Hijos <- Actual.GenerarHijos()
	 * 		Hijos <- Repetidos(Hijos, Est_Cerrados, Est_Abiertos)
	 * 		Est_Abiertos.insertar(Hijos)
	 * 		Actual <- Est_Abiertos.primero()
	 * FIN
	 * 
	 * */
	private void AlgoritmoAStar(StateObservation mundo){
		
		Nodo nodoInicial = null;
		
		listaAbiertos.add(nodoInicial);
		Nodo actual = null;
		rutaEncontrada = false;
		
		while(!listaAbiertos.isEmpty() && !rutaEncontrada) {
			actual = listaAbiertos.get(0);
			listaAbiertos.remove(0);
			listaCerrados.add(actual);
			
			if(actual.getEstadoFinal()) {
				rutaEncontrada = true;
			
			}else {
//				frontera = actual.expandirHijos();
			
				for(Nodo n : frontera) {
					
					if(n.getEstadoFinal()) {
						listaCerrados.add(n);
						rutaEncontrada = true;
						
					}else {
						Repetido(n);
					}
				}//Por cada hijo
				
			}
		}//FIN DEL WHILE
	
	}//FIN DEL ALGORITMO

	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		
		if(listaCerrados.isEmpty()) {
			listaAbiertos.clear();
			AlgoritmoAStar(stateObs);
		}
		
		accion = listaCerrados.get(listaCerrados.size()-1).getAccion();
		listaCerrados.remove(listaCerrados.size()-1);
		
		return accion;
        
	}
	
	private void Repetido(Nodo aN){	
		/*
		 * Lo primero que hay que tener en cuenta es que si es la misma posicion XY
		 * pero el costo es distinto, quiere decir que uno de ellos tiene un padre mejor que el otro
		 * por tanto, se elimina el de peor costo, y se mantiene el otro
		 * Esto permitirá que se actualicen los padres (la ruta seguida)
		 * y optimizará el algoritmo
		 * */
		
		//Se sabe que si está en cerrada no está en abierta
		
		//Usa el Override hecho en la clase Nodo de EQUALS
		if(listaAbiertos.contains(aN)) {
			
			//Se coge el indice del que esta repetido
			int repetido = listaAbiertos.indexOf(aN);
			Nodo rep = listaAbiertos.get(repetido);
			
			//Se actualiza añadiendo el nuevo, con el padre actualizado
			if(aN.getValorF() < rep.getValorF()) {
				
				listaAbiertos.remove(rep);
				listaAbiertos.add(aN);
				Collections.sort(listaAbiertos);
				
			}
			
			
		}else {
			
			if(listaCerrados.contains(aN)) {
				
				int repetido = listaCerrados.indexOf(aN);
				Nodo rep = listaCerrados.get(repetido);
				
				if(aN.getValorF() < rep.getValorF()) {
					
					listaCerrados.remove(repetido);
					listaAbiertos.add(aN);
					Collections.sort(listaAbiertos);
				}
			
			//Fin de LISTACERRADA	
			}else{ //No está en ninguna lista
				listaAbiertos.add(aN);
				Collections.sort(listaAbiertos);
			}
			
		}//ELSE - LISTA ABIERTA
		
		
	}//FIN DEL METODO REPETIDO
	
	
}