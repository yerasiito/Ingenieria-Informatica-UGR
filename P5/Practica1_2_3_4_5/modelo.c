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
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "entradaTeclado.h"
#include "bici.h"

bool animacion = false, lectura = false;
typedef enum
{
  NONE,
  COLOR,
  TRANSFORMAR
} accionesMenu;

// Global variables
float default_size = 1;
int modo = GL_FILL;
int sombreado1 = GL_SMOOTH, sombreado2 = GL_FLAT;
bool luz = true, luz0 = true, modoTextura = true;
int roty = 0, accionActual = NONE;
float r = 0, g = 0;
char numPractica = '9', Letra;
GLfloat seleccionado[4] = {1, 0, 1, 1}, aseleccionado[4];
void setModo(int M)
{
  modo = M;
}

void setLetra(char k)
{
  lectura = true;
  Letra = k;
}

void setNumPractica()
{
  if (Letra == '1' or Letra == '2' or Letra == '3' or Letra == '4' or Letra == '5' or Letra == '6' or Letra == '7' or Letra == '8' or Letra == '9')
    numPractica = Letra;
}

void invertirSombreado()
{
  if (sombreado1 == GL_FLAT)
  {
    sombreado1 = GL_SMOOTH;
    sombreado2 = GL_FLAT;
  }
  else
  {
    sombreado1 = GL_FLAT;
    sombreado2 = GL_SMOOTH;
  }
}

int getSombreado()
{
  return sombreado1;
}

// Cambia el estado de la iluminacion(si true entonces false y viceversa)
void invertirIluminacion()
{
  luz = !luz;
}

void cambiarPuntoLuz()
{
  luz0 = !luz0;
}

void alternarAnimacion()
{
  animacion = !animacion;
}

void setSeleccion(int i, int j)
{
  r = i / 255.0f;
  g = j / 255.0f;
  r = round(r * 100) / 100;
  g = round(g * 100) / 100;
}

void getSeleccion(float *i, float *j)
{
  *i = r;
  *j = g;
}

void guardaSeleccion()
{
  std::copy(std::begin(seleccionado), std::end(seleccionado), std::begin(aseleccionado));
}
void recuperaSeleccion()
{
  std::copy(std::begin(aseleccionado), std::end(aseleccionado), std::begin(seleccionado));
}

void setColorSeleccion(float color[3])
{
  guardaSeleccion();
  seleccionado[0] = color[0];
  seleccionado[1] = color[1];
  seleccionado[2] = color[2];
  accionActual = COLOR;
}

void setAccionActualMenu(int nuevaAccion)
{
  accionActual = nuevaAccion;
}

const GLfloat *getSeleccionado()
{
  return seleccionado;
}

void elegirAccionMenu(GLfloat mat_ambient[4], GLfloat mat_diffuse[4])
{
  switch (accionActual)
  {
  case COLOR: // o ambiente
    mat_ambient[0] = getSeleccionado()[0];
    mat_ambient[1] = getSeleccionado()[1];
    mat_ambient[2] = getSeleccionado()[2];

    mat_diffuse[0] = getSeleccionado()[0];
    mat_diffuse[1] = getSeleccionado()[1];
    mat_diffuse[2] = getSeleccionado()[2];
    recuperaSeleccion();
    accionActual = NONE;
    break;
  }
}

/**	void initModel()
Inicializa el modelo y de las variables globales
**/
/*Practica 2*/
Malla malla1("./plys/beethoven");
Malla malla2("./plys/big_dodge");
// Sin textura
ObjetoRevolucion peon("./plys/perfil", 20, true, true);
ObjetoRevolucion fuente("./plys/miperfil", 100, true, true);

/*Practica 4*/
Cubo dado(default_size, "./texturas/dado.jpg");
ObjetoRevolucion lata("./plys/lata-pcue", "./texturas/cerveza.jpg", 0, 100);
ObjetoRevolucion tapainf("./plys/lata-pinf", "./texturas/tapas.jpg", 0.5f, 100, false, true); // x=260, y=256, radio 255
ObjetoRevolucion tapasup("./plys/lata-psup", "./texturas/tapas.jpg", 0.0f, 100, true, false); // x=770, y=257, radio 255
void initModel()
{
  initMenu();
  dado.activarTextura();
  lata.activarTextura();
  tapainf.activarTextura();
  tapasup.activarTextura();
}

class Ejes : Objeto3D
{
public:
  float longitud = 30;
  // Dibuja el objeto
  void draw()
  {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, longitud, 0);

      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(longitud, 0, 0);

      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, longitud);
    }
    glEnd();
    if (/*modo == GL_FILL and*/ luz)
    { // Modo: Solido con iluminacion
      glEnable(GL_LIGHTING);
    }
  }

  void asignarTextura(){};
};

void controlLuz()
{
  GLfloat light_red[4] = {0.8f, 0.2f, 0.2f, 1.0f};
  static GLfloat pos1[4] = {5.0, 5.0, 10.0, 0.0};    // Posicion de la fuente de luz 1
  static GLfloat pos2[4] = {-5.0, -5.0, -10.0, 0.0}; // Posicion de la fuente de luz 2

  glLightfv(GL_LIGHT0, GL_POSITION, pos1); // Declaracion de luz. Colocada aqui esta fija en la escena
  glLightfv(GL_LIGHT1, GL_POSITION, pos2); // Declaracion de luz. Colocada aqui esta fija en la escena
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_red);
  if (luz)
  {
    glEnable(GL_LIGHTING);
    if (luz0)
    {
      glEnable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
    }
    else
    {
      glEnable(GL_LIGHT1);
      glDisable(GL_LIGHT0);
    }
  }
  else
  {
    // glDisable(GL_LIGHTING);
  }
}

void controlTextura()
{
  if (modoTextura)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);
}

// Crea los objetos que vamos a dibujar
Ejes ejesCoordenadas;

/*Practica 1*/
Cubo cubo(default_size);
Piramide piramide(default_size, default_size * 2);
PrismaHexagonal prisma(default_size / 2, default_size);

/*Practica 3*/
Bici bici(1, 1.5, 1.5, 1);

int pick(int x, int y, int *i, int *componente)
{
  GLint viewport[4];
  unsigned char data[4];
  bool luzAnterior = luz;
  glGetIntegerv(GL_VIEWPORT, viewport);
  glDisable(GL_DITHER);
  modoTextura = false;
  luz = false;
  dibujoEscena();
  luz = luzAnterior;
  modoTextura = true;
  glEnable(GL_DITHER);
  glFlush();
  glFinish();

  glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  *i = data[0];
  *componente = data[1];
  glutPostRedisplay();
  return *i;
}

void ColorSeleccion(int i, int componente)
{
  unsigned char r = (i & 0xFF);
  unsigned char g = (componente & 0xFF);
  glColor3ub(r, g, 0);
}

/**	void Dibuja( void )
Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
**/
void Dibuja(void)
{
  // Activa o desactiva la iluminacion
  dibujoEscena();
  glutSwapBuffers(); // Intercambia el buffer de dibujo y visualizacion
}

// Variables iluminacion y materiales
GLfloat bright_mat[4] = {0.2f, 0.2f, 0.2f, 1.0f};

GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat fuenteColor[4] = {0.99f, 0.99f, 0.99f, 1.0f};
GLfloat tapainfColor[4] = {0.98f, 0.98f, 0.98f, 1.0f};
GLfloat tapasupColor[4] = {0.97f, 0.97f, 0.97f, 1.0f};
GLfloat lataColor[4] = {0.96f, 0.96f, 0.96f, 1.0f};

GLfloat dadoColor[4] = {0.81f, 0.81f, 0.81f, 1.0f};

GLfloat light_red[4] = {0.8f, 0.2f, 0.2f, 1.0f};
GLfloat light_blue[4] = {0.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_green[4] = {0.2f, 0.8f, 0.2f, 1.0f};
GLfloat light_yellow[4] = {0.8f, 0.8f, 0.2f, 1.0f};
GLfloat light_greenPeon[4] = {0.21f, 0.81f, 0.21f, 1.0f};
float black[4] = {0.1f, 0.1f, 0.1f, 1.0f};

float ejex = 0, ejey = 0; //Molino
//Elevador
int colsigno = 1, rsopsigno = 1, ysopsigno = 1;
float xcolumna = 0, rsoporte = 20, ysoporte = 0;
//Escalera
int rotaz = -45, rotazsigno = 1, rotazDsigno = -1, desplazaysigno = 1;
float rotazD = 0, desplazay = 0;


//Codigo de elevador
//Dibuja 3 columnas en forma de U y sus 2 soportes(cilindros)
void columnasysoportes(){
  glPushMatrix();
    glTranslatef(xcolumna,0,0); //Movimiento columna Talfa
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B (Columna frontal) Equivale a un cubo unidad escalado 1x10x2

    glPushMatrix();
      materialOrtoedro(light_yellow);
      glTranslatef(0,ysoporte,0); //Movimiento soportes en y (Tbeta)
      glTranslatef(1,5,0.75); //T3
      glRotatef(-90,0,0,1); //R1
      glPushMatrix();
        glRotatef(-20,1,0,0); //R2
        glRotatef(rsoporte,1,0,0); //Rotacion soporte
        cilindro(0.25,0,0.25,0.25,5,0.25,0.5,0.5); //C(soporte izquierdo) Equivale a un cilindro unidad escalado 0.5x5x0.5
      glPopMatrix();
      glPushMatrix();
        glRotatef(20,1,0,0); //R3
        glRotatef(-rsoporte,1,0,0); //Rotacion soporte
        cilindro(0.25,0,0.25,0.25,5,0.25,0.5,0.5); //C(soporte derecho) Equivale a un cilindro unidad escalado 0.5x5x0.5
      glPopMatrix();
      materialOrtoedro(light_blue);
    glPopMatrix();

    glRotatef(90,0,1,0); //R4
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B(columna lateral 1) Equivale a un cubo unidad escalado 1x10x2
    glTranslatef(-3,0,0); //T4
    ortoedro(0.5,0,1,0.5,10,1,1,2); //B(columna lateral 2) Equivale a un cubo unidad escalado 1x10x2
  glPopMatrix();
}


//Codigo de escalera
void escalera(){
  glPushMatrix();
    //Primer soporte vertical
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5);
      glScalef(1,12,1); //E1
      cubo.draw(); //Cubo
    glPopMatrix();

    //Segundo soporte vertical
    glTranslatef(0,0,6); //T4
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
      glScalef(1,12,1); //E2
      cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
    glPopMatrix();

    //Primer escalon
    glTranslatef(0,1.5,-0.5); //T5
    glRotatef(-90,1,0,0); //R2
    glPushMatrix();
      glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
      glScalef(1,5,1); //E2
      cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
    glPopMatrix();   

    for(int i = 0; i < 3; i++){ //3 escalones mas
      glTranslatef(0,0,3); //T6
      glPushMatrix();
        glTranslatef(-0.5,0,-0.5); //Centra el cubo en el eje
        glScalef(1,5,1); //E2
        cubo.draw(); //Genera el cubo con coordenadas de base 0,0,0 | 0,0,1 | 1,0,1 | 1,0,0
      glPopMatrix();   
    }

  glPopMatrix();



}

void dibujoEscena()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);                   // Fija el color de fondo a negro
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  glPushMatrix();                // Apila la transformacion geometrica actual
  transformacionVisualizacion(); // Carga transformacion de visualizacion

  ejesCoordenadas.draw(); // Dibuja los ejes

  // Cambia el modo de visualizacion
  glPointSize(3);
  glPolygonMode(GL_FRONT_AND_BACK, modo);

  // Variables P1
  float cuboC[4] = {0.5, 0.0, 1, 1};
  float p1Color3[4] = {1.0, 0.0, 0, 1};
  float p1Color4[4] = {0.0, 1.0, 0.0, 1};
  controlLuz();

  setNumPractica();
  switch (numPractica)
  {
  case '1': /*Dibuja objetos de la PRACTICA 1*/
    glPushMatrix();
    // Dibuja el cubo
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cuboC);
    cubo.draw();

    // Dibuja la pirámide
    glTranslatef(default_size * 1.5, 0, 0);
    piramide.draw();

    // Figura extra 1 (toroide)
    glTranslatef(default_size * 3, 0, default_size / 2);
    glRotatef(90, 1, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color3);
    glColor3fv(p1Color3);
    glutSolidTorus(default_size / 2, default_size, 24, 32);
    glPopMatrix();

    glPushMatrix();
    // Figura extra 2 (cono)
    glTranslatef(1, 0, 2.5 * default_size);

    glRotatef(-90, 1, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, p1Color4);
    glColor3fv(p1Color4);
    glutSolidCone(default_size / 2, default_size, 24, 20);
    glPopMatrix();

    glPushMatrix();
    // Figura extra 3 (prisma base hexagonal)
    glTranslatef(default_size * 1.5, 0, 2 * default_size);
    prisma.draw();
    glPopMatrix();

    break;
  case '2':
    /*Dibuja P2 con iluminacion y materiales de la P4*/
    glTranslatef(-13, 0, 0);
    // bethoween
    malla1.setMaterial(light_red, light_red);
    malla1.draw();

    // Coche
    glTranslatef(13, 0, 0);
    malla2.setMaterial(light_green, light_green);
    malla2.draw();

    // Peon
    glTranslatef(11, 0, 0);
    glPushMatrix();
    glScalef(2, 2, 2);      // Escalamos el peon
    glEnable(GL_NORMALIZE); // Al escalar, hay que renormalizar las normales
    malla2.setMaterial(light_blue, light_blue);
    peon.draw();
    glPopMatrix();

    // Fuente
    glTranslatef(8, 0, 0);
    fuente.setMaterial(fuenteColor, fuenteColor);
    fuente.draw();
    break;
  case '3':
    if (lectura)
    {
      bici.entradaTecladoBici(Letra);
      lectura = false;
    }
    bici.draw();
    break;
  case '4':
    /*Dibuja objetos de la PRACTICA 4*/
    // Peon 1
    glTranslatef(-6.0, 0, 0);

    // glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(0, 1.4, 0);
    peon.setMaterial(black, black);
    peon.draw();
    // glPopAttrib();
    // Peon 2
    // glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(3, 0, 0);
    peon.setMaterial(light_red, light_red, white, 100);
    peon.draw();
    // glPopAttrib();

    // Peon 3
    //  glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(3, 0, 0);
    peon.setMaterial(light_greenPeon, light_greenPeon, bright_mat);
    peon.draw();
    // glPopAttrib();

    glTranslatef(2, -1.4, 0);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(0, 0, -1);
    // Cubo con textura de dado
    cubo.setMaterialC(dadoColor);
    controlTextura();
    dado.draw();
    glPopMatrix();
    glPopAttrib();

    glTranslatef(4, 0, 0);

    glEnable(GL_NORMALIZE);
    glRotatef(90, 0, 1, 0);
    glScalef(2, 2, 2);
    lata.setMaterial(lataColor, lataColor);
    lata.draw();

    tapainf.setMaterial(tapainfColor, tapainfColor);
    tapainf.draw();

    tapasup.setMaterial(tapasupColor, tapasupColor);
    tapasup.draw();
    glDisable(GL_TEXTURE_2D);
    break;
  case '5':
    glPushMatrix();
    /*Dibuja P2 con iluminacion y materiales de la P4*/
    glTranslatef(-13, 0, 0);
    // bethoween
    malla1.setMaterial(light_red, light_red);
    malla1.draw();

    // Coche
    glTranslatef(13, 0, 0);
    malla2.setMaterial(light_green, light_green);
    malla2.draw();

    // Peon
    glTranslatef(11, 0, 0);
    glPushMatrix();
    glScalef(2, 2, 2);      // Escalamos el peon
    glEnable(GL_NORMALIZE); // Al escalar, hay que renormalizar las normales
    malla2.setMaterial(light_blue, light_blue);
    peon.draw();
    glPopMatrix();

    // Fuente
    glTranslatef(8, 0, 0);
    fuente.setMaterial(fuenteColor, fuenteColor);
    fuente.draw();

    glPopMatrix();
    glTranslatef(0,0,5);
    /*Dibuja objeto de la PRACTICA 3*/
    glPushMatrix();
    if (lectura)
    {
      bici.entradaTecladoBici(Letra);
      lectura = false;
    }
    bici.draw();
    glPopMatrix();

    /*Dibuja objetos de la PRACTICA 4*/
    // Peon 1
    glTranslatef(-6.0, -1.5, 3);

    // glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(0, 1.4, 0);
    peon.setMaterial(black, black);
    peon.draw();
    // glPopAttrib();
    // Peon 2
    // glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(3, 0, 0);
    peon.setMaterial(light_red, light_red, white, 100);
    peon.draw();
    // glPopAttrib();

    // Peon 3
    //  glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(3, 0, 0);
    peon.setMaterial(light_greenPeon, light_greenPeon, bright_mat);
    peon.draw();
    // glPopAttrib();

    glTranslatef(2, -1.4, 0);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    glTranslatef(0, 0, -1);
    // Cubo con textura de dado
    cubo.setMaterialC(dadoColor);
    controlTextura();
    dado.draw();
    glPopMatrix();
    glPopAttrib();

    glTranslatef(4, 0, 0);

    glEnable(GL_NORMALIZE);
    glRotatef(90, 0, 1, 0);
    glScalef(2, 2, 2);
    lata.setMaterial(lataColor, lataColor);
    lata.draw();

    tapainf.setMaterial(tapainfColor, tapainfColor);
    tapainf.draw();

    tapasup.setMaterial(tapasupColor, tapasupColor);
    tapasup.draw();
    glDisable(GL_TEXTURE_2D);
    break;

  case '6':
    materialOrtoedro(light_green);
    ortoedro(1,0,1,1,10,1,2,0); //A
    glTranslatef(1,10,1); //T1
    glRotatef(ejey, 0,1,0); //Ra
    glPushMatrix();
      glTranslatef(-3,2,-1); //T3
      glRotatef(-90,0,0,1); //R1
      materialOrtoedro(light_red);
      ortoedro(1,0,1,1,6,1,2,0); //B
    glPopMatrix();
    glTranslatef(3.5,1,0); //T2
    glRotatef(ejex,1,0,0); //Rb
    glRotatef(-20,0,1,0); //R2
    materialOrtoedro(light_blue);
    glPushMatrix();
      glRotatef(90,0,1,0); //R4
      glTranslatef(-0.5,0,-1); //T5
      ortoedro(0.5,0,0.5,0.5,6,0.5,1,0); //C
    glPopMatrix();
    glRotatef(40,0,1,0); //R3
    glTranslatef(0,-6,0); //T4
    glPushMatrix();
      glRotatef(90,0,1,0); //R4
      glTranslatef(-0.5,0,-1); //T5
      ortoedro(0.5,0,0.5,0.5,6,0.5,1,0); //C
    glPopMatrix();
    break;
    case '7':
    materialOrtoedro(light_blue);
    glPushMatrix();
      glRotatef(-90,0,0,1); //R1
      glTranslatef(-1,-6.5,0); //T1
      ortoedro(0.5,0,1,0.5,13,1,1,2); //A(Base) Equivale a un cubo unidad escalado 1x13x2
    glPopMatrix();

    glTranslatef(-7.5,0,0); //T2
    columnasysoportes();

    glTranslatef(15,0,2); //T5
    glRotatef(180,0,1,0); //R5
    columnasysoportes();

    break;

    case '8':
      glPushMatrix();
        glTranslatef(-0.5,0,-0.5); //T1
        ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //A
      glPopMatrix();
      
      glRotatef(ejey,0,1,0); //Ry alfa
     
      glTranslatef(-5,11,-0.5); //T2
      glRotatef(-90,0,0,1); //R1
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //B

      glTranslatef(1,0,0.5);
      glRotatef(ejex,0,1,0); //Rx alfa
      glTranslatef(-1,0,-0.5);
      
      glTranslatef(1,-1,5.5); //T3
      glRotatef(-90,1,0,0); //R2
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //D
      glTranslatef(0,0,10); //T4      
      ortoedro(0.5,0,0.5,0.5,10,0.5,1,0); //C 
    break;

    case '9':
      materialOrtoedro(white); //Material de la escalera
      glRotatef(rotaz,0,0,1); //Rzalfa
      glTranslatef(0,12,0); //T1
      //A
      glPushMatrix();
        glRotatef(-90,0,0,1); //R1
        glRotatef(rotazD,0,0,1); //Rzbeta
        escalera();
      glPopMatrix();
      //D
      glPushMatrix();
        glRotatef(-180,0,0,1); //2*R1
        escalera();
      glPopMatrix();

      //B y C
      glTranslatef(-1,-12,0); //T2
      glTranslatef(0,desplazay,0); //Talfa
      escalera();
      glTranslatef(-1,0,0); //T3
      glTranslatef(0,desplazay,0); //Talfa
      escalera();      

    break;
  }

  glPopMatrix();
}

/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(int v)
{

  //Escalera
  rotaz += 1*rotazsigno;
  if(rotaz >= 0){
    rotazsigno = -1;
  }
  else if(rotaz <= -45){
    rotazsigno = 1;
  }

  rotazD += (80.0f/45.0f)*rotazDsigno;
  if(rotazD > -1){
    rotazDsigno = -1;
  }
  else if(rotazD <= -80){
    rotazDsigno = 1;
  }

  desplazay += (10.0f/45.0f)*desplazaysigno;
  if(desplazay >= 10)
    desplazaysigno = -1;
  else if(desplazay < 0.1)
    desplazaysigno = 1;


  //Molino
  ejex +=1;
  ejey +=1;

  //elevador
  xcolumna += 0.01*colsigno;
  if(xcolumna > 1.5)
    colsigno = -1;
  else if(xcolumna < 0)
    colsigno = 1;

  ysoporte += 0.1*ysopsigno;
  if(ysoporte > 5)
    ysopsigno = -1;
  else if(ysoporte < -3.5)
    ysopsigno = 1;

  rsoporte += 0.5*rsopsigno;
  if(rsoporte > 15)
    rsopsigno = -1;
  else if(rsoporte < 0)
    rsopsigno = 1;


  // Animacion bici
  if (animacion)
  {
    static int sentido = 1, bajaSube = 1;

    /*Ejecutores de animacion*/
    // Desplazamiento
    if (sentido == 1)
      bici.entradaTecladoBici('E'); // Hacia delante
    else
      bici.entradaTecladoBici('e'); // Hacia atras

    // Sillin
    if (bajaSube == 1)
      bici.entradaTecladoBici('T');
    else
      bici.entradaTecladoBici('t');

    /*Disparadores de animacion*/
    if (bici.avance >= 20)
      sentido = -1;
    if (bici.avance <= -20)
      sentido = 1;

    if (bici.altura_sillin >= 1)
      bajaSube = -1;
    if (bici.altura_sillin <= -0.5)
      bajaSube = 1;
  }
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}