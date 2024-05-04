/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;
import java.util.Collections;
/**
 *
 * @author ylope
 */
public class CivitasJuego {
    static final int TAMANIOTABLERO = 20;
    private int indiceJugadorActual;
    private ArrayList<Jugador> jugadores;
    private Tablero tablero;
    private MazoSorpresas mazo;
    private GestorEstados gestorEstado;
    private EstadoJuego estadoJuego;
    private final Dado dado = Dado.getInstance();
    
    private void init(){
        indiceJugadorActual = 0;
        jugadores = new ArrayList<>();
        tablero = new Tablero();
        mazo = new MazoSorpresas();
        gestorEstado = new GestorEstados();
        estadoJuego = null;
    }
    
    public CivitasJuego(ArrayList<String> nombres, boolean debug){
        init();
        //Inicializar jugadores
        jugadores = new ArrayList<>();
        for(int i = 0; i < nombres.size(); i++){
            Jugador nuevo = new Jugador(nombres.get(i));
            jugadores.add(nuevo);
        }
        //Fijar estado inicial
        estadoJuego = gestorEstado.estadoInicial();

        //Poner el dado en modo debug(o no)
        Dado.getInstance().setDebug(debug);
        
        //Se sortea el jugador que empieza
        indiceJugadorActual = dado.quienEmpieza(nombres.size());
        
        mazo = new MazoSorpresas(debug);
        
        inicializaTablero(mazo);
        inicializaMazoSorpresas();
    }

    private void inicializaTablero(MazoSorpresas mazo){
        //PARTE INFERIOR DEL TABLERO
        tablero.añadeCasilla(new Casilla(TipoCasilla.DESCANSO, "Salida")); //SALIDA
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE,"Acera del Darro", 400, 250, 200)); //CALLE
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE,"Rodrigo de Triana", 500, 300, 250)); //CALLE
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.SORPRESA, "SUERTE", mazo)); //SORPRESA
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Cuesta de Gomerez", 600, 400, 300)); //CALLE;
        
        //PRIMER LATERAL
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Albaicin", 750, 500, 400)); //CALLE);
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.SORPRESA, "SUERTE", mazo)); //SORPRESA
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Oficios", 1000, 750, 500)); //CALLE

        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Recogidas", 1000, 750, 500)); //CALLE

        tablero.añadeCasilla(new Casilla(TipoCasilla.DESCANSO, "Parque FuenteNueva")); //DESCANSO
        
        //PARTE SUPERIOR
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Camino del Sacromonte", 1250, 800, 600)); //CALLE
               
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Calle Real de la Alhambra", 1500, 900, 750)); //CALLE
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.SORPRESA, "SUERTE", mazo)); //SORPRESA
                
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Almona del Campillo", 1500, 900, 750)); //CALLE

        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Caldederia", 1600, 950, 800)); //CALLE
        
        //SEGUNDO LATERAL
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Camino de Ronda", 1750, 1000, 900)); //CALLE
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.SORPRESA, "SUERTE", mazo)); //SORPRESA
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Gran Via de Colon", 2000, 1250, 1100)); //CALLE
        
        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Angel Gabinet", 2500, 1500, 1250)); //CALLE

        tablero.añadeCasilla(new Casilla(TipoCasilla.CALLE, "Horno de Oro", 3000, 2000, 1500)); //CALLE
    }
    
    private void inicializaMazoSorpresas(){
        mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR, "Te han robado la tarjeta de credito en el Almanjayar y pierdes 1000€ en una transferencia por una tele",-1000));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR, "Te inspeccionan por monopolio y debes sobornar al estado para no acabar en la cárcel. Pagas 1500€",-1500));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR, "Has ganado la quiniela, tantas horas de futbol no fueron en vano. Ganas 1000€",1000));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL, "Inviertes 500€ en TrollCoin y su valor se cuatriplica al dia siguiente. Ganas 1500€",1500));
        
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL, "La luz ha subido tanto que los inquilinos no pagan. Pierdes 150€ por propiedad",-150));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL, "Un terremoto sacude la ciudad(y a tus propiedades). Pierdes 250€ por propiedad",-250));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL, "Ayudas a una persona y resulta ser un youtuber, te haces una foto y se hace viral. Ganas 250€ por propiedad",250));
        mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL, "El FBI irrumpe en tus propiedades por presunto soborno y te llevan a juicio. "
                                                            + "No sabes como, ganas el juicio y te compensan 150€ por daños en tus propiedades",150));
        
    }
    
    public int getIndiceJugadorActual(){
        return indiceJugadorActual;
    }
    
    public Jugador getJugadorActual(){
        return jugadores.get(indiceJugadorActual);
    }
    
    public ArrayList<Jugador> getJugadores(){
        return jugadores;
    }
    
    public Tablero getTablero(){
        return tablero;
    }
    
    private void PasarTurno(){
        indiceJugadorActual = (indiceJugadorActual+1)%jugadores.size();
    }
    
    private void avanzaJugador(){
        Jugador jugadorActual = getJugadorActual();
        int posicionActual = jugadorActual.getCasillaActual();
        int tirada = dado.tirar();
        int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);
        Casilla casilla= tablero.getCasilla(posicionNueva);
        ContabilizarPasosPorSalida();
        jugadorActual.moverACasilla(posicionNueva);
        casilla.recibeJugador(indiceJugadorActual, jugadores);
    }
    
    //Visibilidad Modificada, era Private
    public ArrayList<Jugador> Ranking(){
        Collections.sort(jugadores);
        return jugadores;
    }
    
    public OperacionJuego siguientePaso(){
        Jugador jugadorActual=getJugadorActual();
        OperacionJuego operacion = gestorEstado.siguienteOperacion(jugadorActual, estadoJuego);
        if(operacion==OperacionJuego.PASAR_TURNO){
            PasarTurno();
            siguientePasoCompletado(operacion);
        }
        else if(operacion==OperacionJuego.AVANZAR){
            avanzaJugador();
            siguientePasoCompletado(operacion);
        }
        
        return operacion;
    }
    
    public void siguientePasoCompletado(OperacionJuego operacion){
        estadoJuego = gestorEstado.siguienteEstado(getJugadorActual(), estadoJuego, operacion);
    }
    
    public boolean comprar(){       
       Jugador jugadorActual = getJugadorActual();
       int numCasillaActual = jugadorActual.getCasillaActual();
       Casilla casilla = tablero.getCasilla(numCasillaActual);
       boolean res = jugadorActual.comprar(casilla);
       
       return res; 
    }
    
    public boolean construirCasa(int ip){
        return getJugadorActual().construirCasa(ip);
    }
        
    public boolean construirHotel(int ip){
        return getJugadorActual().construirHotel(ip);
    }
    
    private void ContabilizarPasosPorSalida(){
        if(tablero.computarPasoPorSalida())
            getJugadorActual().pasaPorSalida();
    }
    
    public boolean finalDelJuego(){
        boolean fin = false;
        for(int i = 0; i < jugadores.size() && !fin; i++)
            if(jugadores.get(i).enBancarrota())
                fin = true;
        
        return fin;
    }
}