package src_LOPEZ_RAMIREZ_YERAY;

import java.util.Comparator;
import java.util.PriorityQueue;
import ontology.Types.ACTIONS;

/**
 * @brief Modificacion de la cola con prioridad original 
 * para respetar el orden de coste y generacion de nodos
 * @author yerasito
 *
 */
public class PriorityQueueNodo extends PriorityQueue<Nodo>{
	private static final long serialVersionUID = 8780424473060020311L;
	
	//Constructor de la cola
	//Usa el comparador modificado
	public PriorityQueueNodo() {
		super(new ComparadorNodo());
	}
	
	/**
	 * @brief Modificacion del metodo compare en la cola
	 * El orden es: valorF > valorG > Orden de generacion
	 * @author yerasito
	 *
	 */
	private static class ComparadorNodo implements Comparator<Nodo> {
		/**
		 * Compara dos nodos basándose en sus valores de f, g y en la prioridad de la acción.
		 * @param n1 primer nodo a comparar
		 * @param n2 segundo nodo a comparar
		 * @return -1 si n1 es menor que n2, 0 si son iguales, 1 si n1 es mayor que n2.
		 */
		@Override
	    public int compare(Nodo n1, Nodo n2) {
			// Comparar valores de f
			int cmp = Double.compare(n1.getValorF(), n2.getValorF());
	        if (cmp != 0)
	        	return cmp;

	        // Comparar valores de g
	        cmp = Double.compare(n1.getValorG(), n2.getValorG());
        	if (cmp != 0)
	            return cmp;

        	// Comparar prioridad de la accion
        	return Integer.compare(getPriority(n1.getAccion()), getPriority(n2.getAccion()));
		}
		
		/**
		 * Devuelve la prioridad numérica de una acción dada para romper empates entre nodos con el mismo valor F y valor G.
		 * Las acciones tienen una prioridad asignada basada en su orden de generación. El orden es:
		 * UP > DOWN > LEFT > RIGHT
		 * @param action la acción para la que se quiere conocer la prioridad numérica
		 * @return la prioridad numérica asignada a la acción dada
		 */
	    private int getPriority(ACTIONS action) {
	        return switch (action) {
		        case ACTION_UP -> 1;
		        case ACTION_DOWN -> 2;
		        case ACTION_LEFT -> 3;
		        case ACTION_RIGHT -> 4;
		        default -> Integer.MAX_VALUE;
	        };
	    }
}
	/**
	 * Sobrescribe el método contains de la clase padre PriorityQueueNodo para buscar un Nodo
	 * que tenga la misma posición que el Nodo dado como argumento.
	 * @param o el objeto que se desea buscar en el conjunto
	 * @return true si el objeto se encuentra en el conjunto, false en caso contrario
	 */
	@Override
    public boolean contains(Object o) {
		// Verifica que el objeto a buscar sea de tipo Nodo
	    if (!(o instanceof Nodo)) {
	        return false;
	    }
	    
	    // Convierte el objeto a un Nodo
    	boolean esta = false;
    	Nodo nodo = (Nodo) o;
        
        // Busca un Nodo en el conjunto que tenga la misma posición que el Nodo dado
    	for(Nodo n : this) {
    		if(n.getPosicion().x == nodo.getPosicion().x && n.getPosicion().y == nodo.getPosicion().y) {
    			esta = true;
    		}
    	}
        // Retorna true si se encontró el Nodo, false en caso contrario
    	return esta;
    }
}
