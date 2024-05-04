/**
 * @file CasillaCalleSostenible.java
 * @date Diciembre de 2021
 */
package civitas;

/**
 * @brief Clase Hija de CasillaCalle que gestiona las calles Sostenibles del @c Tablero.
 */
public class CasillaCalleSostenible extends CasillaCalle {
    float porcentajeInversion;

    public CasillaCalleSostenible(String titulo, float precioCompra, float precioEdificar, float precioBaseAlquiler, float porcentajeInversion) {
        super(titulo, precioCompra, precioEdificar, precioBaseAlquiler);
        this.porcentajeInversion = porcentajeInversion;
    }

    public void setPorcentajeInversion(float porcentajeInversion) {
        this.porcentajeInversion = porcentajeInversion;
    }
    
    @Override
    public boolean soySostenible(){
        return true;
    }
    
    @Override
    public float getImporteHacermeSostenible(){
        return 0;
    }
    
    @Override
    public CasillaCalleSostenible hacermeSostenible(){
        return null;
    }
    
    @Override
    public float getPrecioAlquilerCompleto(){
        float precioAlquiler = super.getPrecioAlquilerCompleto();
        return precioAlquiler + precioAlquiler*porcentajeInversion/100;
    }

    @Override
    public String toString() {
        return "CasillaCalleSostenible{" + super.toString() + "porcentajeInversion=" + porcentajeInversion + '}';
    }
    


}
