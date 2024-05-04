/**
 * @file
 * @author Yeray Lopez Ramirez
 * @date
 * @brief
 */
package civitas;

import GUI.CapturaNombres;
import GUI.CivitasView;
import controladorCivitas.Controlador;
import java.util.ArrayList;

/**
 *
 * @author yerasito
 */
public class TestP5 {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    
        CivitasView vistaCivitas = new CivitasView();
        CapturaNombres capturaNombres = new CapturaNombres(vistaCivitas, true);
        
        ArrayList<String> nombres = capturaNombres.getNombres();
        
        CivitasJuego juego = new CivitasJuego(nombres, true);
        
        Controlador controlador = new Controlador(juego, vistaCivitas);
        
        vistaCivitas.setCivitasJuego(juego);
        
        controlador.juega();
    }
}
