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
#include "practicasIG.h"
#include <vector>

//Global variables
float default_size = 2;
int modo = GL_FILL;
bool luz = true;

void setModo(int M){
  modo = M;
}

//Cambia el estado de la iluminacion(si true entonces false y viceversa)
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
    if(modo == GL_FILL and luz) {//Modo: Solido con iluminacion
      glEnable (GL_LIGHTING);
    }
}
} ; 

//Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;
Cubo cubo(default_size);
Piramide piramide(default_size,default_size*2);
PrismaHexagonal prisma(default_size/2, default_size);

//Malla
class Malla:Objeto3D{

  private:
    std::vector <float> vertices;
    std::vector <int> caras;
    std::vector <float> normal;

  public:
    Malla(const char *nombre_archivo){
      ply::read(nombre_archivo, vertices, caras);
    }

    void calcular_normales(int i){
      int iv = caras[i]*3;
      int iv1 = caras[i+1]*3;
      int iv2 = caras[i+2]*3;

      //Obtenemos los vertices de los 2 vectores
      std::vector <float> v = {vertices[iv], vertices[iv+1], vertices[iv+2]};
      std::vector <float> v1 = {vertices[iv1], vertices[iv1+1], vertices[iv1+2]};
      std::vector <float> v2 = {vertices[iv2], vertices[iv2+1], vertices[iv2+2]};

      //Obtenemos los vectores a partir de los vertices
      std::vector <float> A = {v[0] - v1[0], v[1] - v1[1], v[2] - v1[2]};
      std::vector <float> B = {v[0] - v2[0], v[1] - v2[1], v[2] - v2[2]};

      //Calculamos la normal de los dos vectores
      float normal_x = A[1]*B[2] - A[2]*B[1];
      float normal_y = A[2]*B[0] - A[0]*B[2];
      float normal_z = A[0]*B[1] - A[1]*B[0];
      
      //Calculamos el modulo de la normal
      float modulo = sqrt(normal_x*normal_x + normal_y*normal_y + normal_z*normal_z);

      //Volcamos el resultado en el vector de normal
      normal = {normal_x/modulo, normal_y/modulo, normal_z/modulo};

    }

    void draw(){
      glBegin(GL_TRIANGLES);
      {
        for(int i = 0; i < caras.size()-3; i+=3){
          int iv = caras[i]*3;
          int iv1 = caras[i+1]*3;
          int iv2 = caras[i+2]*3;
  
          calcular_normales(i);

          glNormal3f(normal[0], normal[1], normal[2]);
          glVertex3f(vertices[iv], vertices[iv+1], vertices[iv+2]);
          glVertex3f(vertices[iv1], vertices[iv1+1], vertices[iv1+2]);
          glVertex3f(vertices[iv2], vertices[iv2+1], vertices[iv2+2]);
        }
      }
      glEnd();
    }
};
Malla malla("./plys/beethoven");

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja (void)
{
  //glShadeModel(GL_FLAT);
  static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color3[4] = { 1.0, 0.0, 0, 1 };
  float  color4[4] = { 0.0, 1.0, 0.0, 1 };

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

  malla.draw();
  //Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  // Dibuja el cubo
  //cubo.draw();                

  // Dibuja la pirámide
  glTranslatef(default_size*1.5, 0, 0);
  piramide.draw();

  //Figura extra 1 (toroide)
  glTranslatef(default_size*3, 0, default_size/2);
  glRotatef(90, 1, 0, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  glColor3f (color3[0], color3[1], color3[2]);
  //glutSolidTorus(default_size/2, default_size, 24, 32);
  glRotatef(-90, 1, 0, 0);

  //Figura extra 2 (cono)
  glTranslatef(-4*default_size, 0, 2*default_size);
  glRotatef(-90, 1, 0, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  glColor3f (color4[0], color4[1], color4[2]);
  //glutSolidCone(default_size,default_size,24,20);

  glRotatef(90, 1, 0, 0);

  //Figura extra 3 (prisma base hexagonal)
  glTranslatef(default_size*1.5, 0, -default_size/2);
  //prisma.draw();

  glPopMatrix();
  
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
