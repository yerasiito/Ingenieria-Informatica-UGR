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
#include "bici.h"

ObjetoRevolucion pieza("./plys/cilindro", 32, true, true);

/*
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
	glPushMatrix();
	  float m;
	  m= modulo(x1-x0,y1-y0,z1-z0);

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
Crea un ortoedro con las bases en x0,y0,z0 y x1,y1,z1, y profundidad de la base a.
**/
void ortoedro(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b = 0)
{
  glPushMatrix();
    float m;
	  m= modulo(x1-x0,y1-y0,z1-z0);

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

Bici::Bici(float escalar, float escala_rueda1, float escala_rueda2, float grosor_rueda){
  sillin = Malla("./plys/sillin");
	rueda = ObjetoRevolucion("./plys/rueda",32, false, false);
  escale = escalar;
  glScalef(escale, escale, escale);
  //Para que las ruedas no solapen el cuerpo
  if(escala_rueda1/escalar > 1.85) escala_r1 = 1.85*escalar; //maximo trasera
  else escala_r1 = escala_rueda1;
  
  if(escala_rueda2/escalar > 1.7) escala_r2 = 1.7*escalar; //maximo delantera
  else escala_r2 = escala_rueda2;

  grosor_r = grosor_rueda;
}

void Bici::creaCuerpoBici(){
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuerpoColor);
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
  glPopMatrix();

  //Añillo sillin
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuerpoColor);
    glTranslatef(-0.87,2.5,0);
    glRotatef(15, 0, 0, 1);
    glScalef(0.11,1,0.11);
    rueda.draw();
  glPopMatrix();

}

void Bici::Rueda(){
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ruedaColor);
  //Rueda delantera
  glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glScalef(escala_r2, grosor_r, escala_r2);
    rueda.draw();
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, llantaColor);
  //Llantas delantera
  glPushMatrix();
    float x,y, x1, y1, desfase = 0.15;
    int num_llantas = 24;
    float tamanio_llanta = escala_r2;
    glRotatef(3*M_PI*avance*multiplicador, 0, 0, -1);
    for(int i = 0; i <= num_llantas; i++){
      if(i == num_llantas-1) //Resalta una de las llantas para ver que giran
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorR);

      x = tamanio_llanta*cos((M_PI/(num_llantas/2))*i + desfase);
      y = tamanio_llanta*sin((M_PI/(num_llantas/2))*i + desfase);

      x1 = cos((M_PI/(num_llantas/2))*i);
      y1 = sin((M_PI/(num_llantas/2))*i);

      cilindro(x1/4.6, y1/4.6, -0.3, x, y, 0.0, 0.05);
      cilindro(x1/4.6, y1/4.6, 0.3, x, y, 0.0, 0.05);
    }

  glPopMatrix();
}

void Bici::creaRuedas(){
  float pos_rTrasera = -2.45*escale;
  float pos_rDelantera = +2.45*escale;
  
  //Rueda trasera
  glPushMatrix();
    glTranslatef(pos_rTrasera, 0, 0);
    glRotatef(3*M_PI*avance*multiplicador, 0, 0, -1);
    Rueda();
  glPopMatrix();

  //Rueda delantera
  glPushMatrix();
    glTranslatef(pos_rDelantera, 0, 0);
    glRotatef(3*M_PI*avance*multiplicador, 0, 0, -1);
    Rueda();
  glPopMatrix();
}

void Bici::pedal(float pos_x, float pos_y, float pos_z, float tam_x, float tam_y, float tam_z){
  glPushMatrix();

    glTranslatef(pos_x, pos_y, pos_z);
    glScalef(tam_x, tam_y, tam_z);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pedalColor);
    ortoedro(0, 0, 0, 0, 0, 1, 0.2); //Centro del pedal
    ortoedro(-0.4, 0, -0.1, -0.4, 0, 1.5, 0.3, 0.2); //Paralela izquierda 
    ortoedro(0.4, 0, -0.1, 0.4, 0, 1.5, 0.3, 0.2); //Paralela derecha

    ortoedro(-0.3, 0, 0, 0.3, 0, 0, 0.2); //Lado trasero
    ortoedro(-0.3, 0, 1.0, 0.3, 0, 1.0, 0.2); //Paralela media
    ortoedro(-0.5, 0, 1.5, 0.5, 0, 1.5, 0.3, 0.2); //Paralela frontal
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorR);
    ortoedro(-0.5, 0.0, 0, -0.5, 0.0, 1.5, 0.2, 0.1); //Reflectante
  glPopMatrix();
}

void Bici::pinion(float tam, int num_engranajes){
  //Disco del piñon
  glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glScalef(tam, 0.7, tam);
    rueda.draw();
  glPopMatrix();

  //Crea los engranajes
  glPushMatrix();
    float tamanio_engranaje = tam*0.97, x,y;
    for(int i = 0; i <= num_engranajes; i++){
      x = tamanio_engranaje*cos((M_PI/(num_engranajes/2))*i);
      y = tamanio_engranaje*sin((M_PI/(num_engranajes/2))*i);
      cilindro(1.2*x, 1.2*y, 0, x, y, 0.0, 0.1, 0.05);
    }
  glPopMatrix();
}

void Bici::cadenas(int num_cadenas, float pendiente){
  glPushMatrix();
    for(int i = 0; i <= num_cadenas; i++){
      cilindro(0, 0, 0.01, 0.1, pendiente, 0.01, 0.05, 0.02); //Extension trasera
      cilindro(0, 0, 0.09, 0.1, pendiente, 0.09, 0.05, 0.01); //Extension delantera
      cilindro(0, 0, 0, 0, 0, 0.1, 0.05); //Cilindro izquierdo
      glTranslatef(0.1, pendiente, 0);
    }
  glPopMatrix();
}

void Bici::creaSistemaPedales(){
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
  pedal(0.75, 0, 1.05, 0.5, 0.5, 0.5);
  
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

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultColor);
  
  //Piñones delanteros  
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

  //Cadenas
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sillinColor);
  
  //Inferior
  glPushMatrix();
    glTranslatef(-2.5, -0.2, -0.58);
    cadenas(22, -0.01);
  glPopMatrix();
  
  //Cirfunferencia piñon izquierdo
  glPushMatrix();
    glTranslatef(-0.25, 0.0, -0.58);
    int num_cadenas = 25;
    float tamanio_penion = 0.43;
    float x1,y1;
    for(int i = -num_cadenas/4; i < num_cadenas/4; i++){
      x = tamanio_penion*cos(M_PI/(num_cadenas/2)*i);
      y = tamanio_penion*sin(M_PI/(num_cadenas/2)*i);

      x1 = tamanio_penion*cos(M_PI/(num_cadenas/2)*(i+1));
      y1 = tamanio_penion*sin(M_PI/(num_cadenas/2)*(i+1));
      cilindro(x, y, 0.01, x1, y1, 0.01, 0.02); //Extension trasera
      cilindro(x, y, 0.09, x1, y1, 0.09, 0.05, 0.01); //Extension delantera
      cilindro(x, y, 0, x, y, 0.1, 0.05); //Cilindro izquierdo
    }
    cilindro(x1, y1, 0, x1, y1, 0.1, 0.05); //Cilindro izquierdo
  glPopMatrix();

  //Cirfunferencia piñon derecho
  glPushMatrix();
    glTranslatef(-2.5, 0.0, -0.58);
    tamanio_penion = 0.2;
    num_cadenas = 20;
    for(int i = num_cadenas/4; i < 3*num_cadenas/4; i++){
      x = tamanio_penion*cos(M_PI/(num_cadenas/2)*i);
      y = tamanio_penion*sin(M_PI/(num_cadenas/2)*i);

      x1 = tamanio_penion*cos(M_PI/(num_cadenas/2)*(i+1));
      y1 = tamanio_penion*sin(M_PI/(num_cadenas/2)*(i+1));
      cilindro(x, y, 0.01, x1, y1, 0.01, 0.02); //Extension trasera
      cilindro(x, y, 0.09, x1, y1, 0.09, 0.05, 0.01); //Extension delantera
      cilindro(x, y, 0, x, y, 0.1, 0.05); //Cilindro izquierdo
    }
    cilindro(x1, y1, 0, x1, y1, 0.1, 0.05); //Cilindro izquierdo
  glPopMatrix();

  //Superior
  glPushMatrix();
    glTranslatef(-2.5, 0.2, -0.58);
    cadenas(22, 0.01);
  glPopMatrix();

}

void Bici::draw(){
  //Animacion
  glRotatef(angulo, 0, 1, 0); //Gira sobre si misma
  glTranslatef(avance, 0, 0); //Se mueve hacia delante y atrás

  glPushMatrix();
    glScalef(escale, escale, escale); 
    creaCuerpoBici();
    creaSistemaPedales();
  glPopMatrix();
  
  glPushMatrix();
    creaRuedas();
  glPopMatrix();
}