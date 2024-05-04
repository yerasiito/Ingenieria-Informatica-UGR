/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

public enum OperacionInmobiliaria{
    CONSTRUIR_CASA, CONSTRUIR_HOTEL, TERMINAR;
    
    public static ArrayList<String> operaciones(){
        ArrayList<String> operaciones = new ArrayList<String> (){{
            for(int i = 0; i < OperacionInmobiliaria.values().length; i++)
                add(OperacionInmobiliaria.values()[i].toString());
        }};
        return operaciones;
    }
}
