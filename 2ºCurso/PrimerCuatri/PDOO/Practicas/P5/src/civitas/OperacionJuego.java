/**
 * @file OperacionJuego.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

/**
 * @brief Enumerado OperacionJuego que gestiona los posibles estados del civitas
 * Utilizado por @c GestorEstados, @c Controlador y @c VistaTextual
 */
public enum OperacionJuego {
    PASAR_TURNO,
    AVANZAR,
    COMPRAR,
    GESTIONAR
}