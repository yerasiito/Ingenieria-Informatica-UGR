/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Yeray Lopez Ramirez

	Programa principal
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
modulo visual.c
    Inicialización de ventana X
    Transformación de visualización
    Transformación de proyección
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"




//================================================ VARIABLES  

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 30, view_roty = 45;
float x_camara, y_camara, z_camara;

/**

Distancia de la cámara

**/

float D = 10;


/**

Tamaño de la ventana X

**/


float anchoVentana, altoVentana;



/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float d, float x, float y, float z)
{
  view_rotx = ax;
  view_roty = ay;
  x_camara = x;
  y_camara = y;
  z_camara = z;
  D = d;
}

void giroCamara (float ax, float ay){
  view_rotx += ax;
  view_roty += ay;
}


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/
void transformacionVisualizacion ()
{
  glTranslatef (0, 0, -D);
  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0);

  glTranslatef(-x_camara,-y_camara,-z_camara);
}

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion (bool perspectiva)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity ();
  float calto;			// altura de la ventana corregida

  if (anchoVentana > 0)
    calto = altoVentana / anchoVentana;
  else
    calto = 1;

  if(perspectiva){
    glFrustum (-1, 1, -calto, calto, 1, 1500);
  }
  else{
    glOrtho(-10, 10, -calto*10, calto*10, 1, 1500);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity ();

}

/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto)
{
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport (0, 0, ancho, alto);	// Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  fijaProyeccion ();		// Cargamos la transformacion de proyeccion

}

int menu;
typedef enum{START, SALIR,PAUSE} opciones_menu;

void Init(){
  menu = glutCreateMenu(seleccionMenu);
  glutAddMenuEntry("Start", START);
  glutAddMenuEntry("Exit", SALIR);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void seleccionMenu (int opcion){
  switch ( opcion ){
    case START:
      std::cout << "empieza\n";
    case SALIR:
      exit(0);
  }
  glutPostRedisplay();

}