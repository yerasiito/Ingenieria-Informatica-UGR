/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

public class Estacion {
    private final String nombre;
    private final TipoEstacion tipo;

    public Estacion(String nombre, TipoEstacion tipo) {
        this.nombre = nombre;
        this.tipo = tipo;
    }

    public String getNombre() {
        return nombre;
    }

    public TipoEstacion getTipo() {
        return tipo;
    }

    @Override
    public String toString() {
        return "Estacion{" + "nombre=" + nombre + ", tipo=" + tipo + '}';
    }
}
