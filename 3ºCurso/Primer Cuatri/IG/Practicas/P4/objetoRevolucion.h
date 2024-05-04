/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informaticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
	modulo objetoRevolucion.h

*/

#ifndef OBJETOREVOLUCION_H
#define OBJETOREVOLUCION_H

#include "malla.h"
#include "lector-jpg.h"

class ObjetoRevolucion:public Malla
{
  public:
    int n; //Numero de revoluciones
    int m; //Numero de vertices del perfil inicial
    bool tapa = false;
  
  /**
   * Constructor vacio
  */
  ObjetoRevolucion();
  
  /**
   * @brief Constructor con parametros
   * @param nombre_archivo Lee los vertices del perfil con este nombre
   * @param nrevol Indica el numero de revoluciones a aplicar, por defecto 10
   * @param tapa_sup True para crear la tapa superior, false en otro caso. Por defecto false
   * @param tapa_sup True para crear la tapa inferior, false en otro caso. Por defecto true
   */
  ObjetoRevolucion(const char *nombre_archivo, int nrevol, bool tapa_sup = false, bool tapa_inf = true);


  ObjetoRevolucion(const char *nombre_archivo, const char *nombre_textura, float centroT = 0, int nrevol = 10, bool tapa_sup = false, bool tapa_inf = false);


  void crearRevolucion();

  void crear_tapas(bool tapa_sup, bool tapa_inf);

  void normales_vertices();
  
  void draw_lines();

  void draw_points();

  void setTexturaCil();

  void setTexturaTapa(float centro);

  void calcularMinMax();

};
#endif