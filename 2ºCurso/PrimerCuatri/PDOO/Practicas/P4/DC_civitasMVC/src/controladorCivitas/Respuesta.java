/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controladorCivitas;

import java.util.ArrayList;

public enum Respuesta{
    NO, SI;
    
    public static ArrayList<String> respuestas(){
        ArrayList<String> respuestas = new ArrayList<String> (){{
            for(int i = 0; i < Respuesta.values().length; i++)
                add(Respuesta.values()[i].toString());
        }};
        
        return respuestas;
    }
}