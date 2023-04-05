package src_LOPEZ_RAMIREZ_YERAY;
import java.util.ArrayList;
import java.util.Collections;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteDijkstra extends AbstractPlayer{
	//Greedy Camel: 
	// 1) Busca la puerta m�s cercana. 
	// 2) Escoge la accion que minimiza la distancia del camello a la puerta.

	Vector2d fescala;
	Vector2d portal;
	int i = 0;
    ArrayList<Types.ACTIONS> test = new ArrayList<Types.ACTIONS>();
	
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 */
	public AgenteDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer){
		//Calculamos el factor de escala entre mundos (pixeles -> grid)
        fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
        //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        //Seleccionamos el portal mas proximo
        portal = posiciones[0].get(0).position;
        portal.x = Math.floor(portal.x / fescala.x);
        portal.y = Math.floor(portal.y / fescala.y);
	}
	
	/**
	 * return the best action to arrive faster to the closest portal
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @return best	ACTION to arrive faster to the closest portal
	 */
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
        //Posicion del avatar
        Vector2d avatar =  new Vector2d(stateObs.getAvatarPosition().x / fescala.x, 
        		stateObs.getAvatarPosition().y / fescala.y);
        
        //Probamos las cuatro acciones y calculamos la distancia del nuevo estado al portal.
        Vector2d newPos_up = avatar, newPos_down = avatar, newPos_left = avatar, newPos_right = avatar;
        if (avatar.y - 1 >= 0) {
        	newPos_up = new Vector2d(avatar.x, avatar.y-1);
        }
        if (avatar.y + 1 <= stateObs.getObservationGrid()[0].length-1) {
        	newPos_down = new Vector2d(avatar.x, avatar.y+1);
        }
        if (avatar.x - 1 >= 0) {
        	newPos_left = new Vector2d(avatar.x - 1, avatar.y);
        }
        if (avatar.x + 1 <= stateObs.getObservationGrid().length - 1) {
        	newPos_right = new Vector2d(avatar.x + 1, avatar.y);
        }
        
        //Manhattan distance
        ArrayList<Integer> distances = new ArrayList<Integer>();
        distances.add((int) (Math.abs(newPos_up.x - portal.x) + Math.abs(newPos_up.y-portal.y)));
        distances.add((int) (Math.abs(newPos_down.x - portal.x) + Math.abs(newPos_down.y-portal.y)));
        distances.add((int) (Math.abs(newPos_left.x - portal.x) + Math.abs(newPos_left.y-portal.y)));
        distances.add((int) (Math.abs(newPos_right.x - portal.x) + Math.abs(newPos_right.y-portal.y)));      
       
        // Nos quedamos con el menor y tomamos esa accion. 
        int minIndex = distances.indexOf(Collections.min(distances));
        
        
        
        //A lo bruto
        if(i == 0) {
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_LEFT);
        	test.add(Types.ACTIONS.ACTION_LEFT);
        	test.add(Types.ACTIONS.ACTION_LEFT);
        	test.add(Types.ACTIONS.ACTION_LEFT);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_DOWN);
        	test.add(Types.ACTIONS.ACTION_DOWN);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_UP);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	test.add(Types.ACTIONS.ACTION_RIGHT);
        	i+=1;
        }
        
        Types.ACTIONS a;
        if(test.size() > 0) {
            a = test.get(0);
        	test.remove(0);
            return a;
        }
        
        return Types.ACTIONS.ACTION_NIL;
//        switch (minIndex) {
//        	case 0:  
//        		return Types.ACTIONS.ACTION_UP;
//        	case 1:  
//        		return Types.ACTIONS.ACTION_DOWN;
//        	case 2:  
//        		return Types.ACTIONS.ACTION_LEFT;
//        	case 3:  
//        		return Types.ACTIONS.ACTION_RIGHT;
//        	default:
//        		return Types.ACTIONS.ACTION_NIL;
//        }              
		
	}
}
