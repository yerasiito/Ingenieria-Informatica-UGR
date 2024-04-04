#include "obj3dlib/tetraedro3d.h"
#include <GL/glut.h>


void TetraedroObj3D::drawSolido(){
  glColor3f(colores.x,colores.y,colores.z);
  glutSolidTetrahedron();
}

void TetraedroObj3D::drawSuave(){
  glShadeModel(GL_SMOOTH);
  GLfloat ambient[4]={matAmb.x,matAmb.y,matAmb.z,matAmb.w};
  GLfloat diffuse[4]={matDiff.x,matDiff.y,matDiff.z,matDiff.w};
  GLfloat specular[4]={matSpec.x,matSpec.y,matSpec.z,matSpec.w};
  glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &specular);
  glMaterialf(GL_FRONT,GL_SHININESS,10);

  glMatrixMode(GL_MODELVIEW);
  glColor3f(colores.x,colores.y,colores.z);
  glutSolidTetrahedron();
  glEnd();
}
