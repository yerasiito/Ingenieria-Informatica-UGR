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
	modulo malla.h

*/

#ifndef MALLA_H
#define MALLA_H

#include <vector>
#include "modelo.h"

class Malla:public Objeto3D{
  public:
    std::vector <float> vertices;
    std::vector <int> caras;
    std::vector <float> normales_c;
    std::vector <float> normales_v;
    std::vector <float> coordTextura;
    float xMax = 0.0, yMax = 0.0f;
  public:
    /****************CONSTRUCTORES****************/
    /**
     * @brief Constructor por defecto, necesario para compilar las clases heredadas 
    */
    Malla();

    /**
     * @brief Constructor con parametro. Lee el ply e introduce los valores en las variables de la clase
     * @param nombre_archivo el nombre del archivo a leer
    */
    Malla(const char *nombre_archivo);

    /**
     * @brief Constructor con parametro. Lee el ply y la textura.
    */
    Malla(const char *nombre_archivo, const char *nombre_textura);

    /****************NORMALES****************/
    /**
     * @brief Calcula las normales de las caras del objeto
    */
    void normales_caras();

    /**
     * @brief Calcula las normales de los vertices del objeto
    */
    void normales_vertices();

    /************ILUMINACION & MATERIALES************/
    /**
     * @brief establece el material del objeto
     * @param mat_ambient establece el nuevo color ambiente
     * @param mat_diffuse establece el nuevo color difuso
     * @param mat_specular establece el nuevo color especular
     * @param e establece la nueva exponente especular
     * @param mat_emission establece el nuevo color de emision
    */
void setMaterial(GLfloat mat_ambient[4] = {}, GLfloat mat_diffuse[4] = {}, GLfloat mat_specular[4] = {}, 
                        GLfloat e = -1, GLfloat mat_emission[4] = {});
    
    /****************FUNCIONES DRAW****************/
    /**
     * @brief Dibuja en modo caras(FLAT)
    */
    void draw_caras();

    /**
     * @brief Dibuja en modo vertices(SMOOTH)
    */
    void draw_vertices();

    /**
     * @brief Dibuja el objeto en funcion del modo actual de dibujo
    */
    void draw();

    void calcularXmax();

    void setTexturaTapa();
};

#endif