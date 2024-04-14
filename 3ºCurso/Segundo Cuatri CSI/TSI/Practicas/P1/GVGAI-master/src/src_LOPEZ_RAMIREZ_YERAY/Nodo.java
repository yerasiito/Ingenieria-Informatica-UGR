package src_LOPEZ_RAMIREZ_YERAY;

import java.util.ArrayList;

import core.game.StateObservation;
import ontology.Types.ACTIONS;
import tools.Vector2d;

public class Nodo {

	private Nodo padre;

	private Vector2d posicion;
	private Vector2d meta;
	
	private double valorG = 0;
	private double valorH = 0;
	private double valorF = 0;

	private ACTIONS movimiento;

	private boolean estadoFinal;
	private boolean heuristica;
	
	//CONSTRUCTOR
   /**
	* Constructor de la clase Nodo
	* @param pos La posición del nodo en el espacio de búsqueda
	* @param acc La acción que se ha tomado para llegar al nodo
	* @param parent El nodo padre del nodo actual en el árbol de búsqueda
	* @param goal La posición objetivo del espacio de búsqueda
	* @param heuristic Si se va a utilizar una heurística o no en la búsqueda
	*/
	public Nodo(Vector2d pos, ACTIONS acc, Nodo parent, Vector2d goal, Boolean heuristic) {
		padre = parent;
		meta = goal; // ya viene escalada
		heuristica = heuristic;
		movimiento = acc;

		// Redondea las coordenadas de la posición a números enteros
		pos.x = Math.floor(pos.x);
		pos.y = Math.floor(pos.y);
		posicion = pos;

		// Verifica si la posición actual coincide con la posición objetivo
		estadoFinal = (posicion.x == meta.x && posicion.y == meta.y);
		
		// Calcula el valor de g, que es la distancia desde el nodo actual hasta el nodo inicial
		if (padre != null)
			valorG = padre.getValorG() + posicion.dist(padre.getPosicion());
		else
			valorG = 0;

		// Calcula el valor de h, que es la distancia estimada desde el nodo actual hasta el nodo objetivo
		if (heuristica)
			valorH = HeuristicaManhattan();

		// Calcula el valor de f, que es la suma de g y h
		valorF = valorG + valorH;
	}
	
	//METODOS GET
	public Nodo getPadre() {return padre;}
	public Vector2d getMeta() {return meta;}
	public double getValorG() {return valorG;}
	public double getValorH() {return valorH;}
	public double getValorF() {return valorF;}
	public Vector2d getPosicion() {return posicion;}
	public boolean isEstadoFinal() {return estadoFinal;}
	public ACTIONS getAccion() {return movimiento;}
	
	//METODOS SET
	public void setEstadoFinal() {estadoFinal=!estadoFinal;}
	public void setPadre(Nodo p) {padre = p;}
	public void setValorH(double valor) {valorH = valor; valorF = valorG + valor;}
	
   /**
	* Devuelve la posición resultante si el jugador se mueve en la dirección dada por la acción ac.
	* @param ac La acción que indica la dirección en la que moverse.
	* @return La posición resultante tras moverse en la dirección dada.
	*/
	private Vector2d getPosicionJugador(ACTIONS ac) {
	    Vector2d posicionJugador = new Vector2d(-1, -1);
	    switch (ac) {
	        case ACTION_UP:
	            posicionJugador = new Vector2d(posicion.x, posicion.y - 1);
	            break;
	        case ACTION_DOWN:
	            posicionJugador = new Vector2d(posicion.x, posicion.y + 1);
	            break;
	        case ACTION_LEFT:
	            posicionJugador = new Vector2d(posicion.x - 1, posicion.y);
	            break;
	        case ACTION_RIGHT:
	            posicionJugador = new Vector2d(posicion.x + 1, posicion.y);
	            break;
	        default:
	            break;
	    }
	    return posicionJugador;
	}
	
	/**
	 * Método para generar y retornar los hijos de un nodo actual en el árbol de búsqueda.
	 * 
	 * @param stateObs Estado actual del juego.
	 * @return Lista de nodos hijos generados a partir del nodo actual.
	 */
	public ArrayList<Nodo> expandirHijos(StateObservation stateObs) {
	    // Inicialización del array de hijos y obtención de las acciones disponibles.
	    ArrayList<Nodo> hijos = new ArrayList<>();
	    Vector2d posicionJugador = new Vector2d();
	    ArrayList<ACTIONS> accionesDisponibles = stateObs.getAvailableActions();

	    // Generación de los nodos hijos a partir de las acciones disponibles.
	    for (ACTIONS ac : accionesDisponibles) {
	        // Cálculo de la posición del jugador en función de la acción.
	        posicionJugador = getPosicionJugador(ac);
	        // Creación y agregación del nuevo nodo hijo a la lista de hijos.
	        hijos.add(new Nodo(posicionJugador, ac, this, meta, heuristica));
	    }

	    // Retorno de la lista de nodos hijos generados.
	    return hijos;
	}

	
	//Calcula si sucesor tiene mejor valor G que el nodo actual
	public boolean mejorCaminoA(Nodo sucesor) {
		return sucesor.getValorG() < this.getValorG();
	}
	
	//Metaheuristica - Distancia Manhattan
    private double HeuristicaManhattan() {      
        double xDiff = 0, yDiff = 0;

        // Se calcula la diferencia en la coordenada X y Y entre la posición actual y la meta
    	xDiff = Math.abs(posicion.x - meta.x);
        yDiff = Math.abs(posicion.y - meta.y);
        
        // Se devuelve la suma de las diferencias en X y Y
        return xDiff + yDiff;
    }
}
