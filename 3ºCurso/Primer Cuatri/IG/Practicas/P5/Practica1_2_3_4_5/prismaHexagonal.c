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
	modulo prismaHexagonal.c
	Definicion del prisma hexagonal

*/

#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "prismaHexagonal.h"

  PrismaHexagonal::PrismaHexagonal(float l, float h){
    lado = l;
    altura = h;
  }

  void PrismaHexagonal::draw(){
    glPushAttrib(GL_LIGHTING_BIT);
    //base inferior
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glColor3f (color[0], color[1], color[2]);
    glBegin(GL_POLYGON);
    {
      glNormal3f(0, -1, 0);
      glVertex3f(lado/2, 0, 0);
      glVertex3f(lado/2 + lado, 0, 0);
      glVertex3f(lado*2, 0, lado);
      glVertex3f(lado/2 + lado, 0, lado*2);
      glVertex3f(lado/2, 0, lado*2);
      glVertex3f(0, 0, lado);
    }
    glEnd();
  
    //Base superior
    glBegin(GL_POLYGON);
    {
      glNormal3f(0, 1, 0);
      glVertex3f(lado/2, altura, 0);
      glVertex3f(0, altura, lado);
      glVertex3f(lado/2, altura, lado*2);
      glVertex3f(lado/2 + lado, altura, lado*2);
      glVertex3f(lado*2, altura, lado);
      glVertex3f(lado/2 + lado, altura, 0);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    {
      //trasera
      glNormal3f(0, 0, -1);
      glVertex3f(lado/2, 0, 0);
      glVertex3f(lado/2, altura, 0);
      glVertex3f(lado/2 + lado, 0, 0);
      glVertex3f(lado/2 + lado, altura, 0);

      //trasera derecha
      glNormal3f(sqrt(2)/2, 0 ,-sqrt(2)/2);
      glVertex3f(lado*2, 0, lado);
      glVertex3f(lado*2, altura, lado);

      //Delantera derecha
      glNormal3f(sqrt(2)/2, 0 ,sqrt(2)/2);
      glVertex3f(lado/2 + lado, 0, lado*2);
      glVertex3f(lado/2 + lado, altura, lado*2);
      
      //Frente
      glNormal3f(0, 0 , 1);
      glVertex3f(lado/2, 0, lado*2);
      glVertex3f(lado/2, altura, lado*2);
      
      //Delantera izquierda
      glNormal3f(-sqrt(2)/2, 0 ,sqrt(2)/2);
      glVertex3f(0, 0, lado);
      glVertex3f(0, altura, lado);

      //Trasera izquierda
      glNormal3f(-sqrt(2)/2, 0 ,-sqrt(2)/2);
      glVertex3f(lado/2, 0, 0);
      glVertex3f(lado/2, altura, 0);

    }
    glEnd();
    glPopAttrib();
  }
