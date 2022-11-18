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

=======================================================

	cubo.h
*/

#ifndef CUBO_H
#define CUBO_H

#include "modelo.h"

class Cubo:Objeto3D
{
   private:
      float l;
	  GLuint texId = 500;
	  unsigned int w, h;
	  unsigned char *pixeles;
   public:
      Cubo(float lado=1);
	  Cubo(float lado, const char *nombre_archivo);

      void draw();

	  void activarTextura();
};

#endif