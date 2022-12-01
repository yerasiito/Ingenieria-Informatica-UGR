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

Bici bici(1, 1.5, 1.5, 1);
bool animacion = false;

void entradaTecladoBici(unsigned char letra){
  switch(letra){
    case 'R':
      bici.angulo += 5;
      if ( bici.angulo > 360) bici.angulo -=360;
      break;
    case 'r':
      bici.angulo -= 5;
      if ( bici.angulo < 0) bici.angulo +=360;
      break;
    case 'W':
      bici.avance += 0.5*bici.multiplicador;
      bici.rota_rueda = 2*M_PI*bici.avance*bici.multiplicador;   
      bici.giro_pedales -= 5; 
      bici.it--;  
      bici.numero_rotacion_pedales = 180/(5*bici.multiplicador);
      break;
    case 'w':
      bici.avance -= 0.5*bici.multiplicador;
      bici.rota_rueda = 2*M_PI*bici.avance*bici.multiplicador;
      bici.giro_pedales += 5;
      bici.it++;
      bici.numero_rotacion_pedales = 180/(5*bici.multiplicador);
      break;
    case 'T':
      if(bici.altura_sillin >= 1) bici.altura_sillin = 1;
      else bici.altura_sillin += 0.1;
      break;
    case 't':
      if(bici.altura_sillin <= -0.5) bici.altura_sillin = -0.5;
      else bici.altura_sillin -= 0.1;
      break;
    case 'D':
      bici.numero_rotacion_pedales = 180/(5*bici.multiplicador);
      bici.giro_pedales += 5;
      bici.it++;
      break;
    case 'd':
      bici.numero_rotacion_pedales = 180/(5*bici.multiplicador);
      bici.giro_pedales -= 5;
      bici.it--;
      break;
    case 'N':
      bici.rota_rueda -= 2*M_PI*1*bici.multiplicador; 
      break;
    case 'n':
      bici.rota_rueda += 2*M_PI*1*bici.multiplicador; 
      break;
    case 'F':
    case 'f':
      bici.multiplicador = 1;
      break;
    case 'G':
    case 'g':
      bici.multiplicador = 2;
      break;
    case 'H':
    case 'h':
      bici.multiplicador = 2.5;
      break;
    case 'J':
    case 'j':
      bici.multiplicador = 2.75;
      break;
    case 'K':
    case 'k':
      bici.multiplicador = 3;
      break;
  }
}

//Global variables
float default_size = 2;
int modo = GL_FILL;
int sombreado1 = GL_SMOOTH, sombreado2 = GL_FLAT;
bool luz = true;
int roty = 0;
char modelLetra = '3';

void setModo(int M){
  modo = M;
}

void setmodelLetra(char k){
  if(k == '1' or k == '2' or k == '3' or k == '4' or k == '5')
    modelLetra = k;
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

void alternarAnimacion(){
  animacion = !animacion;
}

/**	void initModel()
Inicializa el modelo y de las variables globales
**/
Cubo dado(default_size, "./texturas/dado.jpg");
ObjetoRevolucion lata("./plys/lata-pcue", "./texturas/cerveza.jpg", 0.25f, 100); //El 0/1 indica el algoritmo de texturizacion
ObjetoRevolucion tapainf("./plys/lata-pinf", "./texturas/tapas.jpg", 0.5f, 100, false, true); //x=260, y=256, radio 255
ObjetoRevolucion tapasup("./plys/lata-psup", "./texturas/tapas.jpg", 0.0f, 100, true, false); //x=770, y=257, radio 255
void initModel ()
{
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

//Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;

/*Practica 1*/
Cubo cubo(default_size);
Piramide piramide(default_size,default_size*2);
PrismaHexagonal prisma(default_size/2, default_size);

/*Practica 2*/
Malla malla1("./plys/beethoven");
Malla malla2("./plys/big_dodge");
ObjetoRevolucion peon("./plys/perfil", 20,true, true);
ObjetoRevolucion fuente("./plys/miperfil", 100, true, true);
/*Practica 4*/
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

  // Activa o desactiva la iluminacion
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

  //Variables P1
  float  cuboC[4] = { 0.5, 0.0, 1, 1 };
  float p1Color3[4] = { 1.0, 0.0, 0, 1 };  
  float p1Color4[4] = { 0.0, 1.0, 0.0, 1 };

  //Variables P2
  GLfloat no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat full_mat[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat colorMalla1[4] = { 0.8, 0.2, 0.2, 1.0f};
  GLfloat colorMalla2[4] = { 0.2, 0.8, 0.2, 1.0f};
  float peonColor[4] = { 0.1, 0.1, 0.1, 1};
  float revolucion2[4] = { 1.0, 1.0, 1.0, 1};
  float revolucionI2[4] = { 0.2, 0.2, 0.8, 1};

  //Variables P3

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  switch(modelLetra){
    case '1': /*Dibuja objetos de la PRACTICA 1*/
      glPushAttrib(GL_LIGHTING_BIT);
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

      glPopMatrix();
      glPopAttrib();
      break;
  case '2':  
    /*Dibuja P2 con iluminacion y materiales de la P4*/

    glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(-13, 0, 0); 
      //bethoween
      malla1.setMatAmbient(colorMalla1);
      malla1.setMatDiffuse(colorMalla1);
      malla1.setMatSpecular(full_mat);
      malla1.setSpecularExponent(100);
      malla1.setMatEmission(no_mat);
      malla1.draw();
    glPopAttrib();

    //Coche
    glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(13, 0, 0); 
      malla2.setMatAmbient(colorMalla2);
      malla2.setMatDiffuse(colorMalla2);
      malla2.draw();
    glPopAttrib();


    //Peon
    glTranslatef(11, 0, 0);    
    glPushMatrix();
      glScalef(2, 2, 2); //Escalamos el peon
      glEnable(GL_NORMALIZE); //Al escalar, hay que renormalizar las normales  
      peon.setMatAmbient(peonColor);
      peon.draw();
    glPopMatrix();
    glPopAttrib();
    
    //Fuente
    glPushAttrib(GL_LIGHTING_BIT);
      glTranslatef(8, 0, 0);
      fuente.setMatAmbient(revolucion2);
      fuente.setMatDiffuse(revolucion2);
      fuente.setMatEmission(revolucionI2);
      fuente.draw();
    glPopAttrib();
    glPopMatrix();

    break;
  case '3':
    glPushAttrib(GL_LIGHTING_BIT);
      bici.draw(); 
    glPopAttrib();
    break;
  case '4':
    //Dado con textura
    glPushAttrib(GL_LIGHTING_BIT);
    // glTranslatef(-1,-1,-1);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, revolucion2);
    glColor3fv (revolucion2);
    glEnable(GL_TEXTURE_2D);

    dado.draw();
    
    glTranslatef(3,0,0);

    /*Dibuja objetos de la PRACTICA 4*/
    glEnable(GL_NORMALIZE);
    glRotatef(90, 0, 1, 0);
    lata.draw();

    tapainf.draw();
    tapasup.draw();

    glPopAttrib();
    glDisable(GL_TEXTURE_2D);

    break;
  /*Dibuja objetos de la PRACTICA 3*/
  }
    glPopMatrix();
  
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
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
      entradaTecladoBici('W'); //Hacia delante
    else
      entradaTecladoBici('w'); //Hacia atras

    //Sillin
    if(bajaSube == 1)
      entradaTecladoBici('T');
    else
      entradaTecladoBici('t');

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