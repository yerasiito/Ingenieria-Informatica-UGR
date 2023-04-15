package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

/**
 * 
 * Implementación de A*
 * 
 *  Est_abiertos.insertar(Estado inicial)
    Actual Est_abiertos.primero()
    mientras no es_final?(Actual) y no Est_abiertos.vacía?() hacer
        Est_abiertos.borrar_primero()
        Est_cerrados.insertar(Actual)
        hĳos generar_sucesores (Actual)
        hĳos tratar_repetidos (Hĳos, Est_cerrados, Est_abiertos)
        Est_abiertos.insertar(Hĳos)
        Actual Est_abiertos.primero()
    fin
 * 
 */
public class AgentDijkstra extends AbstractPlayer{
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
	public AgentDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
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
	
//		for(int i = 0; i < listaCerrados.size(); i++) {
//		    for(int j = 0; j < listaCerrados.get(i).size(); j++) {
//		        System.out.print(listaCerrados.get(i).get(j) + "\t");
//		    }
//		    System.out.println();
//		}		
		accion = ACTIONS.ACTION_NIL;
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
	int nodosExpandidos = 0;
	private ArrayList<ACTIONS> AlgoritmoDijkstra(StateObservation mundo){
		Vector2d posJ = new Vector2d(mundo.getAvatarPosition().x/fescala.x, mundo.getAvatarPosition().y/fescala.y);
		Nodo nodoInicial = new Nodo(posJ, ACTIONS.ACTION_NIL, null, portalFin);
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
//		long startTime = System.currentTimeMillis();
		if(it == 0) {
			listaAbiertos.clear();
			camino = AlgoritmoDijkstra(stateObs);
			it++;
		}
//		long endTime = System.currentTimeMillis();
//		long elapsedTime = endTime - startTime;
//		System.out.println("Tiempo de ejecución: " + elapsedTime + " milisegundos.");
	    
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