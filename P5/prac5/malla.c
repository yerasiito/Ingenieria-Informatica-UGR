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
	modulo malla.c

*/
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "malla.h"
#include "file_ply_stl.h"
#include "lector-jpg.h"
#include <iostream>

Malla::Malla(){}

Malla::Malla(const char *nombre_archivo){
  ply::read(nombre_archivo, vertices, caras);
  normales_caras();
  normales_vertices();
}

Malla::Malla(const char *nombre_archivo, const char *nombre_textura){
  pixeles = LeerArchivoJPEG(nombre_textura, w, h);
  ply::read(nombre_archivo, vertices, caras);

  calcularXmax();
  setTexturaTapa();

  normales_caras();
  normales_vertices();
}

void Malla::setMaterial(GLfloat mat_ambient[4], GLfloat mat_diffuse[4], GLfloat mat_specular[4], 
                        GLfloat e, GLfloat mat_emission[4]){
  glPushAttrib(GL_LIGHTING_BIT);
  float i,j;
  getSeleccion(&i,&j);
  if(i == mat_ambient[0] && j == mat_ambient[1]){ //Comprueba si el objeto está seleccionado
    //Los cambios del menu se aplican en el objeto seleccionado
    elegirAccionMenu(mat_ambient, mat_diffuse);
    glColor3fv(getSeleccionado());
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, getSeleccionado()); //Iluminacion ambiente
    return;
  }

  if(mat_ambient){
    glColor3fv(mat_ambient);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //Iluminacion ambiente
  }
  if(mat_diffuse)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //Reflexión difusa
  if(mat_specular)
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //Reflexión especular
  if(e != -1)
    glMaterialf(GL_FRONT, GL_SHININESS, e); //exponente especular
  if(mat_emission)
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); //Emisividad, por defecto es 0. (Los objetos no suelen emitir luz propia)
}

void Malla::normales_caras(){
  normales_c.clear();
  for(size_t i = 0; i < caras.size(); i+=3){
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

    std::vector <float> normal = {normal_x/modulo, normal_y/modulo, normal_z/modulo};

    //Volcamos el resultado en el vector de normal
    normales_c.insert(normales_c.end(), normal.begin(), normal.end());
  }

}

void Malla::normales_vertices(){
  normales_v.clear();

  //Rellenamos el vector de vertices con 0
  normales_v.resize(vertices.size());
  fill(normales_v.begin(), normales_v.end(), 0.0f);
  
  //Sumamos las normales de los 3 vertices de cada cara
  int j = 0;
  for(size_t i = 0; i < caras.size(); i+=3){
    int iv = caras[i]*3;
    int iv1 = caras[i+1]*3;
    int iv2 = caras[i+2]*3;

    //V1
    normales_v[iv] += normales_c[j];
    normales_v[iv+1] += normales_c[j+1];
    normales_v[iv+2] += normales_c[j+2];

    //V2
    normales_v[iv1] += normales_c[j];
    normales_v[iv1+1] += normales_c[j+1];
    normales_v[iv1+2] += normales_c[j+2];

    //V3
    normales_v[iv2] += normales_c[j];
    normales_v[iv2+1] += normales_c[j+1];
    normales_v[iv2+2] += normales_c[j+2];
    j+=3;
  }

  //Normalizamos cada vertice
  float modulo = 0.0;
  for(size_t i = 0; i < normales_v.size(); i+=3){
    modulo = sqrt(normales_v[i]*normales_v[i] + normales_v[i+1]*normales_v[i+1] + normales_v[i+2]*normales_v[i+2]);
    normales_v[i] /= modulo;
    normales_v[i+1] /= modulo;
    normales_v[i+2] /= modulo;
  }

}

void Malla::draw_caras(){
  glPushMatrix();
  glShadeModel(GL_FLAT);
	glBindTexture( GL_TEXTURE_2D , texId );
  glBegin(GL_TRIANGLES);
  {
    for(size_t i = 0; i < caras.size(); i+=3){
      int iv = caras[i]*3, ivT = caras[i]*2;
      int iv1 = caras[i+1]*3, ivT1 = caras[i+1]*2;
      int iv2 = caras[i+2]*3, ivT2 = caras[i+2]*2;

      glNormal3f(normales_c[i], normales_c[i+1], normales_c[i+2]);

      if(texId != 0)
        glTexCoord2f(coordTextura[ivT], coordTextura[ivT+1]);
      glVertex3f(vertices[iv], vertices[iv+1], vertices[iv+2]);
      
      if(texId != 0)
        glTexCoord2f(coordTextura[ivT1], coordTextura[ivT1+1]);
      glVertex3f(vertices[iv1], vertices[iv1+1], vertices[iv1+2]); 
    
      if(texId != 0)
        glTexCoord2f(coordTextura[ivT2], coordTextura[ivT2+1]);
      glVertex3f(vertices[iv2], vertices[iv2+1], vertices[iv2+2]);
    }
  }
  glEnd();
  glPopMatrix();
}

void Malla::draw_vertices(){
  glPushMatrix();
  glShadeModel(GL_SMOOTH);
	glBindTexture( GL_TEXTURE_2D , texId );
  glBegin(GL_TRIANGLES);
  {
    for(size_t i = 0; i < caras.size() ; i++){
      int iv = caras[i]*3;
      int ivT = caras[i]*2;

      if(texId != 0)
        glTexCoord2f(coordTextura[ivT], coordTextura[ivT+1]);
      glNormal3f(normales_v[iv], normales_v[iv+1], normales_v[iv+2]);
      glVertex3f(vertices[iv], vertices[iv+1], vertices[iv+2]);
    }
  }
  glEnd();
  glPopMatrix();
}

void Malla::draw(){
  if(getSombreado() == GL_FLAT)
    draw_caras();
  else if(getSombreado() == GL_SMOOTH)
    draw_vertices();
  glPopAttrib();
}

void Malla::calcularXmax(){
  for(size_t i = 0; i < vertices.size(); i+=3){
    xMax = std::max(xMax, vertices[i]);
    yMax = std::max(yMax, vertices[i+1]);
  }
}

void Malla::setTexturaTapa()
{
  coordTextura = {};
  float u, v;
  float xRadio = xMax, yRadio = yMax; //el radio es la longitud máxima en x del ply
  for(size_t i = 0; i < vertices.size(); i+=3){
    u = (vertices[i]+xRadio)/(2*xRadio);
    v = (vertices[i+2]+yRadio)/(2*yRadio);
    std::vector<float> coordenada = {u, v};
    coordTextura.insert(coordTextura.end(), coordenada.begin(), coordenada.end());
  }
}