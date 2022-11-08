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
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "bici.h"
#include "practicasIG.h"

//Global variables
float default_size = 2;
int modo = GL_FILL;
int sombreado1 = GL_SMOOTH, sombreado2 = GL_FLAT;
bool luz = true;
int roty = 0;

void setModo(int M){
  modo = M;
}

void invertirSombreado(){
  if(sombreado1 == GL_FLAT){
    sombreado1 = GL_SMOOTH;
    sombreado2 = GL_FLAT;
  }
  else{
    sombreado1 = GL_FLAT;
    sombreado2  = GL_SMOOTH;
  }
}

int getSombreado(){
  return sombreado1;
}

//Cambia el estado de la iluminacion(si true entonces false y viceversa)
void invertirIluminacion(){ 
  luz = !luz;
}

/**	void initModel()
Inicializa el modelo y de las variables globales
**/
void
initModel ()
{

}

class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
  void draw()
  {
    glDisable (GL_LIGHTING);
    glBegin (GL_LINES);
    {
      glColor3f (0, 1, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (0, longitud, 0);

      glColor3f (1, 0, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (longitud, 0, 0);

      glColor3f (0, 0, 1);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, longitud);
    }
    glEnd ();
      if(/*modo == GL_FILL and*/ luz) {//Modo: Solido con iluminacion
        glEnable (GL_LIGHTING);
      }
  }
}; 

//Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;

/*Practica 1*/
// Cubo cubo(default_size);
// Piramide piramide(default_size,default_size*2);
// PrismaHexagonal prisma(default_size/2, default_size);

/*Practica 2*/
// Malla malla1("./plys/beethoven");
// Malla malla2("./plys/big_dodge");
// ObjetoRevolucion peon("./plys/perfil", 20,true, true);
// ObjetoRevolucion fuente("./plys/fuente", 100, true, true);

/*Practica 3*/

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/
void Dibuja (void)
{
  static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  //Activa o desactiva la iluminacion
  if(luz){
    glEnable (GL_LIGHTING);
  }
  else{
    glDisable (GL_LIGHTING);
  }

  ejesCoordenadas.draw();			// Dibuja los ejes
  
  //Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  
  /*Dibuja objetos de la PRACTICA 1*/
  /*
  float p1Color3[4] = { 1.0, 0.0, 0, 1 };
  float p1Color4[4] = { 0.0, 1.0, 0.0, 1 };
  
  // Dibuja el cubo
  cubo.draw();                

  // Dibuja la pirámide
  glTranslatef(default_size*1.5, 0, 0);
  piramide.draw();

  // Figura extra 1 (toroide)
  glTranslatef(default_size*3, 0, default_size/2);
  glRotatef(90, 1, 0, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color3);
  glutSolidTorus(default_size/2, default_size, 24, 32);
  glRotatef(-90, 1, 0, 0);

  // Figura extra 2 (cono)
  glTranslatef(-4*default_size, 0, 2*default_size);
  glRotatef(-90, 1, 0, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color4);
  glutSolidCone(default_size,default_size,24,20);

  glRotatef(90, 1, 0, 0);

  //Figura extra 3 (prisma base hexagonal)
  glTranslatef(default_size*1.5, 0, -default_size/2);
  prisma.draw();
  */
  /*Dibuja objetos de la PRACTICA 2*/
  /*
  float colorMalla1[4] = { 1.0, 0.0, 0.0, 1};
  float colorMalla2[4] = { 0.0, 1.0, 0.0, 1};
  float revolucion1[4] = { 1.0, 1.0, 0.0, 1};
  float revolucion2[4] = { 1.0, 1.0, 1.0, 1};

  //Malla beethoven sombreado suave
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorMalla1);
  glTranslatef(-17, 0, 0);  
  malla1.draw();

  //Malla coche sombreado plano
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorMalla2);
  glTranslatef(13, 0, 0);  
  malla2.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, revolucion1);
  glTranslatef(11, 0, 0);
  
  glScalef(2, 2, 2); //Escalamos el peon
  glEnable(GL_NORMALIZE); //Al escalar, hay que renormalizar las normales  
  peon.draw();
  glScalef(0.5, 0.5, 0.5); //Escalamos el peon
  
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, revolucion2);
  glTranslatef(8, 0, 0);
  fuente.draw();
  */
  /*Dibuja objetos de la PRACTICA 3*/

  float biciC[4] = { 1.0, 1.0, 1.0, 1};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, biciC);
  // creaCuerpoBici();
  creaRuedas();

  glPopMatrix();
  
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  //roty+=5.0;
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}