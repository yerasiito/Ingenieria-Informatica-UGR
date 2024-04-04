#include "modelos/retrato.hpp"

Retrato3D::Retrato3D(const std::string & filename) : Objeto3D(), img(filename){
  vertices.push_back( _vertex3<float> (0,0,0));
  vertices.push_back( _vertex3<float> (1,0,0));
  vertices.push_back( _vertex3<float> (1,1,0));
  vertices.push_back( _vertex3<float> (0,1,0));

  caras.push_back( _vertex3<unsigned int> (0,1,2));
  caras.push_back( _vertex3<unsigned int> (0,2,3));

  calcularNormales();

  coordenadasText.push_back(_vertex2<float> (0.0,1.0));
  coordenadasText.push_back(_vertex2<float> (1.0,1.0));
  coordenadasText.push_back(_vertex2<float> (1.0,0.0));
  coordenadasText.push_back(_vertex2<float> (0.0,0.0));

}

void Retrato3D::draw(int modo){
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(posicion.x, posicion.y, posicion.z);
  if (!transformaciones.empty()){
      transformar();
  }

  glShadeModel(GL_SMOOTH);
  GLfloat ambient[4]={1.0, 1.0, 1.0, 1.0};
  GLfloat diffuse[4]={1.0, 1.0, 1.0, 1.0};
  GLfloat specular[4]={1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &specular);

  glMaterialf(GL_FRONT,GL_SHININESS,10);

  //glMatrixMode(GL_MODELVIEW);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // parametros de aplicacion de la textura
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
  // asignacion de la textura
  glTexImage2D(GL_TEXTURE_2D, 0, 3, img.tamX(), img.tamY(), 0, GL_RGB,GL_UNSIGNED_BYTE, img.leerPixels());

  glEnable(GL_TEXTURE_2D);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT,0, &normalVertices[0]);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, &coordenadasText[0]);


  glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, &caras[0]);

  glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}
