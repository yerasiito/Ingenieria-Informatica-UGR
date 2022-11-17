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
	modulo textura.h

*/

#ifndef TEXTURA_H
#define TEXTURA_H

#include <vector>
#include "modelo.h"

class Textura{
  public:
  //private:
    GLuint* texId;
	  unsigned anchoT, altoT;
    unsigned char *data;
    const char *image;
          
  public:
    /****************CONSTRUCTORES****************/
    /**
     * @brief Constructor por defecto, necesario para compilar las clases heredadas 
    */
    Textura();

    /**
     * @brief Constructor con parametro. Lee el fichero dado e introduce los valores en las variables de la clase
     * @param nombre_archivo el nombre del archivo a leer
    */
    Textura(const char *nombre_archivo);

    void activar();

    unsigned char * leerPixels()  ;
};

#endif