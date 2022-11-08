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
ObjetoRevolucion rueda("./plys/rueda",32, false, false);
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
  cilindro(-0.75, 2, 0, 1.75, 2.5, 0, 0.21); //1
  cilindro(-0.25, 0, 0, -0.75, 2, 0, 0.21); //2.1
  cilindro(-0.75, 2, 0, -1.0, 3, 0, 0.19); //2.2

  cilindro(-0.25, 0.0, 0.0, 1.85, 2.3, 0, 0.22); //3
  cilindro(-2.45, 0.0, -0.45, -2.45, 0.0, 0.45, 0.2); //4 union rueda izquierda
  cilindro(-2.45, 0.0, 0.3, -2.45, 0.0, 0.25, 0.5); //4 platillo delantero
  cilindro(-2.45, 0.0, -0.3, -2.45, 0.0, -0.25, 0.5); //4 platillo delantero
  cilindro(-2.43, 0.0, -0.3, -1.05, 1.7, -0.3, 0.2, 0.1); //4
  cilindro(-2.43, 0.0, 0.3, -1.05, 1.7, 0.3, 0.2, 0.1); //4 paralela
  cilindro(-1.05, 1.7, -0.3, -1.05, 1.7, 0.3, 0.2, 0.1); //4 union superior
  cilindro(-1.07, 1.68, 0.3, -0.75, 2.05, 0, 0.2, 0.1); //4 extension frontal
  cilindro(-1.07, 1.68, -0.3, -0.75, 2.05, 0, 0.2, 0.1); //4 extension trasera

  cilindro(-2.5, 0.0, -0.3, -0.45, 0.0, -0.3, 0.14); //5
  cilindro(-2.5, 0.0, 0.3, -0.45, 0.0, 0.3, 0.14); //5 paralela
  cilindro(-0.51, 0.0, 0.3, -0.35, 0, 0, 0.15); //5 extension frontal
  cilindro(-0.51, 0.0, -0.3, -0.35, 0, 0, 0.15); //5 extension trasera

  cilindro(1.85, 2.2, 0, 1.45, 3.5, 0, 0.21); //6.1
  cilindro(2.45, 0, -0.3, 1.95, 1.7, -0.3, 0.2); //6.2
  cilindro(2.45, 0, 0.3, 1.95, 1.7, 0.3, 0.2); //6.2 paralela
  cilindro(2.45, 0.0, 0.45, 2.45, 0.0, -0.45, 0.2); //6.2 union rueda derecha
    cilindro(2.45, 0.0, 0.3, 2.45, 0.0, 0.25, 0.5); //6 platillo delantero
  cilindro(2.45, 0.0, -0.3, 2.45, 0.0, -0.25, 0.5); //6 platillo delantero
  
  cilindro(1.95, 1.7, 0.3, 1.85, 2.2, 0, 0.19); //6.2 extension frontal
  cilindro(1.95, 1.7, -0.3, 1.85, 2.2, 0, 0.19); //6.2 extension trasera

  cilindro(1.45, 3.5, -1.0, 1.45, 3.5, 1, 0.19); //Barra Manillar
  cilindro(1.45, 3.5, -1.0, 1.95, 3.7, -1, 0.19); //Manillar Izquierdo
  cilindro(1.45, 3.5, 1.0, 1.95, 3.7, 1, 0.19); //Manillar Derecho

  /*Sustituir por ply de sillin*/
  cilindro(-1.5, 3, 0, -0.5, 3, 0, 0.25); //Sillin 1


}

void creaRuedas(float escala, float grosor){
  glEnable(GL_NORMALIZE);
  float pos_rI = -escala - escala/2 - 0.2*grosor;
  float pos_rD = escala + escala/2 + 0.2*grosor;

  //Rueda izquierda
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(pos_rI, 0, 0);
  glScalef(escala, grosor, escala);
  rueda.draw();
  glPopMatrix();

  //Rueda derecha
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(pos_rD, 0, 0);
  glScalef(escala, grosor, escala);
  rueda.draw();
  glPopMatrix();

  glPushMatrix();
  float x,y, desfase = 0.15;
  int num_llantas = 24;
  float tamaño_llanta = 1*escala;

  //Llantas delantera
  glTranslatef(pos_rD, 0, 0);
  for(int i = 0; i <= num_llantas; i++){
    x = tamaño_llanta*cos((M_PI/(num_llantas/2))*i + desfase);
    y = tamaño_llanta*sin((M_PI/(num_llantas/2))*i + desfase);
    cilindro(x/7, y/7, -0.3, x, y, 0.0, 0.05);
    cilindro(x/7, y/7, 0.3, x, y, 0.0, 0.05);
  }
  glPopMatrix();

  glPushMatrix();
  //Llantas traseras
  glTranslatef(pos_rI, 0, 0);
  for(int i = 0; i <= num_llantas; i++){
    x = tamaño_llanta*cos((M_PI/(num_llantas/2))*i + desfase);
    y = tamaño_llanta*sin((M_PI/(num_llantas/2))*i + desfase);
    cilindro(x/7, y/7, -0.3, x, y, 0.0, 0.05);
    cilindro(x/7, y/7, 0.3, x, y, 0.0, 0.05);
  }
  glPopMatrix();

}