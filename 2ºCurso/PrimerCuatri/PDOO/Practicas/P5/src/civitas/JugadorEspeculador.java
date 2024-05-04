/**
 * @file JugadorEspeculador.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

/**
 * @brief Clase Hija(Jugador) JugadorEspeculador que gestiona este nuevo tipo de
 * jugador.
 * Un jugador cualquiera puede convertirse en especulador
 * Ser especulador implica cambios en sus atributos o como el juego reacciona a él
 *  -Paga la mitad
 *  -Puede construir un @c FactorEspeculador de veces(casas y hoteles)
 * Un jugador solo puede convertido mediante la Sorpresa Convertirme
 */
public class JugadorEspeculador extends Jugador{

    protected static float FactorEspeculador = 2;
    
    protected JugadorEspeculador(Jugador otro){
        super(otro); //Copia atributos
        CasasMax*= FactorEspeculador;
        HotelesMax*=FactorEspeculador;
        ActualizaPropiedadesPorConversion(otro); //Convierte propiedades
    }
    
    float getFactorEspeculador(){
        return FactorEspeculador;
    }
    
    private void ActualizaPropiedadesPorConversion(Jugador jugador){
        jugador.getPropiedades().forEach(propiedad -> {
            propiedad.actualizaPropietarioPorConversion(this); //cambia las propiedades
        });
    }
    
    @Override
    boolean paga(float cantidad){
        float nuevaC = cantidad/FactorEspeculador;
        Diario.getInstance().ocurreEvento("Paco paga " + nuevaC + " en vez de "
                + cantidad + " por ser especulador!");
        return super.paga(nuevaC);
    }
    
}
