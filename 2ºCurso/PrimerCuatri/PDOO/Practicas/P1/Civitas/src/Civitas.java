/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package civitas;

/**
 *
 * @author ylope
 */
public class Civitas {
    static final int NUMEROJUGADORES = 4;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //TEST 1
        System.out.println("TEST 1");
        int n = 0, zero = 0, uno = 0, dos = 0, tres = 0, otro = 0;
        for(int i = 0; i < 100; i++){
            n = Dado.getInstance().quienEmpieza(NUMEROJUGADORES);
            if(n == 0)
                zero++;
            else if(n == 1)
                uno++;
            else if(n == 2)
                dos++;
            else if(n == 3)
                tres++;
            else
                otro++;
        }
        System.out.println("Empieza jugador 0: " + zero);
        System.out.println("Empieza jugador 1: " + uno);
        System.out.println("Empieza jugador 2: " + dos);
        System.out.println("Empieza jugador 3: " + tres);
        System.out.println("Errores: " + otro);
        
        //TEST 2
        System.out.println("\nTEST 2");
        Dado.getInstance().setDebug(true);
        int tirada = 0;
        System.out.println("Tiradas de Dado en Modo Debug");
        for(int i = 0; i < 10; i++){
            tirada = Dado.getInstance().tirar();
            System.out.print(tirada + " ");
        }
        Dado.getInstance().setDebug(false);
        System.out.println("\nTiradas de Dado en Modo Normal");
        for(int i = 0; i < 10; i++){
            tirada = Dado.getInstance().tirar();
            System.out.print(tirada + " ");
        }
        
        //TEST 3
        System.out.println("\n\nTEST 3");
        System.out.println("El ultimo resultado fue: " + Dado.getInstance().getUltimoResultado());
        
        //TEST 4
        System.out.println("\n\nTEST 4");
        System.out.println("Enumerado TipoCasilla: " + TipoCasilla.CALLE);
        System.out.println("Enumerado TipoSopresa: " + TipoSorpresa.PAGARCOBRAR);
        System.out.println("Enumerado EstadosJuego: " + EstadosJuego.INICIO_TURNO);
        
        //TEST 5
        System.out.println("\n\nTEST 5");
        final int NUMEROCALLES = 3;
        Tablero t = new Tablero();
        
        Casilla casilla1 = new Casilla(TipoCasilla.CALLE,"Gran Via", 100f, 200f, 500f);
        Casilla casilla2 = new Casilla(TipoCasilla.CALLE,"Real", 200f, 500f, 1000f);
        Casilla casilla3 = new Casilla(TipoCasilla.CALLE,"Andalucia", 500f, 1000f, 2000f);        
        
        t.aniadeCasilla(casilla1);
        t.aniadeCasilla(casilla2);
        t.aniadeCasilla(casilla3);
        
        for(int i = 0; i < NUMEROCALLES; i++)
            System.out.println(t.getCasilla(i).toString());
        
        //TEST 6
        System.out.println("\n\nTEST 6");
        float auxf = 0, cara = 0, barata = 999999999, media = 0;
        int indiceCara = -1, indiceBarata = -1;
        for(int i = 0; i < NUMEROCALLES; i++){
            auxf = t.getCasilla(i).getPrecioCompra();
            if(auxf > cara){ //es la mas cara
                cara = auxf;
                indiceCara = i;
            }
            if(auxf < barata){ //es la mas barata
                barata = auxf;
                indiceBarata = i;
            }
            media+=auxf;
        }
        media/=NUMEROCALLES;
        int auxi = (int)(media*100); //truncamos a 2 decimales, no tiene sentido x.xxxxxxxx
        media = auxi/100f;
        
        System.out.println("La calle mas cara es: " + t.getCasilla(indiceCara).getNombre());
        System.out.println("La calle mas barata es: " + t.getCasilla(indiceBarata).getNombre());
        System.out.println("La media es: " + media);
        
        //TEST 7
        System.out.println("\n\nTEST 7");
        MazoSorpresas mazo = new MazoSorpresas(true);
        System.out.println(Diario.getInstance().getEventos());
        Diario.getInstance().ocurreEvento("Se termina el juego");
        System.out.println(Diario.getInstance().getEventos());

        System.out.println("\nHay eventos pendientes? " +Diario.getInstance().eventosPendientes());
        System.out.println("Evento leido: " + Diario.getInstance().leerEvento());
        System.out.println("Evento leido: " + Diario.getInstance().leerEvento());
        System.out.println("Evento leido: " + Diario.getInstance().leerEvento());
        System.out.println("Evento leido: " + Diario.getInstance().leerEvento());
        System.out.println("Hay eventos pendientes? " +Diario.getInstance().eventosPendientes());
        
        //TEST 8
        System.out.println("\n\nTEST 8");
        int posicion = 0;
        for(int i = 0; i < 10; i++){
            System.out.println("Posicion de la ficha: " + posicion);
            posicion = t.nuevaPosicion(posicion,Dado.getInstance().tirar());
            
            System.out.println("Ha pasado por salida? " + t.getPasoPorSalida());
            if(t.getPasoPorSalida())
                t.computarPasoPorSalida();
        }
    }
}
