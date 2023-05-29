package src_LOPEZ_RAMIREZ_YERAY;

import java.util.ArrayList;
import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

/**
 * initialize all variables for the agent
 * @param stateObs Observation of the current state.
 * @param elapsedTimer Timer when the action returned is due.
 * @throws IOException 
 */
public class AgenteDijkstra extends AbstractPlayer{
	//Atributos de la clase
	private boolean listaCerrados[][]; //Nodos visitados, incluye muros y trampas. false no visitado, true visitado
    private PriorityQueueNodo listaAbiertos = new PriorityQueueNodo(); //Nodos sin visitar
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	private ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>();	//El camino generado hacia la meta
	
    private ACTIONS accion;
    
    private Vector2d portalFin;
    private Vector2d fescala;
    private Vector2d posicionJugador;
  
	public AgenteDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// Calcular la escala de la cuadrícula
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
		
		// Calcular las dimensiones del mundo
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
      
	    // Encontrar el portal
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
		// Encontrar las posiciones de los obstáculos y agregarlas a la matriz de cerrados
		ArrayList<Observation>[] listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listaCerrados = new boolean[filas][columnas];
		for(ArrayList<Observation> obsList : listadoInnamovible) {
			for(Observation obs : obsList) {
				int posy = (int)(obs.position.y/fescala.y); //La pos y en la matriz es la fila
				int posx = (int)(obs.position.x/fescala.x); //La pos x en la matriz es la columna
				listaCerrados[posy][posx] = true;
			}
		}
	
		// Obtener la posicion del jugador
		posicionJugador = new Vector2d(stateObs.getAvatarPosition().x/fescala.x, stateObs.getAvatarPosition().y/fescala.y);
		
		// Para que no avance si no encuentra camino o se queda sin tiempo
		accion = null;
	}
	
	int nodosExpandidos = 0;
	private ArrayList<ACTIONS> AlgoritmoDijkstra(StateObservation mundo){
	    // Crear el nodo inicial y añadirlo a la lista abierta
		Nodo nodoInicial = new Nodo(posicionJugador, null, null, portalFin, false);
		listaAbiertos.add(nodoInicial);	
		Nodo actual;

		while(!listaAbiertos.isEmpty()) { // Mientras haya nodos en abiertos
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
				nodosExpandidos++;
				// Terminar la busqueda
				break;
			}

			// Expandir los nodos hijos del nodo actual
			ArrayList<Nodo> hijos = actual.expandirHijos(mundo);
			for(Nodo n : hijos) {
	            // Si el nodo hijo no está en abiertos ni en cerrados, añadirlo a abiertos
				if(!listaCerrados[(int)n.getPosicion().y][(int)n.getPosicion().x] && !listaAbiertos.contains(n)) {
					listaAbiertos.add(n);
				}
			}
	        // Incrementar el número de nodos expandidos
			nodosExpandidos++;
		}
		return camino;
	}
	//FIN DEL ALGORITMO
	
	void imprimeInfo(long tInicio) {
		long tFin = System.nanoTime();
		long tiempoTotalms = (tFin - tInicio)/1000000;
		System.out.println("Tiempo de busqueda total: " + tiempoTotalms + " ms");
		System.out.println("Tamaño del camino: " + (camino.size()-1));
		System.out.println("Nodos expandidos: " + nodosExpandidos);
	} 
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
	    // Calcular el camino con Dijkstra
		if (camino.isEmpty()) {
		    listaAbiertos.clear();
			long tInicio = System.nanoTime(); //Mide el tiempo de busqueda
	    	camino = AlgoritmoDijkstra(stateObs);
	    	imprimeInfo(tInicio); // Imprime la info estrictamente necesaria
        }
		
	    // Obtener la accion a realizar del camino
	    if(!camino.isEmpty())
			accion = camino.remove(camino.size()-1);
			
		return accion;
        
	}	
}