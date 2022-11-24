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
	modulo cubo.c

*/

#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "lector-jpg.h"
#include "cubo.h"
#include <iostream>

Cubo::Cubo(float lado){
  l = lado;
}

Cubo::Cubo(float lado, const char *nombre_archivo){
  l = lado;
  pixeles = LeerArchivoJPEG(nombre_archivo, w, h);
}

void Cubo::draw( )
{
  glBindTexture(GL_TEXTURE_2D , texId);
  glPushAttrib(GL_LIGHTING_BIT);
  glBegin(GL_QUADS);
    // frente
    glNormal3f(0,0,1);
    glTexCoord2f(0.497f, 0.747f);   glVertex3f(0.0f, 0.0f, l);
    glTexCoord2f(0.7441f, 0.747f);   glVertex3f(l, 0.0f, l);
    glTexCoord2f(0.7441f, 0.5f);   glVertex3f(l, l, l);
    glTexCoord2f(0.497f, 0.5f);   glVertex3f(0.0f, l, l);
    // Trasera
    glNormal3f(0,0,-1);
    glTexCoord2f(0.25f, 0.5f);      glVertex3f(l, l, 0.0f);
    glTexCoord2f(0.25f, 0.747f);     glVertex3f(l, 0.0f, 0.0f);
    glTexCoord2f(0.00585f, 0.747f);  glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.00585f, 0.5f);   glVertex3f(0.0f, l, 0.0f);
    // Lateral derecha
    glNormal3f(1,0,0);
    glTexCoord2f(0.9941f, 0.747f);     glVertex3f(l, 0.0f, 0.0f);
    glTexCoord2f(0.9941f, 0.5f);      glVertex3f(l, l, 0.0f);
    glTexCoord2f(0.7441f, 0.5f);   glVertex3f(l, l, l);
    glTexCoord2f(0.7441f, 0.747f);   glVertex3f(l, 0.0f, l);
    // Lateral izquierdo
    glNormal3f(-1,0,0);
    glTexCoord2f(0.497f, 0.747f);   glVertex3f(0.0f, 0.0f, l);
    glTexCoord2f(0.497f, 0.5f );  glVertex3f(0.0f, l, l);
    glTexCoord2f(0.25f, 0.5f);   glVertex3f(0.0f, l, 0.0f);
    glTexCoord2f(0.25f, 0.747f);  glVertex3f(0.0f, 0.0f, 0.0f);
    // Tapa de arriba
    glNormal3f(0,1,0);
    glTexCoord2f(0.497f, 0.5f );  glVertex3f(0.0f, l, l);
    glTexCoord2f(0.7441f, 0.5f);   glVertex3f(l, l, l);
    glTexCoord2f(0.7441f, 0.2519f);      glVertex3f(l, l, 0.0f);
    glTexCoord2f(0.497f, 0.2519f);   glVertex3f(0.0f, l, 0.0f);
    // Tapa de abajo
    glNormal3f(0,-1,0);
    glTexCoord2f(0.7441f, 0.747f);   glVertex3f(l, 0.0f, l);
    glTexCoord2f(0.497f, 0.747f);   glVertex3f(0.0f, 0.0f, l);
    glTexCoord2f(0.497f, 0.995f);  glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.7441f, 0.995f);     glVertex3f(l, 0.0f, 0.0f);

glEnd(); 
glPopAttrib();
}
