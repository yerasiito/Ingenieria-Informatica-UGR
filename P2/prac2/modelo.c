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
#include <set>

//Global variables
float default_size = 2;
int modo = GL_FILL;
int draw_model = GL_FLAT;
bool luz = true;

void setModo(int M){
  modo = M;
}

void setDrawModel(int M){
  draw_model = M;
}

int getDrawModel(){
  return draw_model;
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
      if(/*modo == GL_FILL and*/ luz) {//Modo: Solido con iluminacion
        glEnable (GL_LIGHTING);
      }
  }
} ; 

class ObjetoRevolucion:public Malla
{
  public:
    int n = 100; //Numero de revoluciones
    int m; //Numero de vertices del perfil inicial

  ObjetoRevolucion(const char *nombre_archivo, bool tapa_sup, bool tapa_inf){
    
    ply::read_vertices(nombre_archivo, vertices);
    m = vertices.size()/3;
    
    crear_tapas(tapa_sup, tapa_inf);
    crearRevolucion();

    normales_caras();
    normales_vertices();
  }

  void crearRevolucion(){
    vertices = {};
    //Añade al vertices final todos los vertices rotados


    for(int i = 0; i < n-1; i++){
      float alfa = (2*M_PI*i)/(n-1);
      for(int j = 0; j <= m*3-1; j+=3){
        std::vector<float> vi = {vertices[j]*cos(alfa), vertices[j+1], vertices[j]*sin(alfa)};
        vertices.insert(vertices.end(), vi.begin(), vi.end());
      }
    }


    //Duplica los vertices del perfil al final
    for(int j = 0; j <= m*3-1; j+=3){
      std::vector<double> vi = {vertices[j]*cos(0), vertices[j+1], vertices[j]*sin(0)};
      vertices.insert(vertices.end(), vi.begin(), vi.end());
    }

    //Crear el vector de caras
    caras = {};
    int k = 0;
    for(int i = 0; i <= n-2; i++){
      for(int j = 0; j <= m-2; j++){
        k = i * m + j;
        std::vector<int> triangle1 = {k+m+1, k+m, k};
        std::vector<int> triangle2 = {k+1, k+m+1, k};
        caras.insert(caras.end(), triangle1.begin(), triangle1.end());
        caras.insert(caras.end(), triangle2.begin(), triangle2.end());
      }
    }

  }

  void crear_tapas(bool tapa_sup, bool tapa_inf){
    float min = 9999999, max = -999999999;
    for(int i = 1; i < vertices.size(); i+=3){
      if(vertices[i] < min)
        min = vertices[i];
      if(vertices[i] > max)
        max = vertices[i];
    }

    if(tapa_inf){
      std::vector<float> ver_inf = {0, min, 0};
      vertices.insert(vertices.begin(), ver_inf.begin(), ver_inf.end());
      m+=1;
    }

    if(tapa_sup){
      std::vector<float> ver_sup = {0, max, 0};
      vertices.insert(vertices.end(), ver_sup.begin(), ver_sup.end());
      m+=1;
    }
  }

  void draw_lines(){

    size_t j = 0;
    while(j < vertices.size()){
      glBegin(GL_LINE_STRIP);
      {
        for(int i = 0; i < m; i+=3){
          glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
          j+=3;
        }
      }
      glEnd();
    }
  }

  void draw_points(){
    glBegin(GL_POINTS);
    {
      for(size_t i = 0; i < vertices.size(); i+=3){
        glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
      }
    }
    glEnd();
  }

  // void draw(){
  //   glBegin(GL_POINTS);
  //   {
  //     glVertex3f(vertices[caras[2]], vertices[caras[2]+1], vertices[caras[2]+2]);
  //     int i = 185;
  //     glVertex3f(vertices[caras[i]], vertices[caras[i]+1], vertices[caras[i]+2]);
  //     i = 365;
  //     glVertex3f(vertices[caras[i]], vertices[caras[i]+1], vertices[caras[i]+2]);
  //   //   for(int i = 0; i < n; i++){
  //   //     glVertex3f(vertices[i*m*3],vertices[i*m*3+1], vertices[i*m*3+2]);
  //   //     std::cout << caras[i*m] << "\n";
  //   //   }
  //   // }
  //   glEnd();
  //   }
  // }
};

//Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;
Cubo cubo(default_size);
Piramide piramide(default_size,default_size*2);
PrismaHexagonal prisma(default_size/2, default_size);
Malla malla1("./plys/beethoven");
Malla malla2("./plys/big_dodge");
ObjetoRevolucion perfil("./plys/miperfil", true, true);

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/

void Dibuja (void)
{
  glShadeModel(draw_model);  
  static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
  
  float colorMalla[4] = { 1.0, 1.0, 1.0, 1};
  float color3[4] = { 1.0, 0.0, 0, 1 };
  float color4[4] = { 0.0, 1.0, 0.0, 1 };

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

  //Dibuja la malla
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorMalla);
  //malla1.draw();
  //glTranslatef(10, 0, 0);  
  //malla2.draw();

  //glTranslatef(0, 10, 0);
  perfil.draw();
  //Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  // Dibuja el cubo
  //cubo.draw();                

  // Dibuja la pirámide
  glTranslatef(default_size*1.5, 0, 0);
  //piramide.draw();

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