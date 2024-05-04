/**
 * @file GestionInmobiliaria.java
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
 * @date Diciembre de 2021
 */
package civitas;

/**
 * @brief Clase GestionInmobiliaria que gestiona las operaciones sobre las calles.
 */
public class GestionInmobiliaria {
    private int propiedad;
    private final OperacionInmobiliaria operacion;
    
    public GestionInmobiliaria(OperacionInmobiliaria gest, int ip){
        operacion = gest;
        ip = propiedad;
    }
    
    public OperacionInmobiliaria getOperacion(){
        return operacion;
    }
    
    public int getPropiedad(){
        return propiedad;
    }
}
