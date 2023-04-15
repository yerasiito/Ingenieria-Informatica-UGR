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
    private myQueue listaAbiertos = new myQueue(); //Abiertos
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>();	
	private ArrayList<ArrayList<Double>> matrizHeuristica;
	
    private ACTIONS accion;
    
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
		
		ArrayList<Observation>[] listadoInnamovible;
		
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

		for(ArrayList<Observation> obsList : listadoInnamovible) {
			for(Observation obs : obsList) {
				int posx = (int)(obs.position.x/fescala.x);
				int posy = (int)(obs.position.y/fescala.y);
				listaCerrados.get(posy).set(posx,true);
			}
		}
		
		for(int i = 0; i < matrizHeuristica.size(); i++) {
			for(int j = 0; j < matrizHeuristica.get(0).size(); j++) {
				matrizHeuristica.get(i).set(j, HeuristicaManhattan(j,i));
			}
		}
		
		for(ArrayList<Double> f : matrizHeuristica) {
			System.out.println();
			for(int i = 0; i < f.size(); i++)
				System.out.print(f.get(i) + "\t");
		}
		System.out.println();
		
		accion = ACTIONS.ACTION_NIL;
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
	
	int nodosExpandidos = 0;
	private ArrayList<ACTIONS> AlgoritmoAstar(StateObservation mundo){
		Vector2d posJ = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		Nodo nodoInicial = new Nodo(posJ, ACTIONS.ACTION_NIL, null, portalFin, true);
		
		listaAbiertos.add(nodoInicial);	
		Nodo actual;
		boolean estaAbiertos = false, estaCerrados = false;
		
		while(!listaAbiertos.isEmpty()) { //Mientras no encuentre el objetivo	
			actual = listaAbiertos.poll();
			listaCerrados.get((int)actual.getPosicion().y).set((int)actual.getPosicion().x, true); //Lo mete en cerrados poniendolo a true
			Double dis = matrizHeuristica.get((int)actual.getPosicion().y).get((int)actual.getPosicion().x);
			matrizHeuristica.get((int)actual.getPosicion().y).set((int)actual.getPosicion().x, dis+1);
			
			if(actual.getEstadoFinal()) { //Si es el estado final calcula el camino
				nodosExpandidos++;
				camino.add(actual.getAccion());
				while(actual.getPadre() != null) {
					actual = actual.getPadre();
					camino.add(actual.getAccion());
				}
				break;
			}
			
			ArrayList<Nodo> hijos = actual.expandirHijos(mundo);
			for(Nodo n : hijos) {
				estaCerrados = listaCerrados.get((int)n.getPosicion().y).get((int)n.getPosicion().x);
				estaAbiertos = listaAbiertos.contains(n);
				
				if(estaCerrados && actual.mejorCaminoA(n)) {
					listaCerrados.get((int)n.getPosicion().y).set((int)n.getPosicion().x, false);
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
				else if(!estaCerrados && !estaAbiertos) {
					listaAbiertos.add(n);
				}
				else if(estaAbiertos && actual.mejorCaminoA(n)) {
					//Actualiza el nodo con el sucesor quitando el actual y metiendo el mejor
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
			}
			nodosExpandidos++;
		}
		System.out.println("Nodos expandidos: " + nodosExpandidos);
		return camino;
	}
	//FIN DEL ALGORITMO
	
	boolean entra = true;
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		if(entra) {
			listaAbiertos.clear();
			camino = AlgoritmoAstar(stateObs);
			entra = false;
			System.out.println("\nTras ejecutar");
			for(ArrayList<Double> f : matrizHeuristica) {
				System.out.println();
				for(int i = 0; i < f.size(); i++)
					System.out.print(f.get(i) + "\t");
			}
			System.out.println();
		}
		
		accion = ACTIONS.ACTION_NIL; //Por defecto es nil
		if(!camino.isEmpty()) {
			accion = camino.get(camino.size()-1);
			camino.remove(camino.size()-1);
		}
			
		return accion; 
	}	
	
}