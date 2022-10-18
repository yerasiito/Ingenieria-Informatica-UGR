/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
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

class ObjetoRevolucion:public Malla
{
  public:
    int n = 1000; //Numero de revoluciones
    int m; //Numero de vertices del perfil inicial

  ObjetoRevolucion(const char *nombre_archivo, bool tapa_sup, bool tapa_inf);

  void crearRevolucion();

  void crear_tapas(bool tapa_sup, bool tapa_inf);

  void draw_lines();

  void draw_points();
};
#endif