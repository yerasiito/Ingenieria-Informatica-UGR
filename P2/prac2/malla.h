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
	modulo malla.h

*/

#ifndef MALLA_H
#define MALLA_H

#include "modelo.h"
#include <vector>

class Malla:Objeto3D{

  private:
    std::vector <float> vertices;
    std::vector <int> caras;
    std::vector <float> normales_c;
    std::vector <float> normales_v;

  public:
    Malla(const char *nombre_archivo);

    void normales_caras();
    void normales_vertices();

    void draw_caras();
    void draw_vertices();
    void draw();
};

#endif