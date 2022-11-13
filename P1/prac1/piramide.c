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
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "piramide.h"

Piramide::Piramide(float l, float h){
  lado = l;
  alto = h;
}

//Dados 2 longitudes (vectores) que forman un triangulo rectangulo, calcula la normal
void Piramide::calcularNormal(float base, float altura){
  //1 calcular hipotenusa
  float hip = sqrt(base*base + altura*altura);
  
  //2 calcular angulo del triangulo calculado
  float ang = altura/hip;
  
  //3 calcular el angulo de la normal
  float angF = M_PI/2 - asin(ang);

  //4 Calcula las dimensiones de la normal
  Nx = sin(angF);
  Ny = cos(angF);

  //printf("\nLas dimensiones de la normal es %f y %f \n", Nx,Ny);
}

void Piramide::draw( )
{
  calcularNormal(lado, alto);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glColor3f (color[0], color[1], color[2]);
  glBegin (GL_QUADS);
  {				//base
    glNormal3f (0, -1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, 0, lado);
    glVertex3f (0, 0, lado);
  }
  glEnd ();

  glBegin (GL_TRIANGLE_STRIP);
  {
    // Trasera
    // glNormal3f (0, Ny, -Nx);
    // glVertex3f (lado, 0, 0);
    // glVertex3f (0, 0, 0);
    // glVertex3f (lado/2, alto, lado/2);

    //Lateral izquierdo
    glNormal3f (-Nx, Ny, 0);
    glVertex3f (0, 0, lado);
    
    //Frontal
    // glNormal3f (0, Ny, Nx);
    // glVertex3f (lado, 0, lado);

    //Lateral derecho
    glNormal3f (Nx, Ny, 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, 0, lado);
    glVertex3f (lado/2, alto, lado/2);

  }
  glEnd ();
}