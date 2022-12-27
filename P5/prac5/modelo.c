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
#include "practicasIG.h"
#include "entradaTeclado.h"

bool animacion = false, lectura = false;

//Global variables
float default_size = 2;
int modo = GL_FILL;
int sombreado1 = GL_SMOOTH, sombreado2 = GL_FLAT;
bool luz = true, luz0 = true;
int roty = 0;
char numPractica = '4', Letra;

void setModo(int M){
  modo = M;
}

void setLetra(char k){
  lectura = true;
  Letra = k;
}

void setNumPractica(){
  if(Letra == '1' or Letra == '2' or Letra == '3' or Letra == '4' or Letra == '5')
    numPractica = Letra;
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

void cambiarPuntoLuz(){ 
  luz0 = !luz0;
}

void alternarAnimacion(){
  animacion = !animacion;
}

/**	void initModel()
Inicializa el modelo y de las variables globales
**/
/*Practica 2 pero tiene texturas*/
const char *cadena = "./texturas/rajoy.jpeg";
Malla malla1("./plys/beethoven", cadena);
Malla malla2("./plys/big_dodge", cadena);
//Sin textura
ObjetoRevolucion peon("./plys/perfil" , 20, true, true);
ObjetoRevolucion fuente("./plys/miperfil", 100, true, true);

/*Practica 4*/
Cubo dado(default_size, "./texturas/dado.jpg");
ObjetoRevolucion lata("./plys/lata-pcue", "./texturas/cerveza.jpg", 0, 100);
ObjetoRevolucion tapainf("./plys/lata-pinf", "./texturas/tapas.jpg", 0.5f, 100, false, true); //x=260, y=256, radio 255
ObjetoRevolucion tapasup("./plys/lata-psup", "./texturas/tapas.jpg", 0.0f, 100, true, false); //x=770, y=257, radio 255
void initModel ()
{
  malla1.activarTextura();
  malla2.activarTextura();

  dado.activarTextura();
  lata.activarTextura();
  tapainf.activarTextura();
  tapasup.activarTextura();
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

  void asignarTextura(){};
}; 

void controlLuz(){
  GLfloat light_red[4] = { 0.8f, 0.2f, 0.2f, 1.0f};
  static GLfloat pos1[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz 1
  static GLfloat pos2[4] = { -5.0, -5.0, -10.0, 0.0 };	// Posicion de la fuente de luz 2

  glLightfv (GL_LIGHT0, GL_POSITION, pos1);	// Declaracion de luz. Colocada aqui esta fija en la escena
  glLightfv (GL_LIGHT1, GL_POSITION, pos2);	// Declaracion de luz. Colocada aqui esta fija en la escena
  glLightfv (GL_LIGHT1, GL_DIFFUSE, light_red);
  if(luz){
    glEnable (GL_LIGHTING);
    if(luz0){
      glEnable (GL_LIGHT0);
      glDisable (GL_LIGHT1);
    }
    else{
      glEnable (GL_LIGHT1);
      glDisable (GL_LIGHT0);
    }
  }
  else{
    glDisable (GL_LIGHTING);
  }
}

//Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;

/*Practica 1*/
Cubo cubo(default_size);
Piramide piramide(default_size,default_size*2);
PrismaHexagonal prisma(default_size/2, default_size);

/*Practica 3*/
Bici bici(1, 1.5, 1.5, 1);

void pick(int x, int y){
  std::cout << "Picking\n";
  GLint viewport[4];
  unsigned char data[4];

  glGetIntegerv (GL_VIEWPORT, viewport);
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);
  dibujoEscena();
  glEnable(GL_LIGHTING);
  glEnable(GL_DITHER);
  glFlush();
  glFinish();

  glReadPixels(x, viewport[3]-y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glutPostRedisplay();
}

void ColorSeleccion ( int i, int componente){
  unsigned char r = (i & 0xFF);
  unsigned char g = (componente & 0xFF);
  glColor3ub(r,g,0);
}

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/
void Dibuja (void){  
  // Activa o desactiva la iluminacion
  controlLuz();

  dibujoEscena();

  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


void dibujoEscena ()
{
  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
  
  glPushMatrix ();		// Apila la transformacion geometrica actual
  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  //Variables iluminacion y materiales
  GLfloat bright_mat[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat full_mat[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat light_red[4] = { 0.8f, 0.2f, 0.2f, 1.0f};
  GLfloat light_green[4] = { 0.2f, 0.8f, 0.2f, 1.0f};
  float black[4] = { 0.1f, 0.1f, 0.1f, 1.0f};

  ejesCoordenadas.draw();			// Dibuja los ejes
  
  //Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  //Variables P1
  float cuboC[4] = { 0.5, 0.0, 1, 1 };
  float p1Color3[4] = { 1.0, 0.0, 0, 1 };  
  float p1Color4[4] = { 0.0, 1.0, 0.0, 1 };

  setNumPractica();
  switch(numPractica){
    case '1': /*Dibuja objetos de la PRACTICA 1*/
      glPushMatrix();
        // Dibuja el cubo
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuboC);
        glColor3fv (cuboC);
        cubo.draw();                

        // Dibuja la pirámide
        glTranslatef(default_size*1.5, 0, 0);
        piramide.draw();
      
        // Figura extra 1 (toroide)
        glTranslatef(default_size*3, 0, default_size/2);
        glRotatef(90, 1, 0, 0);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color3);
        glColor3fv(p1Color3);
        glutSolidTorus(default_size/2, default_size, 24, 32);
      glPopMatrix();
      
      glPushMatrix();
        // Figura extra 2 (cono)
        glTranslatef(1, 0, 2.5*default_size);

        glRotatef(-90, 1, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color4);
        glColor3fv(p1Color4);
        glutSolidCone(default_size/2,default_size,24,20);
      glPopMatrix();

      glPushMatrix();
        //Figura extra 3 (prisma base hexagonal)
        glTranslatef(default_size*1.5, 0, 2*default_size);
        prisma.draw();
      glPopMatrix();

      break;
  case '2':  
    /*Dibuja P2 con iluminacion y materiales de la P4*/
      glTranslatef(-13, 0, 0); 
      //bethoween
      malla1.setMaterial(light_red, light_red);
      ColorSeleccion(0,100);
      malla1.draw();

    //Coche
      glTranslatef(13, 0, 0); 
      malla2.setMaterial(light_green, light_green);
      ColorSeleccion(0,100);
      malla2.draw();

    //Peon
    glTranslatef(11, 0, 0);    
    glPushMatrix();
      glScalef(2, 2, 2); //Escalamos el peon
      glEnable(GL_NORMALIZE); //Al escalar, hay que renormalizar las normales  
      malla2.setMaterial(black, black);
      ColorSeleccion(0,100);
      peon.draw();
    glPopMatrix();
    
    //Fuente
      glTranslatef(8, 0, 0);
      fuente.setMaterial(full_mat, full_mat);
      ColorSeleccion(0,100);
      fuente.draw();
    break;
  case '3':
    if(lectura){
      bici.entradaTecladoBici(Letra);
      lectura = false;
    }
    bici.draw(); 
    break;
  case '4':
    /*Dibuja objetos de la PRACTICA 4*/
    //Peon 1
    glTranslatef(-6.0,0,0);

    // glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(0,1.4,0);
      peon.setMaterial(black, black);
      peon.draw();
    // glPopAttrib();
    //Peon 2
    // glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(3,0,0);
      peon.setMaterial(light_red, light_red, full_mat, 100);
      peon.draw();
    // glPopAttrib();

    //Peon 3
    // glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(3,0,0);
      peon.setMaterial(light_green, light_green, bright_mat);
      peon.draw();
    // glPopAttrib();
    glTranslatef(2,0,0);

    glTranslatef(0,-1.4, 0);
    glPushMatrix();
      glTranslatef(0,0,-1);
      //Cubo con textura de dado
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, full_mat);
      glColor3fv (full_mat);
      glEnable(GL_TEXTURE_2D);
      dado.draw();
    glPopMatrix();

    glTranslatef(4,0,0);

    glEnable(GL_NORMALIZE);
    glRotatef(90, 0, 1, 0);
    glScalef(2,2,2);
    lata.draw();

    tapainf.draw();
    tapasup.draw();
    glDisable(GL_TEXTURE_2D);

    break;
    case '5': //Es la 2 con texturas
      glEnable(GL_TEXTURE_2D);
        glTranslatef(-5, 0, 0); 
        //bethoween
        malla1.setMaterial(full_mat, full_mat);
        malla1.draw();

        //Coche
        glTranslatef(13, 0, 0); 
        malla2.setMaterial(full_mat, full_mat);
        malla2.draw();
      glDisable(GL_TEXTURE_2D);
      break;
    /*Dibuja objetos de la PRACTICA 3*/
  }
  
  glPopMatrix();
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  //Animacion bici
  if(animacion){
    static int sentido = 1, bajaSube = 1;

    /*Ejecutores de animacion*/
    //Desplazamiento
    if(sentido == 1)
      bici.entradaTecladoBici('E'); //Hacia delante
    else
      bici.entradaTecladoBici('e'); //Hacia atras

    //Sillin
    if(bajaSube == 1)
      bici.entradaTecladoBici('T');
    else
      bici.entradaTecladoBici('t');

    /*Disparadores de animacion*/
    if(bici.avance >= 20)
      sentido = -1;
    if(bici.avance <= -20)
      sentido = 1;

    if(bici.altura_sillin >= 1)
      bajaSube = -1;
    if(bici.altura_sillin <= -0.5)
      bajaSube = 1;

  }
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}