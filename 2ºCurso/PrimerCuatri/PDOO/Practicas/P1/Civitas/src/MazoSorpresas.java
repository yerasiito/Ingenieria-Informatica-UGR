/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

/**
 *
 * @author ylope
 */
public class MazoSorpresas {
        private ArrayList<Sorpresa> sorpresas;
        private boolean barajada;
        private int usadas;
        private boolean debug;
        
        private void init(){
            sorpresas = new ArrayList<>();
            barajada = false;
            usadas = 0;
        }
        
        MazoSorpresas(boolean d){
            init();
            debug = d;
            Diario.getInstance().ocurreEvento("El mazo ha cambiado debug a " + debug);
        }
        
        MazoSorpresas(){
            init();
            debug = false;
        }
        
        void alMazo(Sorpresa s){
            if(!barajada){
                sorpresas.add(s);
            }
        }
        
        Sorpresa siguiente(){
            if((!barajada || usadas == sorpresas.size()) && !debug){
                Collections.shuffle(sorpresas); //mezclamos los objetos
                usadas = 0;
                barajada = true;
            }
            usadas++;
            Collections.rotate(sorpresas, -1);
            return sorpresas.get(sorpresas.size()-1);
        }
}
