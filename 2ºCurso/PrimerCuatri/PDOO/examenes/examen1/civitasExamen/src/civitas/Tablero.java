/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

public class Tablero {
    private static final int TAMANIOTABLERO = 20;
    private boolean porSalida;
    private ArrayList<Casilla> casillas;
    
    public Tablero(){
        casillas = new ArrayList<>();
        porSalida = false;
    }
       
    private boolean correcto(int numCasilla){
        boolean esCorrecto = false;
        if(numCasilla > -1 && numCasilla < casillas.size())
            esCorrecto = true;
        
        return esCorrecto;
    }
    
    boolean computarPasoPorSalida (){
        boolean copia = porSalida;
        porSalida = false;
        return copia;
    }
    
    void añadeCasilla(Casilla casilla){
        casillas.add(casilla);
    }
    
    public Casilla getCasilla(int numCasilla){
        if(correcto(numCasilla))
            return casillas.get(numCasilla);
        else
            return null;
    }
    
    public ArrayList<Casilla> getCasillas() {
        return casillas;
    }
    
    private int getPosicionSiguienteEstacion(int posCalle){
        int d = -1;
        boolean encontrada = false;
        if(getCasilla(posCalle).getTipo() == TipoCasilla.CALLE)
            for(int i = posCalle; i < TAMANIOTABLERO && !encontrada; i++)
                if(casillas.get(i).getTipo() == TipoCasilla.ESTACION){
                    d=i;
                    encontrada = true;
                }
        return d;
    }
    
    private void añadirEstacionADiario(int posCalle, int posEstacion){
        if(posEstacion > -1){
            int d = posEstacion - posCalle;
            Diario.getInstance().ocurreEvento("La calle " + getCasilla(posCalle).getNombre()
                            + "(" + posCalle + ")"
                            + " se encuentra a " + d + " casillas de la estacion "
                            + getCasilla(posEstacion).getNombre()
                            + "(" + posEstacion + ")");   
        }
        else{
            Diario.getInstance().ocurreEvento("La calle " + getCasilla(posCalle).getNombre()
                + "(" + posCalle + ")" + " no tiene cerca ninguna estación");
        }
    }
    
    void calcularFactoresComunicacion(){
        for(int i = 0; i < TAMANIOTABLERO; i++)
            calcularFactorComunicacion(i, getPosicionSiguienteEstacion(i));
    }
    
    private void calcularFactorComunicacion(int posCalle, int posEstacion){
        float factor = 0;
        int d = posEstacion - posCalle;
        Casilla calle = getCasilla(posCalle);
        if(calle.getTipo() == TipoCasilla.CALLE){   
            if(posEstacion != -1){
                Casilla casillaEstacion = getCasilla(posEstacion);
                Estacion estacion = casillaEstacion.getEstacion();
                switch(estacion.getTipo()){
                    case CERCANIAS:
                        factor = 1/(d*10f);
                        break;
                    case LARGADISTANCIA:
                        factor = 2/(d*10f);
                        break;
                    case MULTIPLE:
                        factor = 3/(d*10f);
                }
                calle.setFactorComunicacion(factor);
            }
        añadirEstacionADiario(posCalle, posEstacion);
        }
    }
    
    int nuevaPosicion (int actual, int tirada){
        int nueva = (actual+tirada)%TAMANIOTABLERO;
        if(nueva != actual+tirada){
            porSalida = true;
        }
        return nueva;
    }
}
