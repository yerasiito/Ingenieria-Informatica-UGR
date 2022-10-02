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
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <vector>
#include "practicasIG.h"


//Global variables
float default_size = 2;
int modo = GL_FILL;
bool luz = true;

void setModo(int M){
  modo = M;
}

void setIluminacion(){
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
void draw( )
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
  if(luz)
    glEnable (GL_LIGHTING);

}
} ; 

Ejes ejesCoordenadas;

class Cubo:Objeto3D
{
public:
  float l = 1;

Cubo(float lado){
  l = lado;
}
// Dibuja el cubo
void draw( )
{
  glBegin (GL_QUAD_STRIP);
  {				/* Caras transversales */
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (l, l, l);
    glVertex3f (0, l, l);
    glVertex3f (l, 0, l);
    glVertex3f (0, 0, l);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (l, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (l, l, 0);
    glVertex3f (0, l, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (l, l, l);
    glVertex3f (0, l, l);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {				/* Costados */
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (l, 0, 0);
    glVertex3f (l, l, 0);
    glVertex3f (l, l, l);
    glVertex3f (l, 0, l);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, l);
    glVertex3f (0, l, l);
    glVertex3f (0, l, 0);
  }
  glEnd ();
}
} ;

Cubo cubo(default_size);


class Piramide:Objeto3D
{
public:
  float lado = 1;
  float alto = 1;
  float Nx=0,Ny=0; //Normales de la piramide regular

Piramide(float l, float h){
  lado = l;
  alto = h;
}

//Dados 2 longitudes (vectores) que forman un triangulo rectangulo, calcula la normal
void calcularNormal(float base, float altura){
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

void draw( )
{
  calcularNormal(lado, alto);
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
    glNormal3f (0, Ny, -Nx);
    glVertex3f (lado, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (lado/2, alto, lado/2);

    //Lateral izquierdo
    glNormal3f (-Nx, Ny, 0);
    glVertex3f (0, 0, lado);
    
    //Frontal
    glNormal3f (0, Ny, Nx);
    glVertex3f (lado, 0, lado);

    //Lateral derecho
    glNormal3f (Nx, Ny, 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, 0, lado);
    glVertex3f (lado/2, alto, lado/2);

  }
  glEnd ();
}
} ;

Piramide piramide(default_size,default_size);


//Malla
class Malla:Objeto3D{

  private:
    std::vector <float> vertices;
    std::vector <int> caras;

  public:
    Malla(const char *nombre_archivo){
      ply::read(nombre_archivo, vertices, caras);
      calcular_normales();
    }

    void calcular_normales(){
      std::cout << "\nCaras: " << caras.size() << "\n";
      for(auto it : caras){
        std::cout << it << " ";
      }
      std::cout << "\nVertices: " << vertices.size() << "\n";
      for(auto it : vertices){
        std::cout << it << " ";
      }
      std::cout << "\n";
    }

    void draw(){
        printf("Por implementar\n");
    }
};
Malla malla("./plys/perfil");


/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/
void Dibuja (void)
{
  static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 0.5, 0.0, 1, 1 };
  float  color2[4] = { 0.0, 0.5, 0.8, 1 };
  float  color3[4] = { 1.0, 0.0, 0, 1 };
  float  color4[4] = { 0.0, 1, 0, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  //Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  //Activa o desactiva la iluminacion
  if(luz){
    glEnable (GL_LIGHTING);
  }
  else{
    glDisable (GL_LIGHTING);
  }

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  
  /* //Practica 1
  // Dibuja el cubo
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);  
  cubo.draw();                

  // Dibuja la pirámide
  glTranslatef(default_size, 0, default_size);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  piramide.draw();

  //Figura extra 1
  glTranslatef(default_size+default_size/1.5, 0, default_size+default_size/1.5);
  glRotatef(90, 1, 0, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  glutSolidTorus(0.5, 1, 24, 32);
  glRotatef(-90, 1, 0, 0);

  //Figura extra 2
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  glTranslatef(default_size, 0, default_size);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1,1,24,20);

  */
  //Practica 2


  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion

}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
