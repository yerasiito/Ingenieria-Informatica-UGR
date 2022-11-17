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
  //private:
    std::vector <float> vertices;
    std::vector <int> caras;
    std::vector <float> normales_c;
    std::vector <float> normales_v;
    std::vector <float> cordtextura;
    GLfloat mat_ambient[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat mat_diffuse[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shininess = 100.0f;
    GLfloat mat_emission[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  public:
    /****************CONSTRUCTORES****************/
    /**
     * @brief Constructor por defecto, necesario para compilar las clases heredadas 
    */
    Malla();

    /**
     * @brief Constructor con parametro. Lee el fichero dado e introduce los valores en las variables de la clase
     * @param nombre_archivo el nombre del archivo a leer
    */
    Malla(const char *nombre_archivo);

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
     * @brief establece el color del material con luz ambiente
     * @param new_ambient establece el nuevo color
    */
    void setMatAmbient(GLfloat new_ambient[4]);

    /**
     * @brief establece el color del material con luz difusa
     * @param new_diffuse establece el nuevo color
    */
    void setMatDiffuse(GLfloat new_diffuse[4]);

    /**
     * @brief establece el color del material con luz especular
     * @param new_specular establece el nuevo color
    */
    void setMatSpecular(GLfloat new_specular[4]);

    /**
     * @brief establece el color del material con luz especular
     * @param e exponente especular
    */
    void setSpecularExponent(GLfloat e);

    /**
     * @brief establece el color de emisión del material
     * @param new_diffuse establece el nuevo color que emite
    */
    void setMatEmission(GLfloat new_emission[4]);
    
    /**
     * @brief Aplica la iluminacion al material del objeto malla
    */
    void setIluMat();

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

    void setTextura(const char *archivo);

};

#endif