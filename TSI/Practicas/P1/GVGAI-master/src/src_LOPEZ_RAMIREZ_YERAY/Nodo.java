package src_LOPEZ_RAMIREZ_YERAY;

import java.util.ArrayList;

import core.game.StateObservation;
import ontology.Types.ACTIONS;
import tools.Vector2d;

public class Nodo {

	private Nodo padre;
	private Vector2d meta;
	private ArrayList<Nodo> hijos;
	private double valorG = 0;
	private double valorH = 0;
	private double valorF = 0;
	//Escala que servirá para expandir los hijos
	private Vector2d posicion;
	private ACTIONS movimiento;
	private boolean estadoFinal;
	private boolean heuristica;
	
	//CONSTRUCTOR
	public Nodo(Vector2d pos, ACTIONS acc, Nodo parent, Vector2d goal, Boolean heuristic) {
		padre = parent;
		//Ya viene escalada
		meta = goal;

		pos.x = Math.floor(pos.x);
        pos.y = Math.floor(pos.y);
        
		posicion = pos;
		
		estadoFinal = (posicion.x == meta.x && posicion.y == meta.y); //Si devuelve TRUE, guarda TRUE
		heuristica = heuristic;
		
		movimiento = acc;
		hijos = new ArrayList<Nodo>();
		
		
		if(padre != null){
			valorG = padre.getValorG() + posicion.dist(padre.getPosicion());
		}else {
			valorG = 0;
		}
		if(heuristica)
			valorH = HeuristicaManhattan();
		
		valorF = valorG + valorH;
	}
	
	//METODOS GET
	public Nodo getPadre() {return padre;}
	public Vector2d getMeta() {return meta;}
	public ArrayList<Nodo> getHijos() {return hijos;}
	public double getValorG() {return valorG;}
	public double getValorH() {return valorH;}
	public double getValorF() {return valorF;}
	public Vector2d getPosicion() {return posicion;}
	public boolean getEstadoFinal() {return estadoFinal;}
	public ACTIONS getAccion() {return movimiento;}
	
	//METODOS SET
	public void setEstadoFinal() {estadoFinal=!estadoFinal;}
	public void setPadre(Nodo p) {padre = p;}
	public void setValorH(double valor) {valorH = valor; valorF = (valorG + valor);}
	
	public boolean compararAccion(Nodo otro) {
		return false;
	}
	
	//Calcula la posicion segun la accion
	private Vector2d getPosicionJugador(ACTIONS ac) {
		Vector2d posicionJugador = new Vector2d(0,0);
		if(ac == ACTIONS.ACTION_UP)
			posicionJugador = new Vector2d(posicion.x,posicion.y-1);
		if(ac == ACTIONS.ACTION_DOWN)
			posicionJugador = new Vector2d(posicion.x,posicion.y+1);
		if(ac == ACTIONS.ACTION_LEFT)
			posicionJugador = new Vector2d(posicion.x-1,posicion.y);
		if(ac == ACTIONS.ACTION_RIGHT)
			posicionJugador = new Vector2d(posicion.x+1,posicion.y);
		
		return posicionJugador;
	}
	
	//Metodo de generacion de hijos en ORDEN
	public ArrayList<Nodo> expandirHijos(StateObservation stateObs) {		
		//Lo primero es inicializar el Array de hijos
		//Genera los hijos en orden
		ArrayList<ACTIONS> accionesDisponibles = stateObs.getAvailableActions();

		for(ACTIONS ac : accionesDisponibles) {
			hijos.add(new Nodo(getPosicionJugador(ac), ac, this, getMeta(),heuristica));		
		}
		
		return hijos;
	}
	
	//Calcula si sucesor tiene mejor valor G que el nodo actual
	public boolean mejorCaminoA(Nodo sucesor) {
		if(sucesor.getValorG() < this.getValorG())
			return true;
		
		return false;
	}
	
	//Metaheuristica - Distancia Manhattan
    private double HeuristicaManhattan() {      
        double xDiff = 0, yDiff = 0;
        
        Vector2d posOrientada = new Vector2d( (posicion.x), (posicion.y));
        
    	xDiff = Math.abs(posOrientada.x - meta.x);
        yDiff = Math.abs(posOrientada.y - meta.y);
        
        double manhattan = xDiff + yDiff;
        
        return manhattan;
    }
}
