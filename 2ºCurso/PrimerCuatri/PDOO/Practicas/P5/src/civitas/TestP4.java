/**
 * @file TestP4.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;
/**
 * @brief Clase de prueba de la Practica 4. 
 * Verifica si el jugador se convierte en Especulador y se hacen efectivos sus cambios
 */
public class TestP4 {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //Creamos jugador y lo metemos en un arrayList jugadores
        Jugador jug1 = new Jugador("Paco");
        ArrayList<Jugador> jugadores = new ArrayList<>();
        jugadores.add(jug1);
        
        //creamos la propiedad que cambiará de propietario(jugador a especulador)
        CasillaCalle propiedad1 = new CasillaCalle("Nueva", 100, 500, 0); //vale 100€
        SorpresaConvertirme sorpresa = new SorpresaConvertirme("Has pisado un casino, y te has puesto a especular");
        jug1.comprar(propiedad1); //el jugador la compra
        
        //Convierte el jugador
        System.out.println("Jugador antes de convertirse " + jugadores.get(0).getClass());
        sorpresa.aplicarAJugador(0, jugadores); //el jugador se convierte
        System.out.println("Jugador despues de convertirse " + jugadores.get(0).getClass());
        
        //Imprime los eventos
        while(Diario.getInstance().eventosPendientes()){
                System.out.println(Diario.getInstance().leerEvento());
        }
        System.out.println("");
        
        JugadorEspeculador convertido = (JugadorEspeculador)jugadores.get(0); //ahorra llamar al array
        
        //Creamos una casilla para que especulador compre a la mitad de precio
        CasillaCalle propiedad2 = new CasillaCalle("Nueva", 200, 10, 0); //vale 200€

        convertido.comprar(propiedad2); //Deberia de pagar 100€
        
        //Imprime los eventos
        while(Diario.getInstance().eventosPendientes()){
                System.out.println(Diario.getInstance().leerEvento());
        }
        System.out.println("");
        
        //Construye todos las casas y hoteles posibles
        System.out.println("El jugador construye todo lo que puede en la prop1: ");
        System.out.println("****************************************************"); //Comentar de aqui al siguiente separador(se peta la terminal)
        for(int i = 0; i < 8; i++){
            while(!convertido.construirHotel(1)){
                convertido.construirCasa(1); //construye casas
            } //debe de poder construirlas todas
        }
        for(int i = 0; i < 8; i++)
            convertido.construirCasa(1); //construye las casas que quedan
        
        //Imprime eventos
        while(Diario.getInstance().eventosPendientes()){
                System.out.println(Diario.getInstance().leerEvento());
        }
        System.out.println("****************************************************");
        
        //Vemos que está todo construido al maximo
        System.out.println("Tiene " + convertido.getPropiedades().get(1).getNumCasas() + " casas");
        System.out.println("Tiene " + convertido.getPropiedades().get(1).getNumHoteles() + " hoteles");
        //intentamos construir de mas
        convertido.construirCasa(1); //No la puede construir
        convertido.construirHotel(1); //No lo puede construir
        
        while(Diario.getInstance().eventosPendientes()){
                System.out.println(Diario.getInstance().leerEvento());
        }

        
    }
}
