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
    static final int NUMEROJUGADORES = 4;
    private int indiceJugadorActual;
    private ArrayList<Jugador> jugadores;
    private Tablero tablero;
    private MazoSorpresas mazo;
    private GestorEstados gestorEstado;
    private EstadoJuego estadoJuego;
    private Dado dado = Dado.getInstance();
    
    private void init(){
        indiceJugadorActual = 0;
        jugadores = new ArrayList<Jugador>();
        tablero = new Tablero();
        mazo = new MazoSorpresas();
        gestorEstado = new GestorEstados();
    }
    
    public CivitasJuego(ArrayList<String> nombres, boolean debug){
        init();
        //Inicializar jugadores
        jugadores = new ArrayList<>();
        for(int i = 0; i < NUMEROJUGADORES; i++){
            Jugador nuevo = new Jugador(nombres.get(i));
            jugadores.add(nuevo);
        }
        //Fijar estado inicial
        estadoJuego = gestorEstado.estadoInicial();

        //Poner el dado en modo debug(o no)
        Dado.getInstance().setDebug(debug);
        
        //Se sortea el jugador que empieza
        indiceJugadorActual = dado.quienEmpieza(NUMEROJUGADORES);
        
        mazo = new MazoSorpresas(debug);
        
        inicializaTablero(mazo);
        inicializaMazoSorpresas();
    }

    public void inicializaTablero(MazoSorpresas mazo){
        //PARTE INFERIOR DEL TABLERO
        tablero.aniadeCasilla(new Casilla("Salida")); //SALIDA
        
        tablero.aniadeCasilla(new Casilla("Acera del Darro", 400, 250, 200)); //CALLE
        
        tablero.aniadeCasilla(new Casilla("Rodrigo de Triana", 500, 300, 250)); //CALLE
        
        tablero.aniadeCasilla(new Casilla("SUERTE", mazo)); //SORPRESA
        
        tablero.aniadeCasilla(new Casilla("Cuesta de Gomerez", 600, 400, 300)); //CALLE;
        
        //PRIMER LATERAL
        tablero.aniadeCasilla(new Casilla("Albaicin", 750, 500, 400)); //CALLE);
        
        tablero.aniadeCasilla(new Casilla("SUERTE", mazo)); //SORPRESA
        
        tablero.aniadeCasilla(new Casilla("Oficios", 1000, 750, 500)); //CALLE

        tablero.aniadeCasilla(new Casilla("Recogidas", 1000, 750, 500)); //CALLE

        tablero.aniadeCasilla(new Casilla("Parque FuenteNueva")); //DESCANSO
        
        //PARTE SUPERIOR
        
        tablero.aniadeCasilla(new Casilla("Camino del Sacromonte", 1250, 800, 600)); //CALLE
               
        tablero.aniadeCasilla(new Casilla("Calle Real de la Alhambra", 1500, 900, 750)); //CALLE
        
        tablero.aniadeCasilla(new Casilla("SUERTE", mazo)); //SORPRESA
                
        tablero.aniadeCasilla(new Casilla("Almona del Campillo", 1500, 900, 750)); //CALLE

        tablero.aniadeCasilla(new Casilla("Caldederia", 1600, 950, 800)); //CALLE
        
        //SEGUNDO LATERAL
        tablero.aniadeCasilla(new Casilla("Camino de Ronda", 1750, 1000, 900)); //CALLE
        
        tablero.aniadeCasilla(new Casilla("SUERTE", mazo)); //SORPRESA
        
        tablero.aniadeCasilla(new Casilla("Gran Via de Colon", 2000, 1250, 1100)); //CALLE
        
        tablero.aniadeCasilla(new Casilla("Angel Gabinet", 2500, 1500, 1250)); //CALLE

        tablero.aniadeCasilla(new Casilla("Horno de Oro", 3000, 2000, 1500)); //CALLE
    }
    
    public void inicializaMazoSorpresas(){
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

    public MazoSorpresas getMazo() {
        return mazo;
    }
    
    public void PasarTurno(){
        indiceJugadorActual = indiceJugadorActual++ % NUMEROJUGADORES;
    }
    
    public ArrayList<Jugador> Ranking(){
        Collections.sort(jugadores);
        return jugadores;
    }
    
    public OperacionJuego siguientePaso(){
        //pendiente
        return null;
    }
    
    public void siguientePasoCompletado(OperacionJuego operacion){
        gestorEstado.siguienteEstado(getJugadorActual(), estadoJuego, operacion);
    }
    
    public boolean comprar(){
       //pendiente
       return true; 
    }
    
    public boolean construirCasa(int ip){
        return getJugadorActual().construirCasa(ip);
    }
        
    public boolean construirHotel(int ip){
        return getJugadorActual().construirHotel(ip);
    }
    
    public void ContabilizarPasosPorSalida(){
        if(tablero.computarPasoPorSalida())
            getJugadorActual().pasaPorSalida();
    }
    
    public boolean finalDelJuego(){
        boolean fin = false;
        for(int i = 0; i < NUMEROJUGADORES && !fin; i++)
            if(jugadores.get(i).enBancarrota())
                fin = true;
        
        return fin;
    }
}