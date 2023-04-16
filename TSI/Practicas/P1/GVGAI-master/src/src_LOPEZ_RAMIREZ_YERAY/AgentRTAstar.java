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
	private ArrayList<ArrayList<Boolean>> listaCerrados;
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	private ArrayList<ArrayList<Double>> matrizHeuristica;
	
    Vector2d portalFin;
    Vector2d fescala;
  
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgentRTAstar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
        //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        //Seleccionamos el portal mas proximo
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
		System.out.println("Jugador en: " + stateObs.getAvatarPosition().x/fescala.x + " " + stateObs.getAvatarPosition().y/fescala.y);
		System.out.println("Meta en: " + portalFin);
		
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
		
		System.out.println("Dimensiones: " + filas + "x" + columnas );
		
		listaCerrados = new ArrayList<ArrayList<Boolean>>(filas);
		matrizHeuristica = new ArrayList<ArrayList<Double>>(filas);
		
		for(int i = 0; i < filas; i++) {
		    ArrayList<Boolean> fila = new ArrayList<Boolean>(columnas);
		    ArrayList<Double> filaD = new ArrayList<Double>(columnas);
		    for(int j = 0; j < columnas; j++) {
		        fila.add(false); //Inicializa a false
		        filaD.add(0.0); //Inicializa con las distancias
		    }
		    listaCerrados.add(fila);
		    matrizHeuristica.add(filaD);
		}
		
		listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listadoInnamovible[0] = new ArrayList<Observation>(); //Para cambiar el tamaño
		actualizarInnmovable(stateObs) ;
		
		for(int i = 0; i < matrizHeuristica.size(); i++) {
			for(int j = 0; j < matrizHeuristica.get(0).size(); j++) {
				matrizHeuristica.get(i).set(j, HeuristicaManhattan(j,i));
			}
		}		
	}
	
    private void actualizarInnmovable(StateObservation stateObs) {
    	ArrayList<Observation>[] nuevoInmovable = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
    	
		if(nuevoInmovable[0].size() != listadoInnamovible[0].size()) {
			listadoInnamovible = nuevoInmovable;
			for(ArrayList<Observation> obsList : nuevoInmovable) {
				for(Observation obs : obsList) {
					int posx = (int)(obs.position.x/fescala.x);
					int posy = (int)(obs.position.y/fescala.y);
					listaCerrados.get(posy).set(posx,true);
				}
			}
		}
    }
    
	//Metaheuristica - Distancia Manhattan
    private double HeuristicaManhattan(int x, int y) {      
        double xDiff = 0, yDiff = 0;
        
        Vector2d pos = new Vector2d(x, y);
        if(listaCerrados.get(y).get(x)) {
        	pos.x = Double.NaN;
        	pos.y = Double.NaN;
        }
        
    	xDiff = Math.abs(pos.x - portalFin.x);
        yDiff = Math.abs(pos.y - portalFin.y);
        
        double manhattan = xDiff + yDiff;
        
        return manhattan;
    }
	
	int nodosExpandidos = 1;
	private ACTIONS AlgoritmoRTA(StateObservation mundo){
		ACTIONS accion;
		Vector2d posJ = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		Nodo nodoLocal = new Nodo(posJ, ACTIONS.ACTION_NIL, null, portalFin, true);		
		double valorH = matrizHeuristica.get((int)posJ.y).get((int)posJ.x);
		nodoLocal.setValorH(valorH);
		
		ArrayList<Nodo> hijos = nodoLocal.expandirHijos(mundo);
		ColaNodo expandidos = new ColaNodo();
		for(Nodo n : hijos) { //Obtenga las F
			//Si es el nodo final, lo devuelve
			if(n.getEstadoFinal()) {
				nodosExpandidos++;
				System.out.println("Nodos expandidos: " + nodosExpandidos);
				return n.getAccion();
			}
			//Si no es un obstaculo lo añade a expandidos
			if(!listaCerrados.get((int)n.getPosicion().y).get((int)n.getPosicion().x)) {
				valorH = matrizHeuristica.get((int)n.getPosicion().y).get((int)n.getPosicion().x);
				n.setValorH(valorH);
				expandidos.add(n);
			}
		}
		//Obtiene 2º minimo
		Nodo minimo = null;
		
		//Primer minimo
		minimo = expandidos.poll();
		accion = minimo.getAccion();
		
		//Segundo minimo
		if(expandidos.size() > 0) {
			minimo = expandidos.poll();
		}

		matrizHeuristica.get((int)posJ.y).set((int)posJ.x, Math.max(nodoLocal.getValorH(), minimo.getValorF()));
		nodosExpandidos++;
		return accion;
	}
	//FIN DEL ALGORITMO
	
	int it = 0;
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		ACTIONS accion = ACTIONS.ACTION_NIL;
		actualizarInnmovable(stateObs);
		accion = AlgoritmoRTA(stateObs);

		return accion; 
	}	
	
}