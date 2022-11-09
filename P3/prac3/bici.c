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

float defaultColor[4] = {1, 1, 1, 1};
float cuerpoColor[4] = {1, 0.2, 0.2, 1};
float sillinColor[4] = {0.1, 0.1, 0.1, 1};

float metalicColor[4] = {0.792, 0.8, 0.807, 1};

float llantaColor[4] = {0.69, 0.702, 0.717, 1};
float ruedaColor[4] = {0.305, 0.29, 0.278, 1};
float pedalColor[4] = {0.3, 0.3, 0.3, 1};

Malla sillin("./plys/sillin");
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

/**
Crea un cubo con las bases en x0,y0,z0 y x1,y1,z1, y profundidad de la base a.
**/
void caja(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b = 0)
{
  float m;
	m= modulo(x1-x0,y1-y0,z1-z0);
  glPushMatrix();
	
	 glTranslatef(x0,y0,z0);
	 glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	 glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90, 0.0, 0.0, 1.0);
	
  float x,y,z;
	
  if(b==0)
    b=a;

	x= a/2;
	z= b/2;
	y = m;

  glShadeModel( GL_FLAT );

   /* Caras transversales */
  glBegin( GL_QUAD_STRIP );{
    glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

    glVertex3f( x, 0, -z );
    glVertex3f( -x, 0, -z );


    glVertex3f( x, y, -z );
    glVertex3f( -x, y, -z );

    glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

    glVertex3f( x, y, z );
    glVertex3f( -x, y, z );
    glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
    glVertex3f( x, 0, z );
    glVertex3f( -x, 0, z );

    glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
    glVertex3f( x, 0, -z );
    glVertex3f( -x, 0, -z );  }
  glEnd();

  /* Costados */
  glBegin( GL_QUADS );{
    glNormal3f( 1.0, 0.0, 0.0 );
    glVertex3f( x, 0, -z );
    glVertex3f( x, y, -z );
    glVertex3f( x, y, z );
    glVertex3f( x, 0, z ); }
  glEnd();


  glBegin( GL_QUADS );{
    glNormal3f( -1.0, 0.0, 0.0 );
    glVertex3f( -x, 0, -z );
    glVertex3f( -x, 0, z );
    glVertex3f( -x, y, z );
    glVertex3f( -x, y, -z ); }
  glEnd();

  glPopMatrix();
}


void creaCuerpoBici(){
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuerpoColor);

  glPushMatrix();
  glTranslatef(-0.87,2.5,0);
  glRotatef(15, 0, 0, 1);
  glScalef(0.11,1,0.11);
  rueda.draw();
  glPopMatrix();

  glPushMatrix();

  cilindro(-0.75, 2, 0, 1.75, 2.5, 0, 0.21); //1
  cilindro(-0.25, 0, 0, -0.75, 2, 0, 0.21); //2.1
  cilindro(-0.75, 2, 0, -1.0, 3, 0, 0.19); //2.2

  cilindro(-0.25, 0.0, 0.0, 1.85, 2.3, 0, 0.22); //3
  cilindro(-2.43, 0.0, -0.75, -1.05, 1.7, -0.3, 0.2, 0.1); //4
  cilindro(-2.43, 0.0, 0.65, -1.05, 1.7, 0.3, 0.2, 0.1); //4 paralela
  cilindro(-1.05, 1.7, -0.3, -1.05, 1.7, 0.3, 0.2, 0.1); //4 union superior
  cilindro(-1.07, 1.68, 0.3, -0.75, 2.05, 0, 0.2, 0.1); //4 extension frontal
  cilindro(-1.07, 1.68, -0.3, -0.75, 2.05, 0, 0.2, 0.1); //4 extension trasera

  cilindro(-2.4, 0.0, -0.7, -0.45, 0.0, -0.3, 0.14); //5
  cilindro(-2.4, 0.0, 0.65, -0.45, 0.0, 0.3, 0.14); //5 paralela
  cilindro(-0.51, 0.0, 0.3, -0.35, 0, 0, 0.15); //5 extension frontal
  cilindro(-0.51, 0.0, -0.3, -0.35, 0, 0, 0.15); //5 extension trasera

  cilindro(1.85, 2.2, 0.0, 1.6, 3.0, 0, 0.21); //6.1
  cilindro(1.6, 3.0, 0.0, 1.55, 3.2, 0.0, 0.15); //6.1 extension arriba
  cilindro(1.6, 3.0, 0.0, 2.4, 3.3, 0.0, 0.21); //Union cuerpo y manillar
  cilindro(2.45, 0, -0.3, 1.95, 1.7, -0.3, 0.2); //6.2
  cilindro(2.45, 0, 0.3, 1.95, 1.7, 0.3, 0.2); //6.2 paralela

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, metalicColor);
  cilindro(-2.45, 0.0, 0.3, -2.45, 0.0, 0.25, 0.5); //4 platillo trasero
  cilindro(-2.45, 0.0, -0.3, -2.45, 0.0, -0.25, 0.5); //4 platillo trasero
  cilindro(-2.45, 0.0, -0.805, -2.45, 0.0, 0.705, 0.15); //4 union rueda izquierda
  cilindro(2.45, 0.0, 0.3, 2.45, 0.0, 0.25, 0.5); //6 platillo delantero
  cilindro(2.45, 0.0, -0.3, 2.45, 0.0, -0.25, 0.5); //6 platillo delantero
  cilindro(2.45, 0.0, 0.45, 2.45, 0.0, -0.45, 0.2); //6.2 union rueda derecha
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuerpoColor);
  
  cilindro(1.95, 1.7, 0.3, 1.85, 2.2, 0, 0.19); //6.2 extension frontal
  cilindro(1.95, 1.7, -0.3, 1.85, 2.2, 0, 0.19); //6.2 extension trasera

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sillinColor);
  cilindro(2.4, 3.3, -1.0, 2.4, 3.3, 1, 0.19); //Barra Manillar
  cilindro(2.4, 3.3, -1.0, 2.8, 3.5, -1, 0.19); //Manillar Izquierdo
  cilindro(2.4, 3.3, 1.0, 2.8, 3.5, 1, 0.19); //Manillar Derecho

  /*Sustituir por ply de sillin*/
  glTranslatef(-1, 3, 0);
  glScalef(1, 1, 1);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sillinColor);
  sillin.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuerpoColor);

  glTranslatef(0, 0.0, 2.0);

  glPopMatrix();
}

void creaRuedas(float escala, float grosor){
  glEnable(GL_NORMALIZE);
  float pos_rI = -escala - escala/2 - 0.2*grosor;
  float pos_rD = escala + escala/2 + 0.2*grosor;

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ruedaColor);
  
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


  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, llantaColor);

  glPushMatrix();
  float x,y, desfase = 0.15;
  int num_llantas = 24;
  float tamanio_llanta = 1*escala;

  //Llantas delantera
  glTranslatef(pos_rD, 0, 0);
  for(int i = 0; i <= num_llantas; i++){
    x = tamanio_llanta*cos((M_PI/(num_llantas/2))*i + desfase);
    y = tamanio_llanta*sin((M_PI/(num_llantas/2))*i + desfase);
    cilindro(x/7, y/7, -0.3, x, y, 0.0, 0.05);
    cilindro(x/7, y/7, 0.3, x, y, 0.0, 0.05);
  }
  glPopMatrix();

  glPushMatrix();
  //Llantas traseras
  glTranslatef(pos_rI, 0, 0);
  for(int i = 0; i <= num_llantas; i++){
    x = tamanio_llanta*cos((M_PI/(num_llantas/2))*i + desfase);
    y = tamanio_llanta*sin((M_PI/(num_llantas/2))*i + desfase);
    cilindro(x/7, y/7, -0.3, x, y, 0.0, 0.05);
    cilindro(x/7, y/7, 0.3, x, y, 0.0, 0.05);
  }
  glPopMatrix();

}

void pedal(float pos_x, float pos_y, float pos_z, float tam_x, float tam_y, float tam_z){
  float colorR[4] = { 1.0, 0.55, 0.0, 1};

  glTranslatef(pos_x, pos_y, pos_z);
  glScalef(tam_x, tam_y, tam_z);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pedalColor);
  caja(0, 0, 0, 0, 0, 1, 0.2); //Centro del pedal
  caja(-0.4, 0, -0.1, -0.4, 0, 1.5, 0.3, 0.2); //Paralela izquierda 
  caja(0.4, 0, -0.1, 0.4, 0, 1.5, 0.3, 0.2); //Paralela derecha

  caja(-0.3, 0, 0, 0.3, 0, 0, 0.2); //Lado trasero
  caja(-0.3, 0, 1.0, 0.3, 0, 1.0, 0.2); //Paralela media
  caja(-0.5, 0, 1.5, 0.5, 0, 1.5, 0.3, 0.2); //Paralela frontal
  
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorR);
  caja(-0.5, 0.0, 0, -0.5, 0.0, 1.5, 0.2, 0.1); //Reflectante
}

void pinion(float tam, int num_engranajes){
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glScalef(tam, 0.7, tam);
  rueda.draw();
  glPopMatrix();

  glPushMatrix();
  //Crea los engranajes
  float tamanio_engranaje = tam*0.97, x,y;
  for(int i = 0; i <= num_engranajes; i++){
    x = tamanio_engranaje*cos((M_PI/(num_engranajes/2))*i);
    y = tamanio_engranaje*sin((M_PI/(num_engranajes/2))*i);
    cilindro(1.2*x, 1.2*y, 0, x, y, 0.0, 0.1, 0.05);
  }

  glPopMatrix();
}

void creaSistemaPedales(){
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, metalicColor);

  //Brazos pedales
  glPushMatrix();

  cilindro(-0.25, 0.0, -0.8, -0.25, 0.0, 0.8, 0.2); //Conexion pedales y cuerpo

  cilindro(-0.25, 0.0, 0.75, 0.75, 0.0, 0.75, 0.2, 0.1); //Brazo pedal frontal Izquierda
  cilindro(0.75, 0.0, 0.75, 0.75, 0.0, 1.0, 0.15); //Union brazo y pedal Izquierda

  glTranslatef(-0.5,0,0);
  glRotatef(180, 0, 1, 0);

  cilindro(-0.25, 0.0, 0.75, 0.75, 0.0, 0.75, 0.2, 0.1); //Brazo pedal frontal Derecha
  cilindro(0.75, 0.0, 0.75, 0.75, 0.0, 1.0, 0.15); //Union brazo y pedal Derecha

  glPopMatrix();
  
  //Pedales
  glPushMatrix();
  pedal(0.75, 0, 1.05, 0.5, 0.5, 0.5);
  glPopMatrix();
  
  glPushMatrix(); 
  glRotatef(180, 1, 0, 0); 
  pedal(-1.25, 0, 1.05, 0.5, 0.5, 0.5);
  glPopMatrix();

  //Piñones traseros
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultColor);
  
  glPushMatrix();
  glTranslatef(-0.25, 0.0, -0.6);  
  glScalef(0.5, 0.5, 0.5);
  
  pinion(1, 36);
  glTranslatef(0, 0, 0.15);
  pinion(0.75, 24);
  glTranslatef(0, 0, 0.15);
  pinion(0.5, 16);

  float x,y;
  int num_llantas = 6;
  float tamanio_llanta = 1;

  for(int i = 0; i <= num_llantas; i++){
    x = tamanio_llanta*cos((M_PI/(num_llantas/2))*i);
    y = tamanio_llanta*sin((M_PI/(num_llantas/2))*i);
    cilindro(x/9, y/9, -0.3, x, y, -0.3, 0.5, 0.1);
  }
  glPopMatrix();


  //Piñones delanteros
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultColor);
  
  glPushMatrix();
  glTranslatef(-2.45, 0.0, -0.65);  
  glScalef(0.5, 0.5, 0.5);


  pinion(0.2, 24);  
  glTranslatef(0, 0, 0.12);
  pinion(0.3, 24);  
  glTranslatef(0, 0, 0.12);
  pinion(0.35, 24);  
  glTranslatef(0, 0, 0.12);
  pinion(0.4, 24);
  glTranslatef(0, 0, 0.12);
  pinion(0.5, 16);

  glPopMatrix();
}