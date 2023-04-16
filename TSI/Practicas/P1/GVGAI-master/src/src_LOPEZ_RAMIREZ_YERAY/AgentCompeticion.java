package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgentCompeticion extends AbstractPlayer{
	//Atributos de la clase
	private ArrayList<ArrayList<Boolean>> listaCerrados;
    private ColaNodo listaAbiertos = new ColaNodo(); //Abiertos
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); //Hijos en la ejecucion
	ArrayList<Observation>[] listadoInnamovible; //muros y trampas
	ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>();	
	private int nodosExpandidos = 0;
    private ACTIONS accion;
    
    Vector2d portalFin;
    Vector2d fescala;
  
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgentCompeticion(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
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
		
		inicializarCerrados(stateObs);
		
		//Actualiza mapa de muros
		listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listadoInnamovible[0] = new ArrayList<Observation>(); //Para cambiar el tamaño
		actualizarInnmovable(stateObs) ;
	}

	private ArrayList<ACTIONS> Algoritmo(StateObservation mundo){
		nodosExpandidos = 0;
		Vector2d posJ = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		Nodo nodoInicial = new Nodo(posJ, ACTIONS.ACTION_NIL, null, portalFin, true);
		
		listaAbiertos.add(nodoInicial);	
		Nodo actual;
		boolean estaAbiertos = false, estaCerrados = false;
		while(!listaAbiertos.isEmpty()) { //Mientras no encuentre el objetivo	
			actual = listaAbiertos.poll();
			listaCerrados.get((int)actual.getPosicion().y).set((int)actual.getPosicion().x, true); //Lo mete en cerrados poniendolo a true
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
//		System.out.println("Nodos expandidos: " + nodosExpandidos);
		return camino;
	}
	//FIN DEL ALGORITMO
	
	private void inicializarCerrados(StateObservation stateObs) {
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
		listaCerrados = new ArrayList<ArrayList<Boolean>>(filas);
		
		for(int i = 0; i < filas; i++) {
		    ArrayList<Boolean> fila = new ArrayList<Boolean>(columnas);
		    for(int j = 0; j < columnas; j++) {
		        fila.add(false);
		    }
		    listaCerrados.add(fila);
		}
	}
	
	
    private boolean actualizarInnmovable(StateObservation stateObs) {
    	ArrayList<Observation>[] nuevoInmovable = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
    	boolean cambios = nuevoInmovable[0].size() != listadoInnamovible[0].size() || nuevoInmovable[1].size() != listadoInnamovible[1].size();
    	if(cambios) {
			inicializarCerrados(stateObs);
			listadoInnamovible = nuevoInmovable;
			for(ArrayList<Observation> obsList : nuevoInmovable) {
				for(Observation obs : obsList) {
					int posx = (int)(obs.position.x/fescala.x);
					int posy = (int)(obs.position.y/fescala.y);
					listaCerrados.get(posy).set(posx,true);
				}
			}
			listaAbiertos.clear();
			camino.clear();
		}
		
		return cambios;
    }
    
    int it = 0;
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
		
		if(it == 0 || actualizarInnmovable(stateObs)) {
			camino = Algoritmo(stateObs);
			it++;
		}
	    
		if(!camino.isEmpty()) {
			accion = camino.get(camino.size()-1);
			camino.remove(camino.size()-1);
		}
			
		return accion; 
	}	
	
}