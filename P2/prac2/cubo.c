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
	modulo cubo.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "cubo.h"

Cubo::Cubo(float lado){
  l = lado;
}

void rand(float color[4]){
}
// Dibuja el cubo
void Cubo::draw( )
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glColor3f (color[0], color[1], color[2]);


  glBegin (GL_QUAD_STRIP);
  {				/* Caras transversales */
    rand(color);
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (l, l, l);
    glVertex3f (0, l, l);
    glVertex3f (l, 0, l);
    glVertex3f (0, 0, l);
    rand(color);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (l, 0, 0);
    glVertex3f (0, 0, 0);
    rand(color);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (l, l, 0);
    glVertex3f (0, l, 0);
    rand(color);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (l, l, l);
    glVertex3f (0, l, l);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {				/* Costados */
    rand(color);
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (l, 0, 0);
    glVertex3f (l, l, 0);
    glVertex3f (l, l, l);
    glVertex3f (l, 0, l);
    rand(color);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, l);
    glVertex3f (0, l, l);
    glVertex3f (0, l, 0);
  }
  glEnd ();
}
