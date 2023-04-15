package src_LOPEZ_RAMIREZ_YERAY;

import java.util.Comparator;
import java.util.PriorityQueue;

import ontology.Types.ACTIONS;

public class ColaNodo extends PriorityQueue<Nodo>{
	private static final long serialVersionUID = 8780424473060020311L;
	
	public ColaNodo() {
		super(new Comparador());
	}
	
	private static class Comparador implements Comparator<Nodo> {

		//Prioridad valorF>valorG>Orden de generacion
		@Override
	    public int compare(Nodo n1, Nodo n2) {
	        double f1 = n1.getValorF();
	        double f2 = n2.getValorF();
	        if (f1 < f2)
	        	return -1;
	        else if (f1 > f2)
	        	return 1;
	        else
	        {
	        	double g1 = n1.getValorG();
	        	double g2 = n2.getValorG();
	  	        
	        	if (g1 < g2)
		            return -1;
		        else if (g1 > g2)
		            return 1;
		        else
		        {  
		        	int priority1 = getPriority(n1.getAccion());
		        	int priority2 = getPriority(n2.getAccion());	    	        
		        	return Integer.compare(priority1, priority2);
		        }
	        }
		}
		
		//Prioridad de generacion: UP, DOWN, LEFT, RIGHT
	    private int getPriority(ACTIONS action) {
	        switch (action) {
	            case ACTION_UP:
	                return 1;
	            case ACTION_DOWN:
	                return 2;
	            case ACTION_LEFT:
	                return 3;
	            case ACTION_RIGHT:
	                return 4;
	            default:
	                return Integer.MAX_VALUE;
	        }
	    }
}
	//Contiene si tiene las mismas coordenadas
	@Override
    public boolean contains(Object o) {
	    if (!(o instanceof Nodo)) {
	        return false;
	    }
	    
	    Nodo nodo = (Nodo) o;
        // Aquí se escribe el código para sobrescribir el método
    	boolean esta = false;
    	for(Nodo n : this) {
    		if(n.getPosicion().x == nodo.getPosicion().x && n.getPosicion().y == nodo.getPosicion().y) {
    			esta = true;
    		}
    	}
    	
    	
    	return esta;
    }
}
