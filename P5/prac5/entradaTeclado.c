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
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <iostream>
#include "practicasIG.h"
/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("h, H: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!       

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}


/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;
bool perspectiva = true;
int xcamara = 0.0, ycamara = 0.0, zcamara = 0.0;

void letra (unsigned char k, int x, int y)
{
  setLetra(k);
  
  switch (k)
    {
    case 'A':
    case 'a':
      xcamara -= 1.0;
      break;
    case 'S':
    case 's':
      zcamara += 1.0;
      break;
    case 'W':
    case 'w':
      zcamara -= 1.0; 
      break;
    case 'D':
    case 'd':
      xcamara += 1.0;  
      break;
    case 'R':
    case 'r':
      rotxCamara = 0;
      rotyCamara = 0;
      dCamara = 10;
    case 'U':
    case 'u':
      alternarAnimacion();
      break;
    case 'p':
    case 'P':
      setModo(GL_POINT);
      break;
    case 'l':
    case 'L':
      setModo(GL_LINE);
      break;
    case 'f':
    case 'F':
      setModo(GL_FILL);
      break;
    case 'Y':
    case 'y':
      invertirSombreado();
      break;
    case 'i':
    case 'I':
      invertirIluminacion();
      break;
    case 'c':
      cambiarPuntoLuz();
      break;
    case 'h':
    case 'H':
      printHelp ();		// H y h imprimen ayuda
      break;
    case '+':			// acerca la cámara
      dCamara /= 1.1;
      break;
    case '-':			// aleja la cámara
      dCamara *= 1.1;
      break;
    case 27:			// Escape  Terminar
      exit (0);
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, dCamara, xcamara, ycamara, zcamara);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara += 5.0;	// Cursor arriba + rotacion x
      if (rotxCamara > 360)
	rotxCamara -= 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara -= 5.0;
      if (rotxCamara < 0)
	rotxCamara += 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara += 5.0;
      if (rotyCamara > 360)
	rotyCamara -= 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara -= 5.0;
      if (rotyCamara < 0)
	rotyCamara += 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      dCamara -= 0.5;
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      dCamara += 0.5;
      break;
    case GLUT_KEY_F1:
      rotxCamara = 0;
      rotyCamara = 0;
      dCamara = 12;
      perspectiva = false;
      break;
    case GLUT_KEY_F2:
      rotxCamara = 0;
      rotyCamara = -90;
      dCamara = 12;
      perspectiva = true;
      break;
    case GLUT_KEY_F3:
      rotxCamara = 90;
      rotyCamara = 0;
      dCamara = 12;
      perspectiva = true;
      break;
    case GLUT_KEY_F4:
      perspectiva = !perspectiva;
      break;
    default:
      return;
    }
  fijaProyeccion(perspectiva);
  setCamara (rotxCamara, rotyCamara, dCamara, xcamara, ycamara, zcamara);
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
