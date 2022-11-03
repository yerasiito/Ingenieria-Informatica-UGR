/*

	Informática Gráfica					Curso 2022-23

	Dpto. Lenguajes y Sistemas Informaticos
	E.T.S.I. Informaica
	Univ. de Granada

	J.C. Torres

        Modulo de creacion de elementos geometricos para gruas. Creado a partir del código de las práacticas de CAD (https://lsi2.ugr.es/~cad/).

*/

// Nota: Los acentos han sido suprimidos en la documentacion por compatibilidad
// con las version usada de doxygen. Las letras ñ se han sustituido por "ny"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "objetoRevolucion.h"


ObjetoRevolucion pieza("./plys/cilindro", 32, true, true);
/**
 Seccion de los perfiles para la estructura
**/
#define seccion 0.1

/**
Calcula el modulo del vector (x,y,z)
**/

float modulo(float x,float y,float z)
{
return sqrt(x*x+y*y+z*z);
}


/**
Crea un cilindro con las bases en x0,y0,z0 y x1,y1,z1, y radio de la base axb.

**/
void cilindro(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b = 0)
{
	float m;
	m= modulo(x1-x0,y1-y0,z1-z0);
	glPushMatrix();
	
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90, 0.0, 0.0, 1.0);
	
	glEnable(GL_NORMALIZE);
	if(b == 0) //El cilindro tiene base circular
		glScalef(a , m , a);
	else //El cilindro tiene base eliptica
		glScalef(a , m , b);
	pieza.draw();

	glPopMatrix();

}

void creaCuerpoBici(){
  cilindro(-0.5, 2, 0, 2, 2.5, 0, 0.21); //1
  cilindro(0, 0, 0, -0.5, 2, 0, 0.21); //2.1
  cilindro(-0.5, 2, 0, -0.75, 3, 0, 0.19); //2.2

  cilindro(0, 0, 0, 2.1, 2.3, 0, 0.22); //3
  cilindro(-0.8, 1.7, -0.3, -2.15, 0.1, -0.3, 0.14); //4
  cilindro(-0.8, 1.7, 0.3, -2.15, 0.1, 0.3, 0.14); //4 paralela
  cilindro(-0.8, 1.7, -0.3, -0.8, 1.7, 0.3, 0.1); //4 union superior
  cilindro(-0.8, 1.7, 0.29, -0.5, 2.05, 0, 0.14); //4 extension frontal
  cilindro(-0.8, 1.7, -0.29, -0.5, 2.05, 0, 0.14); //4 extension trasera

  cilindro(-2.2, 0.1, -0.3, -0.2, 0.0, -0.3, 0.15); //5
  cilindro(-2.2, 0.1, 0.3, -0.2, 0.0, 0.3, 0.15); //5 paralela
  cilindro(-0.26, 0.0, 0.33, 0, 0, 0, 0.14); //5 extension frontal
  cilindro(-0.26, 0.0, -0.33, 0, 0, 0, 0.14); //5 extension trasera

  cilindro(2.1, 2.2, 0, 1.7, 3.5, 0, 0.21); //6.1
  cilindro(2.7, 0, -0.3, 2.2, 1.7, -0.3, 0.2); //6.2
  cilindro(2.7, 0, 0.3, 2.2, 1.7, 0.3, 0.2); //6.2 paralela
  cilindro(2.2, 1.7, 0.3, 2.1, 2.2, 0, 0.19); //6.2 extension frontal
  cilindro(2.2, 1.7, -0.3, 2.1, 2.2, 0, 0.19); //6.2 extension trasera

  cilindro(1.7, 3.5, -1, 1.7, 3.5, 1, 0.19); //Barra Manillar
  cilindro(1.7, 3.5, -1, 2.2, 3.7, -1, 0.19); //Manillar Izquierdo
  cilindro(1.7, 3.5, 1, 2.2, 3.7, 1, 0.19); //Manillar Derecho

  /*Sustituir por ply de sillin*/
  cilindro(-1.25, 3, 0, -0.25, 3, 0, 0.25); //Sillin 1


}

void creaRuedas(){
  glTranslatef(-2, 0, 0);
  glutSolidTorus(0.1, 1.6, 24, 32);
  glTranslatef(4.5, 0, 0);
  glutSolidTorus(0.1, 1.6, 24, 32);
}