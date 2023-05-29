package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteCompeticion extends AbstractPlayer{
	//Atributos de la clase
	private boolean listaCerrados[][]; // Nodos visitados, incluye muros y trampas. false no visitado, true visitado
    private PriorityQueueNodo listaAbiertos = new PriorityQueueNodo(); // Nodos sin visitar
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	private ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	private ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>(); // El camino generado hacia la meta
    
    private Vector2d portalFin;
    private Vector2d fescala;
    private Vector2d posicionJugador;
    
    private int filas, columnas;
	long tiempoTotalms = 0; // Mide el tiempo de busqueda
	int numeroAcciones = 0; // Mide el numero de acciones

	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgenteCompeticion(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// Calcular la escala de la cuadrícula
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
		// Calcular las dimensiones del mundo
		filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
		columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		
		//Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
       
	    // Encontrar el portal
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
		//Actualiza mapa de muros
		listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listadoInnamovible[0] = new ArrayList<Observation>(); //Para cambiar el tamaño
		actualizarInnmovable(stateObs);
	}

	private ArrayList<ACTIONS> algoritmoAStarModificado(StateObservation mundo){
		boolean estaAbiertos = false, estaCerrados = false;
		// Obtener posicion actual del jugador
		posicionJugador = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		
		Nodo actual = new Nodo(posicionJugador, ACTIONS.ACTION_NIL, null, portalFin, true);
		
		listaAbiertos.add(actual);	

		while(!listaAbiertos.isEmpty()) { //Mientras no encuentre el objetivo	
	        // Seleccionar el nodo con la menor distancia a la meta
			actual = listaAbiertos.poll();
			
	        // Añadir la posición del nodo actual a la lista de nodos cerrados
			listaCerrados[(int)actual.getPosicion().y][(int)actual.getPosicion().x] = true;
			
			if(actual.isEstadoFinal()) {
	            // Si se ha alcanzado el estado final, construir el camino de acciones
				camino.add(actual.getAccion());
				while(actual.getPadre() != null) {
					actual = actual.getPadre();
					camino.add(actual.getAccion());
				}
				// Terminar la busqueda
				break;
			}
			
			// Expandir los nodos hijos del nodo actual
			ArrayList<Nodo> hijos = actual.expandirHijos(mundo);
			for(Nodo n : hijos) {
				estaCerrados = listaCerrados[(int)n.getPosicion().y][(int)n.getPosicion().x];
				estaAbiertos = listaAbiertos.contains(n);
				
				// Si el nodo hijo está en cerrados y tiene mejor coste que el actual
				if(estaCerrados && actual.mejorCaminoA(n)) {
					// Lo sacamos de cerrados
					listaCerrados[(int)n.getPosicion().y][(int)n.getPosicion().x] = false;
					
					//Actualiza el nodo con el sucesor quitando el actual y metiendo el mejor
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
				else if(!estaCerrados && !estaAbiertos) { // Si el nodo hijo no está en cerrados ni abiertos lo añadimos a abiertos
					listaAbiertos.add(n);
				}
				else if(estaAbiertos && actual.mejorCaminoA(n)) { // Si el nodo hijo esta en abiertos
					//Actualiza el nodo con el sucesor quitando el actual y metiendo el mejor
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
			}
	        // Incrementar el número de nodos expandidos
			nodosExpandidos++;
		}
		return camino;
	}
	//FIN DEL ALGORITMO
	int nodosExpandidos = 0;
    private boolean actualizarInnmovable(StateObservation stateObs) {
    	ArrayList<Observation>[] nuevosObstaculos = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
    	boolean cambios = nuevosObstaculos[0].size() != listadoInnamovible[0].size() || nuevosObstaculos[1].size() != listadoInnamovible[1].size();
    	
    	// Si ha habido cambios en los obstaculos, actualiza
    	if(cambios) {
    		// Inicalizar cerrados
    		listaCerrados = new boolean[filas][columnas];
    		
			listadoInnamovible = nuevosObstaculos;
	        
			// Actualizar muros
			nuevosObstaculos[0].stream().forEach(obs -> {
	            int posx = (int) (obs.position.x / fescala.x);
	            int posy = (int) (obs.position.y / fescala.y);
	            listaCerrados[posy][posx] = true;
	        });

	        // Actualizar trampas
	        nuevosObstaculos[1].stream().forEach(obs -> {
	            int posx = (int) (obs.position.x / fescala.x);
	            int posy = (int) (obs.position.y / fescala.y);
	            listaCerrados[posy][posx] = true;
	        });
			listaAbiertos.clear();
			camino.clear();
		}
		
    	// Devuelve si ha habido cambios o no
		return cambios;
    }
    
	void imprimeInfo(long tInicio) {
		System.out.println("Tiempo de busqueda total: " + tiempoTotalms + " ms");
		System.out.println("Tamaño del camino: " + numeroAcciones);
		System.out.println("Nodos expandidos: " + nodosExpandidos);
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		ACTIONS accion = null;
		// Comprobar si camino vacio o cambios en los obstaculos
		if(camino.isEmpty() || actualizarInnmovable(stateObs)) {
			long tInicio = System.nanoTime(); //Mide el tiempo de busqueda
			camino = algoritmoAStarModificado(stateObs);
			long tFin = System.nanoTime();
			tiempoTotalms += ((tFin - tInicio)/1000000);
		}
	    
	    // Obtener la accion a realizar del camino
		if(!camino.isEmpty()) {
			accion = camino.remove(camino.size()-1);
			if(camino.isEmpty())
				imprimeInfo(columnas);
			numeroAcciones++;
		}
			
		return accion; 
	}	
	
}