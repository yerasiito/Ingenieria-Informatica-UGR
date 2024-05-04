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
public class MazoSorpresas {
        private boolean barajada;
        private boolean debug;
        private int usadas;
        private ArrayList<Sorpresa> sorpresas;
        
        private void init(){
            barajada = false;
            debug = false;
            usadas = 0;
            sorpresas = new ArrayList<>();
        }
        
        public MazoSorpresas(){
            init();
        }
        
        public MazoSorpresas(boolean d){
            init();
            debug = d;
            Diario.getInstance().ocurreEvento("El mazo ha cambiado debug a " + debug);
        }
        
        public ArrayList<Sorpresa> getMazoSorpresas(){
            return sorpresas;
        }
        
        public void alMazo(Sorpresa s){
            if(!barajada)
                sorpresas.add(s);
        }
        
        public Sorpresa siguiente(){
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
