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

=======================================================

	 modelo.h
*/

#ifndef MODELO_H
#define MODELO_H
#include <iostream>

int pick(int x, int y, int *i, int *componente);

void ColorSeleccion ( int i, int componente);

void setSeleccion (int i, int j);

void getSeleccion(float *i, float *j);

void setColorSeleccion(GLfloat color[3]);

void elegirAccionMenu(GLfloat mat_ambient[4], GLfloat mat_diffuse[4]);

void setAccionActualMenu(int nuevaAccion);

const GLfloat * getSeleccionado();

void dibujoEscena ();

void dibujoSeleccion ();
/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
 * Funcion para cambiar el modo de visualizacion
 **/
void setModo (int M);

/**
 * Funcion para cambiar el modo de sombreado 
 **/
void invertirSombreado ();

/**
 * Funcion para devolver el modo de sombreado
*/
int getSombreado();

/**
 * Funcion para cambiar la variable luz 
 **/
void invertirIluminacion();

void cambiarPuntoLuz();
/**
 * Funcion para activar/desactivar la iluminacion
*/
void alternarAnimacion();

/**
 * Obtiene la entrada de teclado para seleccionar la practica en Dibuja de modelo
*/
void setLetra(char k);

class Objeto3D { 
public: 
	GLuint texId = 0;
	unsigned int w, h;
	unsigned char *pixeles;

	void activarTextura(){
		glGenTextures (1 , &texId );
		glBindTexture(GL_TEXTURE_2D, texId);
  		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  		glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, w, h, 0, GL_RGB,
    		GL_UNSIGNED_BYTE, pixeles);
	}

		virtual void draw() = 0; // Dibuja el objeto
};

#endif