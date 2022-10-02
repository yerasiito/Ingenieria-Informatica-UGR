/*

	Dpto. Lenguajes y Sistemas Informáticos
	E.T.S.I. Informática
	Univ. de Granada

    Dibuja un cubo
    compilar con: gcc cubo.c -lglut -lGLU -lGL -o cubo
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

void
cubo (GLfloat x, GLfloat y, GLfloat z)
//Construye una caja con un vertice en origen y otro en (x,y,z)
{
  float color[4] = { 0.8, 0.0, 1, 1 };
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glBegin (GL_QUAD_STRIP);
  {				/* Caras transversales */
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (x, y, z);
    glVertex3f (0, y, z);
    glVertex3f (x, 0, z);
    glVertex3f (0, 0, z);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (x, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (x, y, 0);
    glVertex3f (0, y, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (x, y, z);
    glVertex3f (0, y, z);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {				/* Costados */
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (x, 0, 0);
    glVertex3f (x, y, 0);
    glVertex3f (x, y, z);
    glVertex3f (x, 0, z);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, z);
    glVertex3f (0, y, z);
    glVertex3f (0, y, 0);
  }
  glEnd ();
}

void
Dibuja (void)
{
  GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
  glPushMatrix ();
  glClearColor (1, 1, 1, 1);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef (-0.5, -0.5, -100);
  glLightfv (GL_LIGHT0, GL_POSITION, pos);
  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0);
  glRotatef (view_rotz, 0.0, 0.0, 1.0);
  cubo (10, 10, 10);
  glPopMatrix ();
  glutSwapBuffers ();
}

/* ------------------------------------------------------------------------- */

void
Ventana (GLsizei ancho, GLsizei alto)
{				// Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
  float calto;
  glViewport (0, 0, ancho, alto);	//fija el area de dibujo en la ventana 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  if (ancho > 0)
    calto = 1 * (GLfloat) alto / (GLfloat) ancho;
  else
    calto = 1;
  glFrustum (-1, 1, -calto, calto, 5, 250);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

static void
idle ()
{
  view_roty += 0.15;
  glutPostRedisplay ();
}

int
main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG: cubo");
  glutDisplayFunc (Dibuja);
  glutReshapeFunc (Ventana);
  glutIdleFunc (idle);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);
  glShadeModel (GL_FLAT);
  glutMainLoop ();
  return 0;
}
