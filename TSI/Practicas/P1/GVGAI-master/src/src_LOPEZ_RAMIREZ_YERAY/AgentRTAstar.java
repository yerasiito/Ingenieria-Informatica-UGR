package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgentRTAstar extends AbstractPlayer{
	//Atributos de la clase
	private boolean obstaculos[][];
    protected ArrayList<Nodo> HijosActual; //Hijos en la ejecucion
	ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	private double matrizHeuristica[][];
	
    Vector2d portalFin;
    Vector2d fescala;
    private Vector2d posicionJugador;
  
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgentRTAstar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// Calcular la escala de la cuadrícula
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
		// Calcular las dimensiones del mundo
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);

        
	    // Encontrar el portal más cercano
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
        // Inicializar matriz de obstaculos
		listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listadoInnamovible[0] = new ArrayList<Observation>(); //Para cambiar el tamaño
		obstaculos = new boolean[filas][columnas];
		actualizarInnmovable(stateObs);
		
		//Inicializar la matriz heuristica
		matrizHeuristica = new double[filas][columnas];
		for(int i = 0; i < matrizHeuristica.length; i++) {
			for(int j = 0; j < matrizHeuristica[0].length; j++) {
				matrizHeuristica[i][j] = HeuristicaManhattan(j,i);
			}
		}
		
		// Obtener la posicion del jugador
		posicionJugador = new Vector2d(stateObs.getAvatarPosition().x/fescala.x, stateObs.getAvatarPosition().y/fescala.y);
	}
	
	// Actualiza la matriz de obstaculos en cada iteracion
    private void actualizarInnmovable(StateObservation stateObs) {
    	ArrayList<Observation>[] nuevosObstaculos = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		
    	// Si ha habido cambios en los obstaculos, actualiza
    	if(nuevosObstaculos[0].size() != listadoInnamovible[0].size() || nuevosObstaculos[1].size() != listadoInnamovible[1].size()) {
			listadoInnamovible = nuevosObstaculos;
	        
			// Actualizar muros
			nuevosObstaculos[0].stream().forEach(obs -> {
	            int posx = (int) (obs.position.x / fescala.x);
	            int posy = (int) (obs.position.y / fescala.y);
	            obstaculos[posy][posx] = true;
	        });

	        // Actualizar trampas
	        nuevosObstaculos[1].stream().forEach(obs -> {
	            int posx = (int) (obs.position.x / fescala.x);
	            int posy = (int) (obs.position.y / fescala.y);
	            obstaculos[posy][posx] = true;
	        });
		}
    }
    
	//Metaheuristica - Distancia Manhattan
    private double HeuristicaManhattan(int x, int y) {      
        double xDiff = 0, yDiff = 0;

        // Se calcula la diferencia en la coordenada X y Y entre la posición actual y la meta
    	xDiff = Math.abs(x - portalFin.x);
        yDiff = Math.abs(y - portalFin.y);
        
        // Se devuelve la suma de las diferencias en X y Y
        return xDiff + yDiff;
    }
	
	int nodosExpandidos = 1;
	private ACTIONS AlgoritmoRTA(StateObservation mundo){
	    // Actualizar la posición del jugador
		posicionJugador = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
	    
		// Crear un nuevo nodo con la posicion actual del jugador
		Nodo nodoLocal = new Nodo(posicionJugador, ACTIONS.ACTION_NIL, null, portalFin, true);		
		
		// Actualizamos el valor del nodo con el valor de la tabla heuristica
		double valorH = matrizHeuristica[(int)posicionJugador.y][(int)posicionJugador.x];
		nodoLocal.setValorH(valorH);
		
		// Expandir los hijos
		ArrayList<Nodo> hijos = nodoLocal.expandirHijos(mundo);
		
	    // Crear la cola de prioridad
		PriorityQueueNodo expandidos = new PriorityQueueNodo();
		for(Nodo n : hijos) { //Obtenga las F
			//Si es el nodo final, devolver la accion
			if(n.isEstadoFinal()) {
				nodosExpandidos++;
				System.out.println("Nodos expandidos: " + nodosExpandidos);
				return n.getAccion();
			}
	        // Si no es un obstáculo, añadirlo a expandidos
			if(!obstaculos[(int)n.getPosicion().y][(int)n.getPosicion().x]) {
				valorH = matrizHeuristica[(int)n.getPosicion().y][(int)n.getPosicion().x];
				n.setValorH(valorH);
				expandidos.add(n);
			}
		}

		//Primer minimo
		Nodo minimo = expandidos.poll();
		ACTIONS accion = minimo.getAccion();
		//Segundo minimo
		if(expandidos.size() > 0) {
			minimo = expandidos.poll();
		}
		
		// Actualizar la matriz heuristica
		matrizHeuristica[(int)posicionJugador.y][(int)posicionJugador.x] = Math.max(nodoLocal.getValorH(), minimo.getValorF());
		
		nodosExpandidos++;
		return accion;
	}
	//FIN DEL ALGORITMO
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		// Comprobar cambios en los obstaculos
		actualizarInnmovable(stateObs);

		// Calcular accion a ejecutar
		return AlgoritmoRTA(stateObs); 
	}	
	
}