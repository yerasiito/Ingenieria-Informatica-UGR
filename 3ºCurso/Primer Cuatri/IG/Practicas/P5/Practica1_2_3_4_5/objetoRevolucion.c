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
  modulo objetoRevolucion.c

*/

#include <math.h>
#include <GL/glut.h>      // Libreria de utilidades de OpenGL
#include "file_ply_stl.h" //Para leer los vertices
#include "objetoRevolucion.h"
#include <iostream>

//Constructor por defecto, no borrar
ObjetoRevolucion::ObjetoRevolucion(){};

ObjetoRevolucion::ObjetoRevolucion(const char *nombre_archivo, int nrevol, bool tapa_sup, bool tapa_inf)
{
  ply::read_vertices(nombre_archivo, vertices);
  m = vertices.size() / 3;
  n = nrevol;
  crear_tapas(tapa_sup, tapa_inf);
  crearRevolucion();

  normales_caras();
  normales_vertices();
}

ObjetoRevolucion::ObjetoRevolucion(const char *nombre_archivo, const char *nombre_textura, float centroT, int nrevol, bool tapa_sup, bool tapa_inf)
{
  pixeles = LeerArchivoJPEG(nombre_textura, w, h);
  ply::read_vertices(nombre_archivo, vertices);

  m = vertices.size() / 3;
  n = nrevol;


  crear_tapas(tapa_sup, tapa_inf);
  crearRevolucion();

  if (!tapa_sup && !tapa_inf)
    setTexturaCil();
  else
    setTexturaTapa(centroT);

  normales_caras();
  normales_vertices();
}

void ObjetoRevolucion::normales_vertices()
{
  Malla::normales_vertices();

  // Arreglamos la costura de los vertices del perfil
  float aux = 0.0;
  for (int i = 0; i < m * 3; i++)
  {
    aux = normales_v[i];
    normales_v[i] += normales_v[normales_v.size() - (m * 3) + i];
    normales_v[normales_v.size() - (m * 3) + i] += aux;
  }
  // Normalizamos cada vertice
  float modulo = 0.0;
  for (int i = 0; i < m * 3; i += 3)
  {
    modulo = sqrt(normales_v[i] * normales_v[i] + normales_v[i + 1] * normales_v[i + 1] + normales_v[i + 2] * normales_v[i + 2]);
    normales_v[i] /= modulo;
    normales_v[i + 1] /= modulo;
    normales_v[i + 2] /= modulo;
  }
}

void ObjetoRevolucion::crearRevolucion()
{
  vertices = {};
  // Añade al vertices final todos los vertices rotados
  for (int i = 0; i < n - 1; i++)
  {
    float alfa = (2 * M_PI * i) / (n - 1);
    for (int j = 0; j <= m * 3 - 1; j += 3)
    {
      std::vector<double> vi = {vertices[j] * cos(alfa), vertices[j + 1], vertices[j] * sin(alfa)};
      vertices.insert(vertices.end(), vi.begin(), vi.end());
    }
  }

  // Duplica los vertices del perfil al final
  for (int j = 0; j < m * 3; j += 3)
  {
    std::vector<double> vi = {vertices[j] * cos(0), vertices[j + 1], vertices[j] * sin(0)};
    vertices.insert(vertices.end(), vi.begin(), vi.end());
  }
  // Crear el vector de caras
  caras = {};
  int k = 0;
  for (int i = 0; i <= n - 2; i++)
  {
    for (int j = 0; j <= m - 2; j++)
    {
      k = i * m + j;
      std::vector<int> triangle1 = {k + m + 1, k + m, k};
      std::vector<int> triangle2 = {k + 1, k + m + 1, k};
      caras.insert(caras.end(), triangle1.begin(), triangle1.end());
      caras.insert(caras.end(), triangle2.begin(), triangle2.end());
    }
  }
}

void ObjetoRevolucion::crear_tapas(bool tapa_sup, bool tapa_inf)
{
  if (tapa_inf)
  {
    std::vector<float> ver_inf = {0.001, vertices[1], 0};
    vertices.insert(vertices.begin(), ver_inf.begin(), ver_inf.end());
    m++;
  }

  if (tapa_sup)
  {
    std::vector<float> ver_sup = {0.001, vertices[m * 3 - 2], 0};
    vertices.insert(vertices.end(), ver_sup.begin(), ver_sup.end());
    m++;
  }
}

void ObjetoRevolucion::draw_lines(){

  size_t j = 0;
  while (j < vertices.size())
  {
    glBegin(GL_LINE_STRIP);
    {
      for (int i = 0; i < m; i += 3)
      {
        glVertex3f(vertices[j], vertices[j + 1], vertices[j + 2]);
        j += 3;
      }
    }
    glEnd();
  }
}

void ObjetoRevolucion::draw_points()
{
  glBegin(GL_POINTS);
  {
    for (size_t i = 0; i < vertices.size(); i += 3){
      glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
  }
  glEnd();
}

void ObjetoRevolucion::setTexturaCil()
{
  float u, v;
  float x1, y1, x2, y2;
  float minY = vertices[1];
  float maxY = vertices[vertices.size()-2];
  float di, dmax = maxY - minY;

  for (int i = n; i >= 0; i--)
  {
    u = (float)i / n;
    di = 0;
    for (int j = m; (j - 1) >= 0; j--)
    {
      v = di / dmax;
      x1 = vertices[j * 3 - 6];
      x2 = vertices[j * 3 - 3];
      y1 = vertices[j * 3 - 5];
      y2 = vertices[j * 3 - 2];
      di += sqrt(pow((x1 - x2), 2) + pow((y1 - y2),2));
      v = 1.0f - v;
      // std::cout << "\nVertices: " << v1 << " " << v2 << " ";
      // std::cout << "\nCoordenadas: " << u << " " << v << "\n";
      std::vector<float> coordenada = {u, v};
      coordTextura.insert(coordTextura.end(), coordenada.begin(), coordenada.end());
    }
  }
}

void ObjetoRevolucion::setTexturaTapa(float centro)
{
  coordTextura = {};
  float u, v;
  float radio = vertices[0]; //el radio es la longitud máxima en x del ply
  if(centro){ //Si es la tapa de abajo, el máximo x es el último vertice
    radio = vertices[vertices.size()-3];
  }
  for(size_t i = 0; i < vertices.size(); i+=3){
    u = centro + (vertices[i]+radio)/(2*radio)/2;
    v = (vertices[i+2]+radio)/(2*radio);
    std::vector<float> coordenada = {u, v};
    coordTextura.insert(coordTextura.end(), coordenada.begin(), coordenada.end());
  }
}