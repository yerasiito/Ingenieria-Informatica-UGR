package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgentAStar extends AbstractPlayer{
	//Atributos de la clase
	private ArrayList<ArrayList<Boolean>> listaCerrados;
    private MyQueue listaAbiertos = new MyQueue(); //Abiertos
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>();	
	
    private boolean rutaEncontrada = false;
    private ACTIONS accion;
    
    Vector2d portalFin;
    Vector2d fescala;
  
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgentAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
        //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        //Seleccionamos el portal mas proximo
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
		rutaEncontrada = false;
		System.out.println("Jugador en: " + stateObs.getAvatarPosition().x/fescala.x + " " + stateObs.getAvatarPosition().y/fescala.y);
		System.out.println("Meta en: " + portalFin);
		
		ArrayList<Observation>[] listadoInnamovible;
		
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
		
		System.out.println("Dimensiones: " + filas + "x" + columnas );
		
		listaCerrados = new ArrayList<ArrayList<Boolean>>(filas);
		
		for(int i = 0; i < filas; i++) {
		    ArrayList<Boolean> fila = new ArrayList<Boolean>(columnas);
		    for(int j = 0; j < columnas; j++) {
		        fila.add(false);
		    }
		    listaCerrados.add(fila);
		}
		
		listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());

		for(ArrayList<Observation> obsList : listadoInnamovible) {
			for(Observation obs : obsList) {
				int posx = (int)(obs.position.x/fescala.x);
				int posy = (int)(obs.position.y/fescala.y);
				listaCerrados.get(posy).set(posx,true);
			}
		}	
		accion = ACTIONS.ACTION_NIL;
	}
	
	int nodosExpandidos = 0;
	private ArrayList<ACTIONS> AlgoritmoDijkstra(StateObservation mundo){
		Vector2d posJ = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		Nodo nodoInicial = new Nodo(posJ, ACTIONS.ACTION_NIL, null, portalFin, true);
		listaAbiertos.add(nodoInicial);	
		Nodo actual = null;

		while(!listaAbiertos.isEmpty()) { //Mientras no encuentre el objetivo	
			actual = listaAbiertos.poll();
			listaCerrados.get((int)actual.getPosicion().y).set((int)actual.getPosicion().x, true);
			
			if(actual.getEstadoFinal()) {
				nodosExpandidos++;
				camino.add(actual.getAccion());
				while(actual.getPadre() != null) {
					actual = actual.getPadre();
					camino.add(actual.getAccion());
				}
				break;
			}
			
			ArrayList<Nodo> hijos = actual.expandirHijos();
			for(Nodo n : hijos) {
				if(!listaCerrados.get((int)n.getPosicion().y).get((int)n.getPosicion().x) && !listaAbiertos.contains(n)) {
					listaAbiertos.add(n);
				}
			}
			nodosExpandidos++;
		}
		System.out.println("Nodos expandidos: " + nodosExpandidos);
		return camino;
	}
	//FIN DEL ALGORITMO
	
	int it = 0;
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		if(it == 0) {
			listaAbiertos.clear();
			camino = AlgoritmoDijkstra(stateObs);
			it++;
		}
	    
		accion = ACTIONS.ACTION_NIL;
		if(!camino.isEmpty()) {
			accion = camino.get(camino.size()-1);
			camino.remove(camino.size()-1);
		}
			
		//Averiguar camino
		//Obtener el ultimo de cerrados y borrarlo
		return accion;
        
	}	
	
}